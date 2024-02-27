This folder contains the raw measurement data and the visualization for the current-sense amplifier error analysis.
The data has been generated using the CS-AMPLIFIER-ERROR-TOOL Excel by Texas Instruments https://www.ti.com/tool/CS-AMPLIFIER-ERROR-TOOL, which is provided in this folder with all parameters configured for the 1.2V VDD and 12V rails.
Although a visualization of the RSS error is provided in the Excel spreadsheet, we used a custom python script (provided as a Jupyter notebook) to produce a custom visualization that is consistent with the other figures of this paper.
## Directory Content:

- **Error_Analysis_12v.xlsm**: Raw error analysis for 1.2V configuration 
- **Error_Analysis_1v2.xlsm**: Raw error analysis for 12V configuration
- **Visualize_Error_Analysis.ipynb**: Jupyter notebook to generate the figure
- **error_margin_analysis.pdf**: Final figure used in the paper