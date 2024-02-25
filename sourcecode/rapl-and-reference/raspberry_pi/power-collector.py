#!/usr/bin/env python
#  -*- coding: utf-8 -*-
import csv
import threading
from pathlib import Path
from time import sleep, time

import RPi.GPIO as GPIO
from serial import Serial

from daqhats import mcc128, OptionFlags, HatIDs, HatError, TriggerModes, AnalogInputMode, \
    AnalogInputRange
from daqhats.daqhats_utils import select_hat_device, enum_mask_to_string, \
    chan_list_to_mask, input_mode_to_string, input_range_to_string
from lcd import Adafruit_LCD1602
from lcd import PCF8574

# GPIO pin at which the trigger pin is connected
GPIO_BOARD_TRIGGER = 12

READ_ALL_AVAILABLE = -1

CURSOR_BACK_2 = '\x1b[2D'
ERASE_TO_END_OF_LINE = '\x1b[0K'


class MeasurementThread(threading.Thread):
    interrupted: bool = False
    total_samples_read: int = 0

    def __init__(self, hat: mcc128, num_channels: int, writer, meta_writer):
        threading.Thread.__init__(self)
        self.hat = hat
        self.num_channels = num_channels
        self.writer = writer
        self.meta_writer = meta_writer

    def run(self) -> None:
        read_request_size = READ_ALL_AVAILABLE

        # When doing a continuous scan, the timeout value will be ignored in the
        # call to a_in_scan_read because we will be requesting that all available
        # samples (up to the default buffer size) be returned.
        timeout = 5.0

        # Read all of the available samples (up to the size of the read_buffer which
        # is specified by the user_buffer_size).  Since the read_request_size is set
        # to -1 (READ_ALL_AVAILABLE), this function returns immediately with
        # whatever samples are available (up to user_buffer_size) and the timeout
        # parameter is ignored.

        while not self.interrupted:
            read_result = self.hat.a_in_scan_read(read_request_size, timeout)

            # Check for an overrun error
            if read_result.hardware_overrun:
                print('\n\nHardware overrun\n')
                break
            elif read_result.buffer_overrun:
                print('\n\nBuffer overrun\n')
                break

            samples_read_per_channel = int(len(read_result.data) / self.num_channels)
            self.total_samples_read += samples_read_per_channel

            if samples_read_per_channel > 0:
                for m in range(samples_read_per_channel):
                    index = m * self.num_channels
                    self.writer.writerow(read_result.data[index:(index + self.num_channels)])

                sleep(0.01)


def setup_lcd() -> Adafruit_LCD1602.Adafruit_CharLCD:
    PCF8574_address = 0x27  # I2C address of the PCF8574 chip.
    PCF8574A_address = 0x3F  # I2C address of the PCF8574A chip.
    # Create PCF8574 GPIO adapter.
    try:
        mcp = PCF8574.PCF8574_GPIO(PCF8574_address)
    except:
        try:
            mcp = PCF8574.PCF8574_GPIO(PCF8574A_address)
        except:
            print("No LCD Connected")
            return None
    lcd = Adafruit_LCD1602.Adafruit_CharLCD(pin_rs=0, pin_e=2, pins_db=[4, 5, 6, 7], GPIO=mcp)
    mcp.output(3, 1)
    lcd.begin(16, 2)
    lcd.display()
    return lcd


class Measurement:
    lcd: Adafruit_LCD1602.Adafruit_CharLCD

    def lcd_write(self, line1: str, line2: str = ""):
        if self.lcd is not None:
            self.lcd.setCursor(0, 0)
            self.lcd.message((line1.ljust(16) + "\n"))
            self.lcd.message(line2.ljust(16))

    def __init__(self):
        """
        This function is executed automatically when the module is run directly.
        """

        # Store the channels in a list and convert the list to a channel mask that
        # can be passed as a parameter to the MCC 128 functions.
        channels = [0, 1, 2, 3, 4, 5, 6, 7]
        channel_mask = chan_list_to_mask(channels)
        num_channels = len(channels)

        input_mode = AnalogInputMode.SE
        input_range = AnalogInputRange.BIP_5V

        samples_per_channel = 0

        options = OptionFlags.CONTINUOUS | OptionFlags.EXTTRIGGER
        trigger_mode = TriggerModes.RISING_EDGE

        scan_rate = 1000

        GPIO.setmode(GPIO.BOARD)
        GPIO.setup(GPIO_BOARD_TRIGGER, GPIO.IN, pull_up_down=GPIO.PUD_UP)

        ser = Serial("/dev/ttyS0", timeout=5)
        print("Connected to serial interface:", ser.name)
        self.lcd = setup_lcd()
        # Select an MCC 128 HAT device to use.
        address = select_hat_device(HatIDs.MCC_128)
        hat = mcc128(address)

        hat.a_in_mode_write(input_mode)
        hat.a_in_range_write(input_range)
        print('\nSelected MCC 128 HAT device at address', address)

        try:
            while True:
                print("Waiting for benchmark name over serial interface")
                self.lcd_write("Waiting for", "benchmark data")
                while True:
                    binary_line = ser.readline()
                    if not binary_line:
                        print("Waiting for benchmark name over serial interface")
                    else:
                        benchmark_name = str(binary_line.decode("utf-8").replace("\n", ""))
                        break
                print("Got benchmark name:", benchmark_name)
                while True:
                    binary_line = ser.readline()
                    if not binary_line:
                        print("Waiting for benchmark id over serial interface")
                    else:
                        benchmark_id = str(binary_line.decode("utf-8").replace("\n", ""))
                        break
                print("Got benchmark id:", benchmark_id)

                actual_scan_rate = hat.a_in_scan_actual_rate(num_channels, scan_rate)

                print('\nRunning data acquisition on MCC 128')
                print('    Input mode: ', input_mode_to_string(input_mode))
                print('    Input range: ', input_range_to_string(input_range))
                print('    Channels: ', end='')
                print(', '.join([str(chan) for chan in channels]))
                print('    Requested scan rate: ', scan_rate)
                print('    Actual scan rate: ', actual_scan_rate)
                print('    Options: ', enum_mask_to_string(OptionFlags, options))

                output_folder = Path("output", benchmark_name.replace(" ", "_"))
                output_folder.mkdir(exist_ok=True, parents=True)
                self.lcd_write("Initialized", benchmark_name)
                try:
                    print('Starting scan ... Press Ctrl-C to stop\n')
                    with open(Path(output_folder, benchmark_id + ".csv"), "w") as csvfile, open(
                            Path(output_folder, benchmark_id + "_meta.csv"), "w") as meta_csvfile:

                        # write meta information to a csv file
                        meta_writer = csv.writer(meta_csvfile)
                        meta_writer.writerow(["Channels", ', '.join([str(chan) for chan in channels])])
                        meta_writer.writerow(["Requested Scan Rate", scan_rate])
                        meta_writer.writerow(["Actual Scan Rate", actual_scan_rate])
                        meta_writer.writerow(['ID', hat.serial()])

                        writer = csv.writer(csvfile)

                        # Configure and start the scan.
                        # Since the continuous option is being used, the samples_per_channel
                        # parameter is ignored if the value is less than the default internal
                        # buffer size (10000 * num_channels in this case). If a larger internal
                        # buffer size is desired, set the value of this parameter accordingly.
                        hat.trigger_mode(trigger_mode)
                        hat.a_in_scan_start(channel_mask, samples_per_channel, scan_rate,
                                            options)

                        t = MeasurementThread(hat=hat, num_channels=num_channels, writer=writer,
                                              meta_writer=meta_writer)
                        t.start()
                        self.lcd_write("Await trigger", benchmark_name)

                        while t.total_samples_read == 0:
                            sleep(0.1)
                        s = time()
                        print("Trigger received. Starting tracing")
                        self.lcd_write("Measuring", benchmark_name)
                        GPIO.add_event_detect(GPIO_BOARD_TRIGGER, GPIO.FALLING)
                        try:
                            while not GPIO.event_detected(GPIO_BOARD_TRIGGER):
                                print(f"Samples detected:  {t.total_samples_read}")
                                self.lcd_write(f"Measuring {(time() - s):.2f}s", benchmark_name)
                                sleep(1)
                            print("Program stopped")
                            GPIO.remove_event_detect(GPIO_BOARD_TRIGGER)
                        except KeyboardInterrupt:
                            print(CURSOR_BACK_2, ERASE_TO_END_OF_LINE, '\n')
                            print("Tracing aborted!")
                        t.interrupted = True
                        print("Awaiting termination of measurement thread")
                        self.lcd_write("Finalization", benchmark_name)
                        t.join(timeout=10)
                        print("Done!")
                        self.lcd_write("Done", benchmark_name)

                except KeyboardInterrupt:
                    print(CURSOR_BACK_2, ERASE_TO_END_OF_LINE, '\n')
                hat.a_in_scan_stop()
                hat.a_in_scan_cleanup()

        except (HatError, ValueError) as err:
            print('\n', err)
        ser.close()


if __name__ == '__main__':
    Measurement()
