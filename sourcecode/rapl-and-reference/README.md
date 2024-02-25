# RAPL and Reference Power Consumption collection

This folders contains the main source code and scripts to collect RAPL and reference measurements, which requires software both on a Raspberry Pi and the system under test.
In this `README`, we describe the structure of the subfolders and give instructions on how to reproduce the experiments.
- `rasperry_pi` contains all sourcecode for the Raspberry Pi
- `system_under_test/` contains all sourcecode for the System under Test (i.e., the Ice Lake-SP and Broadwell-EP systems for this paper)

## Hardware Setup
Follow the instructions in `/experimental-setup/README.md` to acquire and prepare the hardware required for the experiments.
## Software Setup
Follow the instructions in `rasperry_pi/README.md` and `system_under_test/README.md` to prepare the software stack on both devices.
## Running the experiments
Ensure that all required software components have been installed, compiled, and configured according to the instructions (see above).
### Running the experiments in general
- Boot the Raspberry Pi and 
### Running the experiments with the same workloads as for the paper