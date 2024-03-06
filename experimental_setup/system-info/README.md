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
- Figure 7-15: require probing signals from riser cards. To collect such data, specific software setup for the Raspberry Pi and the test machine are listed in **sourcecode/rapl-and-reference/README.md**.
    - Intel compiler icx
    - CBLAS or Intel MKL
    - Figures 7, 11, 14: require Optane PMMs in addition to DRAM. The PMMs are to be configured in AppDirect mode which can be done with:
        - ndctl
        - daxctl

## Software environment requirements for data visualization:
- see **data/README.md** for the details


## Directory content:

**Broadwell**
- `dmidecode_hardware.txt`: output of `dmidecode`
- `pip_packages.txt`:  All Python packages installed on the Broadwell-EP system.
- `yum_packages.txt`: All Yum packages installed on the Broadwell-EP system.

**Ice Lake**
- `dmidecode_hardware.txt`: output of `dmidecode`
- `numa-topology.txt`: output of `numactl -H`
- `ndctl.txt`: Output of `ndctl namespaces` (populated with 1x128GB PMM per socket)
- `daxctl.txt`: Output of `daxctl namespaces` (populated with 1x128GB PMM per socket)
- `pip_packages.txt`:  All Python packages installed on the Ice Lake-SP system.
- `yum_packages.txt`: All Yum packages installed on the Ice Lake-SP system.

**Raspberry Pi**
- `pip_packages.txt`: Contains all Python packages installed on the Pi.
- `apt_packages.txt`: Contains all Apt packages installed on the Pi.
