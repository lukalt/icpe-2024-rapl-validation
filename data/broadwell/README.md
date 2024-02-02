This folder contains the raw measurement data and visualizations for RAPL validation data on the Broadwell-EP system.
The folder structure is structured the same way as described in `../icelake/README.md` for the IceLake-SP system.

Data is provided for the following hardware configurations:
- `ddr4-2x16gb-2400-both`: `1x16GB DDR4 per socket. Threads are spread across both sockets and access local memory each.`
- `ddr4-2x16gb-2400-socket0`: `1x16GB DDR4 per socket. Threads are placed on socket 0 and access local memory.`
- `ddr4-2x16gb-2400-socket1`: `1x16GB DDR4 per socket. Threads are placed on socket 1 and access local memory.`