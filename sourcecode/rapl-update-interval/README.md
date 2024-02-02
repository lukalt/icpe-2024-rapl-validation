Measure update interval of RAPL counters on Intel Icelake.
Code taken from https://github.com/tud-zih-energy/2021-rome-ee/blob/main/RAPL_resoultion/test.c with minor adaptions.

Procedure:

1. Update the MSR variable according to the power plane you want to measure (Intel DRAM: 619, Intel Package: 611)
2. Run "make"
3. Run "./main" and pipe the result into a file
4. The file contains the update interval in number of clock cycles for 10000 RAPL update
5. Plot this data (e.g., using matplotlib or Excel - see `/data/update-interval`)