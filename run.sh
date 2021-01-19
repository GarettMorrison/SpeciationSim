#!/bin/bash
#Do a full simulation run
#Includes recompiling code, running sim, and running processing python scripts
echo Compiling!
#
#Compile main sim
g++ -std=c++17 -Wall -Wextra -pedantic-errors -g -o mainSim.o sim/*.h sim/*.cpp #
#Compile print function
#
mkdir -p data #fsadfa
#
./mainSim.o #
#
echo Processing! #
python3 py/heightPlot.py data/heightPlot.png #
python3 py/foliagePlot.py data/foliagePlot.png #
python3 py/plantDisplay.py data/plantDisplay.png #
python3 py/geneticAnalysis.py data/geneDiff.png 20 #
#