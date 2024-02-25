Measure update interval of RAPL counters on a system of your choice (Intel Ice Lake-SP and Broadwell-EP systems were used in paper).
Based on these experiments, Figure 6 of the paper has been generated.

The code has been adapted from https://github.com/tud-zih-energy/2021-rome-ee/blob/main/RAPL_resoultion/test.c.

Instructions:
- Ensure that you have `root` access 
  - Alternative, ensure that `/proc/sys/kernel/perf_event_paranoid` is 1 or lower and that you can access `/dev/cpu/0/msr`.
- Build the application using `make all`.
- Run the application using `make run`.
- Ensure that the measured reference clock rate is correct
  - If it is incorrect, manually determine it and hard code it in `main.c`
- Further process the generated `.csv` file with as described in `/data/rapl-update-interval`.

#### MSR IDs
The script is configured to measure update intervals for Package and DRAM power planes on Intel systems.
Users can change the used MSRs. Commonly used MSRs for RAPL are:

| Platform | Power Plane  | MSR        |
|----------|--------------|------------|
| Intel    | Package      | 0x611      |
| Intel    | DRAM         | 0x619      |
| Intel    | Core (PP0)   | 0x639      |
| Intel    | Uncore (PP1) | 0x641      |
| Intel    | Platform     | 0x64D      |
| AMD      | Core         | 0xC001029A |
| AMD      | Package      | 0xC001029B |