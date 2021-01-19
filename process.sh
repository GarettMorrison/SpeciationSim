#!/bin/bash
#Run the data processing scripts
echo Processing! #
python3 py/heightPlot.py data/heightPlot.png #
python3 py/foliagePlot.py data/foliagePlot.png #
python3 py/plantDisplay.py data/plantDisplay.png #
python3 py/geneticAnalysis.py data/geneDiff.png 20 #
#
#