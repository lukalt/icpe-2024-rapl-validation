This directory contains the source code for conducting measurements. Before running the scripts, make sure the environment matches the:
- hardware setup (see **experimental_setup/**)
- software setup (see **experimental_setup/system-info**)

## To collect the measurement data for:
- Figure 5:
    - TODO
- Figure 6:
    - navigate to **sourcecode/rapl-update-interval**
    - follow instructions in **README.md**
- Figure 7-15:
    - navigate to **sourcecode/**
    - follow instructions in TODO

## Directory Content:

- **power-collector/**: contains scripts to measure and process raw measurements by the Raspberry Pi.
- **rapl-trace/**: contains the source code of the RAPL trace application, which samples RAPL counters with low overhead during the execution of another application.
- **rapl-update-interval/**: scripts to analyze the RAPL update interval.
- **workloads/**: Custom benchmarks used for evaluation.
- **measure-all-dram.sh**: runs all RAPL validation workloads allocated on DRAM.
- **measure-all-optane.sh**: runs all RAPL validation workloads allocated on PMem.
- **measure-power-rapl.py**: samples the RAPL energy counters and simultaneously collects power measurements via the Raspberry Pi.