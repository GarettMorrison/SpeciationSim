#include "organism.h"

#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

const int geneLength = 20;

int averageWrap(int in1, int in2, int max){
	//Order nums
	int small = in1;
	int big = in2;
	if(in1 > in2){
		big = in1;
		small = in2;
	}

	int val = 0;
	if(big - small < small + max - big){
		val = (big - small)/2 + small;
	}
	else{
		val = (small + max - big)/2 + big;
	}

	if(val > max){
		val -= max;
	}

	return(val);
}


plant::plant(){
	killPlant();

	dead = true;
}


void plant::printCode(){
	cout << " -> ";
	for(int i = 0; i < geneLength; i++){
		cout << genes[i] << ' ';
	}
	cout << endl;
}


void plant::growPlant(){

	Rgb = genes[0];
	rGb = genes[1];
	rgB = genes[2];
	height = genes[3]/10 + 1;
	foliage = genes[4]/10 + 1;
	roots = (genes[5]>127);

	splitFood = genes[6];

	dead = false;
	procreate = false;

	food -= (height + foliage)*2 + roots*20;
}

void plant::killPlant(){
	for(int i = 0; i < geneLength; i++){
		genes[i] = 0;
	}
	
	Rgb = 0;
	rGb = 0;
	rgB = 0;
	height = 0;
	foliage = 0;
	roots = 0;

	splitFood = 0;

	dead = true;
	procreate = false;

	food = 0;
}

void plant::spawnPlant(int* loadData, int inFood){
	for(int i = 0; i < geneLength; i++){
		genes[i] = loadData[i];
	}
	food = inFood;
	genes[0] = rand()%255;
	genes[1] = rand()%255;
	genes[2] = rand()%255;
	growPlant();
}

void plant::breedPlant(plant &parentA, plant &parentB){ //Plants getting it ON
	int recombo = rand()%11; //Switch various methods for recombination
	switch(recombo){
		case 0:
			for(int i = 0; i < geneLength; i++){ //Every other start A
				if(i%2 == 0){genes[i] = parentA.genes[i];}
				else{genes[i] = parentB.genes[i];}
			}
			break;
		case 1:
			for(int i = 0; i < geneLength; i++){ //Every other start B
				if(i%2 == 0){genes[i] = parentB.genes[i];}
				else{genes[i] = parentA.genes[i];}
			}
			break;
		case 2:
			for(int i = 0; i < geneLength; i++){ //Every third start A
				if(i%3 == 0){genes[i] = parentA.genes[i];}
				else{genes[i] = parentB.genes[i];}
			}
			break;
		case 3:
			for(int i = 0; i < geneLength; i++){ //Every third start B
				if(i%3 == 0){genes[i] = parentB.genes[i];}
				else{genes[i] = parentA.genes[i];}
			}
			break;
		case 4:
			for(int i = 0; i < geneLength; i++){ //Every fourth start A
				if(i%4 == 0){genes[i] = parentA.genes[i];}
				else{genes[i] = parentB.genes[i];}
			}
			break;
		case 5:
			for(int i = 0; i < geneLength; i++){ //Every fourth start B
				if(i%4 == 0){genes[i] = parentB.genes[i];}
				else{genes[i] = parentA.genes[i];}
			}
			break;
		case 6:
			for(int i = 0; i < geneLength; i++){ //Average Half of Values
				if(i%2 == 0){genes[i] = averageWrap(parentA.genes[i], parentB.genes[i], 255);}
				else if(i%4 == 0){genes[i] = parentA.genes[i];}
				else{genes[i] = parentB.genes[i];}
			}
			break;
		case 7:
			for(int i = 0; i < geneLength; i++){ //Average Half of Values
				if(i%2 == 1){genes[i] = averageWrap(parentA.genes[i], parentB.genes[i], 255);}
				else if(i%4 == 0){genes[i] = parentB.genes[i];}
				else{genes[i] = parentA.genes[i];}
			}
			break;
		case 8:
			for(int i = 0; i < geneLength; i++){ //Average 1/3 values
				if(i%3 == 0){genes[i] = averageWrap(parentA.genes[i], parentB.genes[i], 255);}
				else if(i%3 == 1){genes[i] = parentB.genes[i];}
				else{genes[i] = parentA.genes[i];}
			}
			break;
		case 9:
			for(int i = 0; i < geneLength; i++){ //Average 1/3 values
				if(i%3 == 1){genes[i] = averageWrap(parentA.genes[i], parentB.genes[i], 255);}
				else if(i%3 == 2){genes[i] = parentB.genes[i];}
				else{genes[i] = parentA.genes[i];}
			}
			break;
		case 10:
			for(int i = 0; i < geneLength; i++){ //Average 1/3 values
				if(i%3 == 2){genes[i] = averageWrap(parentA.genes[i], parentB.genes[i], 255);}
				else if(i%3 == 0){genes[i] = parentB.genes[i];}
				else{genes[i] = parentA.genes[i];}
			}
			break;
	}

	int mutateCount = rand()%7-2;
	for(int i = 0; i < mutateCount; i++){
		int mutate = rand()%12;

		if(mutate < 3){	//Add random value
			int select = rand()%geneLength;
			int valSet = rand()%256;
			genes[select] = valSet;
		}
		else if(mutate < 6){	//Shift random value by up to 20
			int select = rand()%geneLength;
			int valSet = rand()%51;
			genes[select] = valSet += valSet - 25;
			if(genes[select] > 255){genes[select] -= 255;}
			if(genes[select] < 0){genes[select] += 255;}
		}
		else if(mutate < 9){	//Shift random value by up to 80
			int select = rand()%geneLength;
			int valSet = rand()%161;
			genes[select] = valSet += valSet - 25;
			if(genes[select] > 255){genes[select] -= 255;}
			if(genes[select] < 0){genes[select] += 255;}
		}
		if(mutate == 10){ //Deletion mutation, shift from right
			int select = rand()%geneLength;
			int valSet = rand()%256;

			for(int iGene = select; iGene < geneLength -1; iGene ++){
				genes[iGene] = genes[iGene +1];
			}
			genes[geneLength-1] = valSet;	
		}
		if(mutate == 11){ //Deletion mutation, shift from left
			int select = rand()%geneLength;
			int valSet = rand()%256;

			for(int iGene = select; iGene > 0; iGene --){
				genes[iGene] = genes[iGene -1];
			}
			genes[0] = valSet;	
		}
	}

	growPlant();

	parentA.food /= 2;
	parentB.food /=2;
	food = parentA.food + parentB.food;

	parentA.procreate = 0;
	parentB.procreate = 0;

}

void plant::doTick(int landType, int shadow){
	// cout << foliage << ' ' << shadow << ' ' << height << endl;
	if(dead){return;} //Do nothing if not alive
	float foodGain = foliage; //Default gain

	int heightGap = shadow - height +1; //Reduce gain if in shadow
	// cout << shadow << ' ' << height << endl;
	if(heightGap > 0){
		foodGain /= pow(2, heightGap);
	}

	foodGain -= ((height/10) * (foliage/5)) + roots*10 + 3;

	if(foodGain > 10){foodGain = 10;} //Cap production
	if(foodGain <= 0){foodGain = -10;} //Negative production bleeds fast

	food += foodGain;


	if(landType == 1 && roots == false){
		food -= 30;
	}

	if(food <= 0){
		killPlant();
		return;
	}

	if(food > splitFood){
		procreate = true;
	}

	if(food > 300){food = 300;}

}

// plant::plant(int* parent1, int* parent2, int food){}