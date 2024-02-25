Measure update interval of RAPL counters on a system of your choice (Intel Ice Lake-SP and Broadwel-EP systems were used in paper)
The code is taken from https://github.com/tud-zih-energy/2021-rome-ee/blob/main/RAPL_resoultion/test.c with minor adaptions.

Procedure:

1. Update the MSR variable according to the power plane you want to measure (Intel DRAM: 619, Intel Package: 611)
2. Run "make"
3. Run "./main.exe" and pipe the (stdout) output into a CSV file. The file contains the update interval in number of clock cycles for 10000 RAPL update
5. Plot this data with **/data/update-interval/Visualize_Update_Interval.ipynb** Jupyter notebook by setting your path to the source CSV file. Note, the paper shows only the memory domain in Figure 6.