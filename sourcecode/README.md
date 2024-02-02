# Sourcecode

Sourcecode for conduction measurements. Scripts for data visualization can be found in `../data`.

- `power-collector/`: contains scripts to measure and process raw measurements by the Raspberry Pi.
- `rapl-trace/`: contains the source code of the RAPL trace application, which samples RAPL counters with low overhead during the execution of another application.
- `rapl-update-interval/`: scripts to analyze the RAPL update interval.
- `workloads/`: Custom benchmarks used for evaluation.
- `measure-all-dram.sh`: runs all RAPL validation workloads allocated on DRAM.
- `measure-all-optane.sh`: runs all RAPL validation workloads allocated on PMem.
- `measure-power-rapl.py`: samples the RAPL energy counters and simultaneously collects power measurements via the Raspberry Pi.