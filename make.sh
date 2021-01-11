#!/bin/bash
echo Compiling!
#
#Compile main sim
g++ -std=c++17 -Wall -Wextra -pedantic-errors -g -o mainSim.o sim/main.cpp sim/organism.h sim/organism.cpp #
#Compile print function#