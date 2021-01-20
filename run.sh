#!/bin/bash
#Do a full simulation run
#Includes recompiling code, running sim, and running processing python scripts
echo Compiling!
#
#Compile main sim
g++ -std=c++17 -Wall -Wextra -pedantic-errors -g -o mainSim.o sim/shared/*.h sim/shared/*.cpp sim/main.cpp #
#Compile print function
#
rm -r data #adsa
mkdir -p data #fsadfa
#
./mainSim.o #
#
echo Processing! #
python3 py/colorPlot.py data/colorPlot.png #
python3 py/heightPlot.py data/heightPlot.png #
python3 py/foliagePlot.py data/foliagePlot.png #
python3 py/plantDisplay.py data/plantDisplay.png #
python3 py/geneticAnalysis.py data/geneDiff.png 20 #
python3 py/bigPlot.py #
python3 py/geneticReader.py #
#