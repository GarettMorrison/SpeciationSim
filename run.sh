#!/bin/bash
#Do a full simulation run
#Includes recompiling code, running sim, and running processing python scripts
echo Compiling!
#
#Compile main sim
g++ -std=c++17 -Wall -Wextra -pedantic-errors -o mainSim.o sim/main.cpp sim/organism.h sim/organism.cpp #
#Compile print function
#
mkdir -p data #fsadfa
#
./mainSim.o #
echo Processing! #
python3 py/heightPlot.py #
python3 py/foliagePlot.py #
python3 py/plantDisplay.py #
#