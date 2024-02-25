This folder contains all scripts and dependencies for running physical power measurements of DIMM memory on a Raspberry Pi.
Refer to the `README.md` in the parent directory for instructions on how to run the experiments.

### Preparation of the Pi
- We used a Raspberry Pi 3 Model B Rev. 1.2. Later versions / revisions / model of the Pi are expected to not affect the results.
- Install the MCC 128 on the Pi and wire it according to specifications from `experimental_setup.`
- Install a 32 GB microSD card to the Pi.
- Power the Raspberry Pi via an external power supply. We used the official Raspberry Pi power supply, which outputs up to 3A at 5.1V. Powering the Pi via the USB ports of a server is not recommended.
- Either connect the Pi via a network cable and connect to it via SSH (recommended) or attach a keyboard and a monitor to it for the setup process.
### Software Setup on the Raspberry Pi
- Install any Linux operating system on the Pi. We used Raspberry Pi OS with kernel `Linux raspberrypi 6.1.21-v8+ #1642 SMP PREEMPT Mon Apr  3 17:24:16 BST 2023 aarch64 GNU/Linux`.
- Open a terminal on the Pi (either via SSH or on a screen attached to the Pi)
- Install Python 3 (we used Python 3.9.2), e.g., `sudo apt install python3 python3-dev python3-pip` on Debian/Ubuntu-based systems and `screen` (e.g., `apt install screen`). All used packages with versions can be found in `/experimental_setup/system-info/raspberry-pi/apt_packages.txt`.
- Copy the current folder to the Pi and change the working to directory to the target location
- Install required Python dependencies:
    * Install all required dependencies using `pip install -r requirements.txt`.
    * Alternatively, install these required packages manually:
      * `pip install pyserial`
      * `pip install RPi.GPIO`
      * `pip install numpy`
      * `pip install pandas`
      * `pip install matplotlib`
      * `pip install PyMCP2221A`
- The `daqhats` library (used for communicating with the MCC128) and the `lcd` library (used for debug output on an optional LCD display) are MIT-licensed and are bundled in the current directory. No installation is required.

### Bundled Dependencies:
* `lcd` by Brent Rubell for Adafruit Industries (https://github.com/Freenove/Freenove_LCD_Module/tree/main/Freenove_LCD_Module_for_Raspberry_Pi/Python/Python_Code/1.1_I2CLCD1602)
* `daqhats` by Measurement Computing Corp. (https://github.com/mccdaq/daqhats/)