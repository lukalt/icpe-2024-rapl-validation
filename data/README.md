This directory contains the raw measurement data from our experiments, scripts to visualize the data, and the final visualized plots.

## General Requirements for Data Visualization
- Desktop environment is required (Windows 10 Pro was used for the paper, Linux/macOS should work as well)
- Python 3 (`3.10.13` was used for the paper) with the following packages:
  - Install required dependencies. Either:
    - manually: `pip install numpy matplotlib pandas pathlib notebook Pyarrow`
    - or restore environment from the provided `requirements.txt`: `pip install -r requirements.txt`
- It is recommended to run everything in a separate Python environment (e.g., using Conda)
- Launch Jupyter notebook: `jupyter notebook`
- The Jupyter notebook app will open in your web browser
<!--
  - `numpy==1.22.4`
  - `pandas==2.1.1`
  - `matplotlib==3.8.0`
-->

### Specific instructions for Data Visualization per figure:
- Figure 5: navigate to **data/error-margin-analysis**, double-click on **Visualize_Error_Analysis.ipynb**, and run all cells in the notebook.
- Figure 6: navigate to **data/update-interval/**, double-click on **Visualize_Update_Interval.ipynb**, and run all the cell in the notebook. 
- Figures 7-15: navigate to **data/rapl-and-reference-results**, double-click on **Visualize_RAPL_Results.ipynb**, and run all the cell in the notebook.

See corresponding README.md files for more information.


## Directory content:

- **error-margin-analysis**: Data and visualization for the measurement error analysis
- **update-interval**: Data and visualization for the RAPL update interval evaluation on the IceLake-SP and Broadwell-EP system.
- **requirements.txt**: python packages required to create the environment