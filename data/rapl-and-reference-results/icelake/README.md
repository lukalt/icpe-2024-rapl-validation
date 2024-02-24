This folder contains the raw measurement data and visualizations for RAPL validation data on the IceLake-EP system.
The results for the Broadwell-EP system can be found in `../broadwell/` for different hardware configurations.

Data is provided for the following hardware configurations:
- `ddr4-2x32gb-3200`: `2x32GB DDR4 per socket. Threads are placed on socket 0. Only memory accesses to local NUMA node.`
- `ddr4-16gb-2400`: `1x16GB DDR4 per socket. Threads are placed on socket 0. Only memory accesses to local NUMA node.`
- `ddr4-32gb-3200`: `1x32GB DDR4 per socket. Threads are placed on socket 0. Only memory accesses to local NUMA node.`
- `ddr4-32gb-3200-both`: `1x32GB DDR4 per socket. Threads are placed on both sockets and memory accesses are local to each NUMA node.`
- `ddr4-32gb-3200-socket0`: `1x32GB DDR4 per socket. Threads are placed on socket 0. Only memory accesses to local NUMA node.`
- `ddr4-32gb-3200-socket1`: `1x32GB DDR4 per socket. Threads are placed on socket 1. Only memory accesses to local NUMA node.`
- `dram`: `1x32GB and 1x128GB PMM per socket. Threads are placed on socket 0. Memory allocation on local DRAM of socket 0.`
- `optane`: `1x32GB and 1x128GB PMM per socket. Threads are placed on socket 0. Memory allocation on local PMM of socket 0.`

Each subfolder contains the results for different hardware configurations with a subfolder for the date the experiments were conducted on.
It contains the following files:
- `config.json`: JSON file describing the experimental setup in a machine-readable format:
  - `riser_names`: Array of the names for each riser (usually corresponds to the type of the memory and/or the socket id)
  - `memory_population`: Text describing the memory configuration
  - `memory_allocation`: Text describing the memory allocation
  - `architecture`: The server architecture the experiments were conducted on: Intel IceLake-SP or Broadwell-EP (see paper)
  - `sockets`: A list of the socket indices which should be visualized in the resulting figures
  - `channels`: List of power lines to the DIMM that are measured in the experiment
    - `riser`: ID of the riser
    - `name`: Name of the power line
    - `voltage_channel`: ID of the DAQ channel that measures the common-mode voltage
    - `voltage_drop_channel`: ID of the DAQ channel that measures the voltage drop
    - `csr_resistance`: Resistance value of the current-sense resistor
    - `gain`: Gain by which the voltage drop is amplified
    - `voltage_gain`: Factor by which the common-mode voltage was scaled (12V lines get converted to lower voltage in the measurement circuit)
- `<workload_id>.pdf`: Phase plot for each workload.
- `scatter.pdf`: Scatter plot showing the correlation between RAPL and reference measurements for all workloads combined.
- `<workload_id>`: A folder containing the raw, unprocessed measurement data
  - `<id>.csv`: Raw voltages collected by the MCC128 for each channel (column x = voltage at channel x).
  - `<id>_meta.csv`: Basic meta information on the configuration of the MCC128 for this run (scan rate, requested scan rate).
  - `<id>_perf.csv`: RAPL measurements samples using custom tool. 
    - `timestamp`: Time in seconds elapsed since the start of the experiment
    - `interval`: Delay to the previous sample in seconds.
    - `socket`: Socket this sample is for
    - `domain`: RAPL domain (package or ram)
    - `energy`: RAPL energy counter difference to previous sample, in Joule.
    - `power`: Average power consumption since the previous sample, in Watt.
- `combined_scatter.pdf`: Scatter plot containing the correlation between RAPL and reference measurements for all memory configurations and workloads conducted on the IceLake-SP system.