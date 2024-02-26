This folder contains all scripts and dependencies for running physical power measurements of DIMM memory on the System under Test.
Refer to the `README.md` in the parent directory for instructions on how to run the experiments.

### Preparation of the System under Test
- Remove the server from the rack
  - Experimental setup requires some space

### Software Setup on the System under Test
- Install Rocky Linux 8.8 (we used kernel `6.4.3-1.el8.elrepo`).
- Install the packages `sudo yum install numactl libnuma python3 python3-dev python3-devel hidapi`.
  - All installed RHEL 8 packages can be found in `/experimental-setup/system-info/yum packages.txt`.
- Install the python packages `sudo pip install numpy pandas PyMCP2221A hidapi==0.14.0 libusb pyserial`.
  - In our case, the installation of `PyMCP2221A` was challenging and required a couple of other dependencies.
  - A list of all installed Python packages can be found in experimental - `/experimental-setup/system-info/setup/system-info/pip_packages.txt`.
  - Install all requirements using `pip install -r requirements.txt`.

### Required Changes for DDR5 Measurements
Our setup can be modified to measure the power consumption of DDR5 DIMMs.
As the DDR5 interface is incompatible with DDR4, our riser cards do not work
here, and DDR5-compatible alternatives can be used. Currently, we only found
the DDR5-R riser from Adex Electronics1, which, however, only supports 4800
MT/s memory. Also, validate that the current-sense resistors are rated for the
voltage and current through them (see paper section 4.5). If too much heat is
dissipated at the shunt, the riser, the memory module, or even the mainboard
can be damaged. Registered DDR5 DIMMs are powered using a single 12 V
supply, and unbuffered DDR5 memory is powered using 5 V. Thus, only a single
current-sense amplifier (ideally with a gain of 200) and two data-acquisition
channels are required for measuring the power consumption of a single DDR5
DIMM. If the bus voltage (e.g., 12V for RDIMMs) exceeds the maximum input
voltage of the DAQ device, a voltage divider (see schematic) is required to step
down the voltage to fit into the supported range.

### Tips and Troubleshooting for IT Setup
Due to the required space for the hardware instrumentation, the server could not
be operated in the rack in the server room. Thus, we moved it to another room
where we set up our measurements. As no network connection to the cluster
infrastructure was available in this room, a local network using an ethernet
switch was set up. The Pi was used to bridge WiFi to this local network, and
we connected the server to the switch via a USB to Ethernet adapter as the Ice
Lake system did not have an RJ45 public network port. The management port
was also connected to the switch to access the IPMI.
Because the server was not connected to the cluster anymore, the distributed
file system and the local operating system of the server could not be used. Thus,
we had to install our own operating system, which did not work at first as the
server did not detect any USB boot devices. After installing Rocky Linux on an
old SATA SSD and connecting this SSD via a SATA to a USB adapter to the
server, the system correctly detected it and booted successfully. We installed
PAPI v7.0.1 libnuma v2.0.16, and libmemkind v1.14.0 from sources.
Do not hesitate to contact the author if questions or problems arise during
the reproduction of the experiments.