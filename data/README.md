# Data

This folder contains the raw measurement data from our experiments, scripts to visualize the data, and the final visualization.

Includes files/folders:
- `broadwell`: Measurement data and visualization for the Broadwell-EP system
- `error-margin-analysis`: Data and visualization for the measurement error analysis
- `icelake`: Measurement data and visualization for the IceLake-SP system
- `update-interval`: Measurement data and visualization for the RAPL update interval evaluation on the IceLake-SP and Broadwell-EP system.
- `Visualization RAPL Results.ipynb`: Main script (Jupyter notebook) to process and visualize the raw measurements for the RAPL validation. Input and Results are stored in the `broadwell` and `icelake` subfolders.

## Instruction on how to run `Visualization RAPL Results.ipynb`
- Desktop environment is required (Windows 10 Pro was used for the paper, Linux/macOS should work as well)
- It is recommended to run everything in a separate Python environment (e.g., using Conda)
- Install Python3 (`3.10.13` was used for the paper)
- Install required dependencies. Either:
  - Install them manually: `pip install numpy matplotlib pandas pathlib notebook Pyarrow`
  - Restore environment from the provided `requirements.txt`: `pip install -r requirements.txt`
- Run jupyter notebook: `jupyter notebook`
- The jupyter notebook app will open in your web browser
- Navigate to the current folder and open `Visualization RAPL Results.ipynb`
- Run all cells in the notebook
- The visualizations can be found in `icelake/` and `broadwell/` (see corresponding README.md files for more information)