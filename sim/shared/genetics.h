#ifndef GENETICS_H
#define GENETICS_H

#include <string>
#include <iostream>

void mutate(int* genes, int geneLength);
void combineGenes(int* child, int* parentA, int* parentB, int geneLength);

int averageWrap(int in1, int in2, int max);
int diffWrap(int in1, int in2, int max);

#endif