# Experimental Setup

## System requirements:
- Table 1 in paper provides an overview of the Intel servers used for the experiments.
- Table 2 specifies memory modules tested


### Hardware devices for direct energy consumption measurements (Figures 7-15):
- 2 x DDR4-compatible riser cards (Figure 2)
- 1 x Raspberry Pi 3B or later
- 2 x INA2180 current-sense amplifier
- 1 x MCC128 data-acquisition board
- 1 x MCP2221 USB UART
- N x Insulated braided copper wires colored, 10 m, 0.14 mm x N
- TODO: add the rest of the devices

The devices to be connected as shown in **circuit_schematic.pdf**.


## Directory Content:

**photos**
- *data-processing.png*: Data processing devices for the instrumented Ice Lake-SP system
- *dimms.jpg*: Front and back photos of used DIMMs (Top: 32GB DDR4, Mid: 16GB DDR4, Bottom: 128GB PMM)
- *ina2180-A2-EVM.jpg*: INA2180-A2 evaluation board
- *ina2180-A4-EVM.png*: INA2180-A4 evaluation board
- *instrumentation_broadwell.jpg*:  Instrumented Broadwell-EP system 
- *instrumentation_broadwell_2.jpg*: Instrumented Broadwell-EP system (close up)
- *instrumentation_icelake.jpg*: Instrumented IceLake-SP system
- *mcp2221.jpg*: MCP2221 USB to UART/GPIO converter installed in USB port of the Ice Lake-SP system
- *perf_board.jpg*: Custom perf board for power distribution
- *riser-cards.jpg*: Ice Lake-SP instrumentation with riser cards 
- *riser-cards-annotated.png*: Ice Lake-SP instrumentation with riser cards (annotated version)
- *riser_back.jpg*: DDR4 riser front view
- *riser_front.png*: DDR4 riser back view

**system-info**
Detailed test system hardware and software specifications

**circuit_schematic.pdf**
Circuit schematic of the experimental setup

**reproduction_instructions.pdf**
Basic instruction on how to run the measurements
