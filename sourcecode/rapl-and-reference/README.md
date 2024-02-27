# RAPL and Reference Power Consumption collection

This folder contains the main source code and scripts to collect RAPL and reference measurements, which requires software both on a Raspberry Pi and the system under test.
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
- Boot the Raspberry Pi
  - Open a terminal
  - Change to the `raspberry_pi` folder created during software setup
  - Run `screen -dmS power-measurements python3 power-collector.py`
  - This will start the agent, which starts the measurements on the Raspberry Pi when requested by the system under test and stores the results on the Raspberry Pi
  - It is recommended, yet not required, to keep the terminal open to monitor the measurements
- Boot the system under test
  - Open a terminal with `root` privileges
  - Change to the `system_under_test` folder creating during software setup
  - The script `python3 measure-power-rapl.py` is the main script to run an experiment
    - It supports several configuration parameters
      - `-P <path>` is the path to the `sample-rapl.exe` executable (found in `raple-trace/`), that regularly samples RAPL counters during the execution of an executable
      - `-I <interval>` is the interval for sampling RAPL counters in milliseconds.
      - `-S <path>` is the path to the MCP2221 serial interface. It is `/dev/ttyACM0` on the system under test and `/dev/ttyS0` on the Raspberry Pi usually. Validate this using `dmesg | grep tty` and update the path if it does not match the default.
      - `-N <workload_name>` is the name of the workload to run. All experiments with the same name will be grouped in the resulting file structure and the name is displayed on the LCD.
    - The arguments are followed by a bash command or executable that will be executed by the script as a child process. RAPL and reference measurements will be executed during the execution of the child process.
    - RAPL sampling is provided by the `sample-rapl.exe` executable, which synchronizes the start and end of measurements via GPIO triggers to the Pi.
    - Any executable or command can be provided as an argument with the following limitations
      - The runtime of it should be at least 250ms
      - A long runtime of the application (> 30 minutes) can lead to storage and memory capacity issues on the Pi
      - Subsequent experiments should be delayed by at least one second
- Merging results
  - The Pi and the system under test both store their measurement data on the local disk.
    - Each experiment is identified by an 8-digit alphanumeric id, which is common on the Pi and the system under test
    - The Pi stores the reference measurements (In `output/<workload_name>/<id>.csv` and some metadata in `output/<workload_name>/<id>_meta.csv` (not required for data processing))
    - The system under test stores RAPL measurements (In `output/<workload_name>/<id>_perf.csv`)
  - After all required experiments have been executed, merge both `output/` folders into a common folder, ideally on your local machine
    - We used SFTP for the file transfers
  - Visualize the raw data as described in `/data/rapl-and-reference-results`
### Running the experiments with the same workloads as for the paper
- We provide a collection of all workloads for experiments conducted for the paper (in particular, Figures 7 - 15 in the paper)
  - Prepare the Pi as described in the last section
  - Change the memory population with risers at the DIMM slots as desired
  - Boot the system under test
    - Open a terminal with `root` privileges
    - Change to the `system_under_test/` folder created during software setup
    - Ensure all workloads in the `workloads/` folder and the subdirectories are compiled using `make`
    - Run `./run_all_workloads_dram.sh` to run all experiments used for DRAM configurations in the paper (and for PMM and DRAM installed in combination with memory allocations only on DRAM)
    - Run `./run_all_workloads_pmm.sh` to run all experiments used for PMM configurations with memory allocations on PMM.
      - The workload and the number of threads is limited for PMM configurations to reduce the execution time for PMM experiments
    - Both scripts run all experiments sequentially with a 5 seconds gap in between
  - Merge and process the results as described above