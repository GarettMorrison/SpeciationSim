#include "genetics.h"

#include <string>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

void mutate(int* inGenes, int geneLength){	//Mutate inGenes
	int mutateCount = rand()%15-10; //Set number of mutations
	for(int i = 0; i < mutateCount; i++){
		int mutationSel = rand()%12;

		if(mutationSel < 3){	//Add random value
			int select = rand()%geneLength;
			int valSet = rand()%256;
			inGenes[select] = valSet;
		}
		else if(mutationSel < 6){	//Shift random value by up to 20
			int select = rand()%geneLength;
			int valSet = rand()%51;
			inGenes[select] = valSet += valSet - 25;
			if(inGenes[select] > 255){inGenes[select] -= 255;}
			if(inGenes[select] < 0){inGenes[select] += 255;}
		}
		else if(mutationSel < 9){	//Shift random value by up to 80
			int select = rand()%geneLength;
			int valSet = rand()%161;
			inGenes[select] = valSet += valSet - 25;
			if(inGenes[select] > 255){inGenes[select] -= 255;}
			if(inGenes[select] < 0){inGenes[select] += 255;}
		}
		if(mutationSel == 10){ //Deletion mutation, shift from right
			int select = rand()%geneLength;
			int valSet = rand()%256;

			for(int iGene = select; iGene < geneLength -1; iGene ++){
				inGenes[iGene] = inGenes[iGene +1];
			}
			inGenes[geneLength-1] = valSet;	
		}
		if(mutationSel == 11){ //Deletion mutation, shift from left
			int select = rand()%geneLength;
			int valSet = rand()%256;

			for(int iGene = select; iGene > 0; iGene --){
				inGenes[iGene] = inGenes[iGene -1];
			}
			inGenes[0] = valSet;	
		}
	}
}

void combineGenes(int* child, int* parentA, int* parentB, int geneLength){
	int recombo = rand()%11; //Switch various methods for recombination
	switch(recombo){
		case 0:
			for(int i = 0; i < geneLength; i++){ //Every other start A
				if(i%2 == 0){child[i] = parentA[i];}
				else{child[i] = parentB[i];}
			}
			break;
		case 1:
			for(int i = 0; i < geneLength; i++){ //Every other start B
				if(i%2 == 0){child[i] = parentB[i];}
				else{child[i] = parentA[i];}
			}
			break;
		case 2:
			for(int i = 0; i < geneLength; i++){ //Every third start A
				if(i%3 == 0){child[i] = parentA[i];}
				else{child[i] = parentB[i];}
			}
			break;
		case 3:
			for(int i = 0; i < geneLength; i++){ //Every third start B
				if(i%3 == 0){child[i] = parentB[i];}
				else{child[i] = parentA[i];}
			}
			break;
		case 4:
			for(int i = 0; i < geneLength; i++){ //Every fourth start A
				if(i%4 == 0){child[i] = parentA[i];}
				else{child[i] = parentB[i];}
			}
			break;
		case 5:
			for(int i = 0; i < geneLength; i++){ //Every fourth start B
				if(i%4 == 0){child[i] = parentB[i];}
				else{child[i] = parentA[i];}
			}
			break;
		case 6:
			for(int i = 0; i < geneLength; i++){ //Average Half of Values
				if(i%2 == 0){child[i] = averageWrap(parentA[i], parentB[i], 255);}
				else if(i%4 == 0){child[i] = parentA[i];}
				else{child[i] = parentB[i];}
			}
			break;
		case 7:
			for(int i = 0; i < geneLength; i++){ //Average Half of Values
				if(i%2 == 1){child[i] = averageWrap(parentA[i], parentB[i], 255);}
				else if(i%4 == 0){child[i] = parentB[i];}
				else{child[i] = parentA[i];}
			}
			break;
		case 8:
			for(int i = 0; i < geneLength; i++){ //Average 1/3 values
				if(i%3 == 0){child[i] = averageWrap(parentA[i], parentB[i], 255);}
				else if(i%3 == 1){child[i] = parentB[i];}
				else{child[i] = parentA[i];}
			}
			break;
		case 9:
			for(int i = 0; i < geneLength; i++){ //Average 1/3 values
				if(i%3 == 1){child[i] = averageWrap(parentA[i], parentB[i], 255);}
				else if(i%3 == 2){child[i] = parentB[i];}
				else{child[i] = parentA[i];}
			}
			break;
		case 10:
			for(int i = 0; i < geneLength; i++){ //Average 1/3 values
				if(i%3 == 2){child[i] = averageWrap(parentA[i], parentB[i], 255);}
				else if(i%3 == 0){child[i] = parentB[i];}
				else{child[i] = parentA[i];}
			}
			break;
	}

}