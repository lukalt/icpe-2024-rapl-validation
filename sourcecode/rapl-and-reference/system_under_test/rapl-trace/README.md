# RAPL Trace
This application executes any command as a sub-process and measures and outputs RAPL energy consumption at a defined sampling interval during the execution of the application.
The measurements are printed to the standard error stream.
This application has been designed for a minimum overhead of the measurements.

## Requirements
* make
* gcc (other compilers work as well, change the compiler accordingly in the `Makefile`)
* `python3` and `python3-dev` / `python3-devel`

## Usage
- Compile the tool using `make all`
- Log in as `root` or run subsequent commands with `sudo`
- To trace RAPL measurements during the execution of an application, run this application the following way:
```
./sample-rapl.exe <sampling_interval_microseconds> [command...]
```
Specify the sampling interval for the measurements in microseconds (e.g. 1000 for 1ms) followed by the command to execute in a child process.

- If compiled with the ``GPIO_TOGGLE`` flag, the GPIO 2 of a MCP2221 USB device will be set to 1 when the measurements start and set back to 0 after the measurements end.
## Credits
This application is based on a RAPL script by Vince Weaver (https://web.eece.maine.edu/~vweaver/projects/rapl/rapl-read.c).
## Troubleshooting
- `gcc: fatal error: cannot read spec file ‘/usr/share/dpkg/no-pie-compile.specs’: No such file or directory`
  - Install the following package: `sudo apt install libdpkg-perl
- `Trying to open: /dev/cpu/0/msr`
  - Ensure that your system supports RAPL and MSRs
  - Check that you are running as root or `/proc/sys/kernel/perf_event_paranoid` is set to 1 or lower
  - Check that you can open `/dev/cpu/0/msr`