## General System Requirements:

- Table 1 in paper provides an overview of the Intel servers used for the experiments.
- Table 2 specifies memory modules tested

#### Additional hardware devices for direct energy consumption measurements (required for reproducing Figures 7-15):
The following table contains a list of other hardware components required for reproducing the actual data collection.
Product URLs are examples. 

| Min. Amount | Product Name                                      | Purpose                                                                                                             | Product URL                                                                                                                                                                                            |
|-------------|---------------------------------------------------|---------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 2           | Adex DDR4 rev. 3, with CSR, Latched               | Installed between DIMM and memory slot. Voltage drop across current-sense resistors is measured to compute current. | https://www.adexelec.com/ddr4-3                                                                                                                                                                        |
| 1           | Raspberry Pi 3 Model B 1,2 GHz QuadCore 64Bit CPU | Collect measurements fromt he Pi                                                                                    | https://www.rasppishop.de/Raspberry-Pi-3-Model-B-12-GHz-QuadCore-64Bit-CPU                                                                                                                             |
| 1           | Raspbery Pi 5V 3A Power Supply                    | Powering the Pi                                                                                                     | https://www.amazon.de/gp/product/B09TZY9XMJ/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1&language=en_GB                                                                                                           |
| 1           | MCC128                                            | Data acquisition on 8 input channels with 16b resolution to measure voltage drop and common-mode voltage            | https://www.mouser.de/ProductDetail/Digilent/6069-410-001?qs=Wj%2FVkw3K%252BMBHG792mJ2izw%3D%3D                                                                                                        |
| 1           | TI INA2180-A2-EVM                                 | Voltage drop amplification of high-current lines (e.g., 1.2V VDD)                                                   | https://www.mouser.de/ProductDetail/Texas-Instruments/INA2180-2181EVM?qs=YCa%2FAAYMW02z%2FAdxvptvsw%3D%3D                                                                                              |
| 1           | TI INA2180-A4-EVM                                 | Voltage drop amplification of low-current lines (e.g., 2.5V VPP, 12V)                                               | https://www.mouser.de/ProductDetail/Texas-Instruments/INA2180-2181EVM?qs=YCa%2FAAYMW02z%2FAdxvptvsw%3D%3D                                                                                              |
| 1           | sb components Raspberry Pi USB UART/I2C Debugger  | Synchronize measurement start via GPIO; Communication link via Pi and system under test                             | https://www.amazon.de/gp/product/B08XY175C2/ref=ppx_yo_dt_b_asin_title_o06_s00?ie=UTF8&psc=1&language=en_GB                                                                                                          |
| 1           | FREENOVE I2C LCD 1602 Module (optional)           | LCD display to show debug information                                                                               | https://www.amazon.de/gp/product/B0B76Z83Y4/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1&language=en_GB                                                                                                           |
| 3m          | 20 awg insulated, solid, tinned copper wire       | Probing wires for current and voltage                                                                               | https://www.amazon.de/gp/product/B08BZKR22W/ref=ppx_yo_dt_b_asin_title_o05_s01?ie=UTF8&psc=1&language=en_GB                                                                                                          |
| 1           | Soldering PCB Board                               | Organize power delivery to different components                                                                     | https://www.amazon.de/gp/product/B0C4T8PF9P/ref=ppx_yo_dt_b_asin_title_o06_s01?ie=UTF8&psc=1&language=en_GB                                                                                            |
| 5           | 2x Screw Terminals                                | Strong wire connections as an alternative to soldering                                                              | https://www.amazon.de/gp/product/B0C4T8PF9P/ref=ppx_yo_dt_b_asin_title_o06_s01?ie=UTF8&psc=1&language=en_GB                                                                                            |
| 1           | LED                                               | Debug LED                                                                                                           | https://www.reichelt.de/de/en/led-5-mm-leaded-green-80-mcd-45--evl-333-2sygd-s5-p230908.html | 
| 4m          | Jumper wires                                      | Connect grounds between systems and used for the trigger signal                                                     | https://www.amazon.de/QILUCKY-Female-Female-Male-Female-Male-Male-Raspberry/dp/B0B1PD6SRH |

Other equipment:

- Soldering iron with common soldering tools
- Insulating tape
- Digital multimeter

The devices are to be connected as shown in **circuit_schematic.pdf**. Attach photos give more details.

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
