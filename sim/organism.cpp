#include "organism.h"

#include "genetics.h"

#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

const int geneLength = 20;


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

	// int i = 3
	// while(i < geneLength)

	height = genes[3]/10 + 1;
	foliage = genes[4]/10 + 4;
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

	combineGenes(genes, parentA.genes, parentB.genes, geneLength);

	//Mutate 
	mutate(genes, geneLength);

	growPlant();

	parentA.food /= 2; //Halves parent's food and gives it to child
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
		foodGain /= 2;
		foodGain -= heightGap*2 -2;
	}

	foodGain -= ((height/20) * (foliage/2)) + roots*5;

	if(foodGain > 10){foodGain = 10;} //Cap production
	if(foodGain <= 0){foodGain = -5;} //Negative production bleeds faster

	food += foodGain;


	if(landType == 1){
		food -= height/3;
		if(roots == false){
			food -= 30;
		}
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