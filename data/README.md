This directory contains the raw measurement data from our experiments, scripts to visualize the data, and the final visualized plots.

## General Requirements for Data Visualization
- Desktop environment is required (Windows 10 Pro was used for the paper, Linux/macOS should work as well)
- Python 3 (v.3.10.13 was used for the paper) with the following packages:
  - Install required dependencies. Either:
    - manually: `pip install numpy matplotlib pandas pathlib notebook Pyarrow openpyxl`
    - OR restore environment from the provided `requirements.txt` using pip: `pip install -r requirements.txt`
    - OR load the provided Conda environment (recommended): 
        - Install `conda 4.14.0` or later and open an (Ana)conda prompt. Load the environment this way:
        - `conda env create -n rapl_validation_visualization --file environment.yml`
        - `conda activate rapl_validation_visualization`
- Launch Jupyter notebook: `jupyter notebook`
- The Jupyter notebook app will open in your web browser


### Specific Instructions for Data Visualization per figure:
- Figure 5: navigate to **data/error-margin-analysis** in the Jupyter, double-click on **Visualize_Error_Analysis.ipynb**, and run all cells in the notebook.
- Figure 6: navigate to **data/update-interval/**, double-click on **Visualize_Update_Interval.ipynb**, and run all the cell in the notebook. 
- Figures 7-15: navigate to **data/rapl-and-reference-results**, double-click on **Visualize_RAPL_Results.ipynb**, and run all the cell in the notebook.

See corresponding `README.md` files for more information.


## Directory Content:

- **error-margin-analysis/**: Data and visualization for the measurement error analysis
- **rapl-and-reference-results/**: Data and visualization for the measurements from riser cards on IceLake-SP and Broadwell-EP system
- **rapl-update-interval/**: Data and visualization for the RAPL update interval evaluation on the IceLake-SP and Broadwell-EP system
- **requirements.txt**: Python packages required to create the environment (load with `pip install -r requirements.txt`)
