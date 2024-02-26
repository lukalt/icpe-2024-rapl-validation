## General software environment requirements for data collection:
- User account with elevated privileges for configuring hardware/software settings
- OS, kernel, power governor (see Table 1 in paper)
- RAPL interface
- libnuma
- GCC compiler 8.5.0
- OpenMP support
- python3
- make

### Specific software environment requirements for each experiment:
- Figure 5: CS-AMPLIFIER-ERROR-TOOL from https://www.ti.com/tool/CS-AMPLIFIER-ERROR-TOOL
  - Preconfigured versions of this Excel tool are bundled with this artifact
- Figure 6: N/A
- Figure 7-15: require probing signals from riser cards. To collect such data, specific software setup for the Raspberry Pi and the test machine are listed in **experimental_setup/reproduction_instructions.pdf**.
    - Intel compiler icx
    - CBLAS or Intel MKL
    - Figures 7, 11, 14: require Optane PMMs in addition to DRAM. The PMMs are to be configured in AppDirect mode which can be done with:
        - ndctl
        - daxctl

## Software environment requirements for data visualization:
- see **data/README.md** for the details


## Directory content:

**Broadwell**
- *dmidecode_hardware.txt*: output of `dmidecode`

**Ice Lake**
- *dmidecode_hardware.txt*: output of `dmidecode`
- *numa-topology.txt*: output of `numactl -H`
- *ndctl.txt*: Output of `ndctl namespaces`
- *daxctl.txt*: Output of `daxctl namespaces`



**pip_packages.txt**
contains all Python packages installed on both the Broadwell-EP and Ice Lake-SP systems.

**yum_packages.txt**
all yum package manager packages installed on both the Broadwell-EP and Ice Lake-SP systems.