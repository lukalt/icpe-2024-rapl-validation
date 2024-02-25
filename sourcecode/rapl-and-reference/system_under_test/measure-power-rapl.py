#!/usr/bin/env python
import serial
from time import sleep, time
import sys
import subprocess
import os
import argparse
import uuid
from pathlib import Path

def prompt_sudo():
    ret = 0
    if os.geteuid() != 0:
        msg = "[sudo] password for %u:"
        ret = subprocess.check_call("sudo -v -p '%s'" % msg, shell=True)
    return ret == 0

par = argparse.ArgumentParser(prog="power collector", description='Collect RAPL measurements during the execution of a provided application and trace the actual power consumption using the Pi')
par.add_argument('-P', dest="raplPath", default="/home/user01/rapl-trace/main.out", type=str, help="Path to the compiled RAPL trace executable.")
par.add_argument("-I", dest="sampleInterval", default=1, type=int, help="RAPL sampling interval in milliseconds.")
par.add_argument("-S", dest="serialPort", default="/dev/ttyACM0", type=str, help="Path to the serial port interface of the MCP2221")
par.add_argument("-N", dest="name", default="unnamed", type=str, help="The name of the application to execute. Will be displayed on the LCD.")
args, remainder = par.parse_known_args(sys.argv)
if len(remainder) > 0 and remainder[0].lower().endswith(".py"):
    remainder = remainder[1:]
if len(remainder) == 0:
    print("Err: please provide a command to execute")
    exit()
command = " ".join(remainder).strip()

name = args.name
run_id = str(uuid.uuid4())[:8]
print(f"Running experiment {name} ID: {run_id}")
print("   " + command)
output_folder = Path("output", name.replace(" ", "_"))
output_folder.mkdir(parents=True, exist_ok=True)
output_file = Path(output_folder, run_id + "_perf.txt")
print("Writing results to:", output_file)
if not prompt_sudo():
    print("Sudo permissions are required")
    exit()

if args.serialPort != "/dev/null":
    # write id and name of the application to the serial port
    serialPort = serial.Serial(port=args.serialPort)
    serialPort.write((name + "\n").encode())
    serialPort.write((run_id + "\n").encode())
    serialPort.close()
    sleep(0.5) # wait 500ms so the Pi can correctly process the data
else:
    print("Skipping serial port communication")

cmd_args = [args.raplPath, f"{int(args.sampleInterval*1000)}"] + command.split(" ")
process = subprocess.Popen(cmd_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)  # launch the rapl tracing with the delegate application as a subprocess
with open(output_file, "w") as f:
    for line in iter(process.stderr.readline, ""):
        if not line:
            break
        f.write(line.decode())  # write stderr of the rapl traces to a file. The standard error stream contains the RAPL measurements
for line in iter(process.stdout.readline, ""):
    if not line:
        break
    print("[Output]", line.decode().replace("\n", ""))  # print standard output of the delegate application
print(f"Command finished with exit code {process.poll()}")

with open(output_file, "a") as f:
    f.write("### Meta Information\n")  # write some meta information for this run id to a file
    f.write(f"### Sampling Interval: {args.sampleInterval}ms\n")
    f.write(f"### Command: '{cmd_args}'\n")
    f.write(f"### Timestamp {time()}\n")
