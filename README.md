*An Experimental Setup to Evaluate RAPL Energy Counters for Heterogeneous Memory - Research Paper Artifact*

This artifact accompanies the research paper `An Experimental Setup to Evaluate RAPL Energy Counters for Heterogeneous Memory` for ICPE 2024.

# Artifact structure:
- `data`: Raw measurement data, visualization scripts, and generated figures
- `sourcecode`: Scripts for collecting and processing measurement data
- `experimental_setup`: Additional material for understanding and reproducing the experimental setup

# Requirements for Data Evaluation Reproduction
All scripts are provided and described in the `data` folder in this artifact.
- Python 3 with the following packages:
  - Jupyter Notebooks
  - `numpy==1.22.4`
  - `pandas==2.1.1`
  - `matplotlib==3.8.0`

# Requirements for Measurement Reproduction
The reproduction of the actual measurements require access to similar systems as described in the paper, the custom measurement hardware as described in the paper and in `experimental_setup/` as well as the software stack (see `experimental_setup/system-info`).