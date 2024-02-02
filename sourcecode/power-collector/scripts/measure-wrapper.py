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

par = argparse.ArgumentParser(prog="power collector",
                                      description='Collect and synchronize power measurements from MCC 128 DAQ board with the system under test')
par.add_argument('-P', dest="perfPath", default="/work/aw272604/perf", type=str)
par.add_argument("-I", dest="sampleInterval", default=1, type=int)
par.add_argument("-S", dest="serialPort", default="/dev/ttyACM0", type=str)
par.add_argument("-N", dest="name", default="unnamed", type=str)
par.add_argument("-E", dest="events", action="append")
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

print("Serial port:", args.serialPort)
if args.serialPort != "/dev/null":
    serialPort = serial.Serial(port=args.serialPort)
    serialPort.write((name + "\n").encode())
    serialPort.write((run_id + "\n").encode())
    serialPort.close()
    sleep(0.5)
else:
    print("Skipping serial port communication")

print("Command to execute:", command)
cmd_args = [args.perfPath, "stat", "-x", "';'", "-e", ",".join(args.events), "-I", str(args.sampleInterval), "--per-node", "--summary", "-o" + str(output_file), "--no-big-num"] + command.split(" ")
process = subprocess.Popen(cmd_args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
for line in iter(process.stdout.readline, ""):
    if not line:
        break
    print("[Output]", line.decode().replace("\n", ""))
print(f"Command finished with exit code {process.poll()}")

with open(output_file, "a") as f:
    f.write("### Meta Information")
    f.write(f"### Sampling Interval: {args.sampleInterval}ms")
    f.write(f"### Command: '{cmd_args}'")
    f.write(f"### Timestamp {time()}")
