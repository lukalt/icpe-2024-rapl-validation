# RAPL Trace
This application executes any command as a sub-process and measures and outputs RAPL energy consumption at a defined sampling interval during the execution of the application.
The measurements are printed to the standard error stream.
This application has been designed for a minimum overhead of the measurements.

## Requirements
* CMake
* C Compiler Installed
* Python3 Installed

## Usage
To trace RAPL measurements during the execution of an application, run this application the following way:
```
./<command> <sampling_microseconds> [command...]
```
Specify the sampling interval for the measurements in microseconds (e.g. 1000 for 1ms) followed by the command to execute in a child process.

If compiled with the ``GPIO_TOGGLE`` flag, the GPIO 2 of a MCP2221 USB device will be set to 1 when the measurements start and set back to 0 after the measurements end.
## Credits
This application is based on a RAPL script by Vince Weaver (https://web.eece.maine.edu/~vweaver/projects/rapl/rapl-read.c).
