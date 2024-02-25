This folder contains C code for workloads to validate RAPL on. 

These workloads are roughly the same the researchers from ZIH at TU Dresden used in their work "Energy Efficiency Aspects of the AMD Zen 2 Architecture" and were manually extracted from the ROCO2 synthethic workload generator (https://github.com/tud-zih-energy/roco2/tree/master).

### How to compile
* Ensure CBLAS ist installed
* Run make
* Run the different workloads using `./<workload>.exe`
* Make sure to set `OMP_NUM_THREADS` to control how many workers will be spawned