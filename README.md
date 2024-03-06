This artifact accompanies the research paper *An Experimental Setup to Evaluate RAPL Energy Counters for Heterogeneous Memory*, ICPE 2024 conference, London, May 7-11, 2024.

# Artifact Structure:
- **data/**: Software requirements for visualizing the plots, raw measurement data, visualization scripts, and generated figures
- **experimental_setup/**: Hardware and software requirements for conducting experiments
- **sourcecode/**: Scripts for collecting and processing measurement data and instructions how to prepare and run the experiments


# Artifact Reproduction Procedure
## To prepare the experimental environment for:
- hardware setup:
    - follow instructions in **experimental_setup/README.md**
- software setup:
    - follow instructions in **experimental_setup/system-info/README.md**

## To collect experimental data for:
- Figure 5:
    - The `Current Sense Amplifier Comparison and Error Calculator` tool from Texas Instruments is provided with all parameters preconfigured in the `/data/error-margin-analysis` folder.
- Figure 6:
    - Navigate to `/sourcecode/rapl-update-interval`
    - Follow instructions in `/sourcecode/rapl-update-interval/README.md`
- Figure 7-15:
    - Navigate to `/sourcecode/rapl-and-reference`
    - Follow instructions in `/sourcecode/rapl-and-reference/README.md`

## To plot collected data:
- Follow instructions in `/data/README.md` per-figure specific instructions
