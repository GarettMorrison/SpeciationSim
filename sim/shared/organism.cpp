#include "organism.h"

#include "genetics.h"

#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

const int geneLength = 20;
const int geneMax = 255;


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
	setCount = 0;

	int i = 3;
	while(i < geneLength-2){
		int select = genes[i];
		if(select == 0){break;} //End if gene is 0
		setCount += 1;
		select /= 52;

		switch(select){
			case 0:
				i++;
				height = genes[i]/10 + 1;
				break;

			case 1:
				i++;
				foliage = genes[i]/10 + 4;
				break;

			case 2:
				i++;
				roots = (genes[i]>127);
				break;

			case 3:
				i++;
				splitFood = genes[i]*2;
				break;

			case 4: //Add mateselector
				if(mateSelCount >= 10){break;} //Dont overflow selectors
				i++;
				mateSels[mateSelCount].weight = genes[i] % 5+1; //Set weight
				mateSels[mateSelCount].check = genes[i] / 10; //set search
				i++;
				mateSels[mateSelCount].trait = genes[i] % 5; //set trait
				mateSels[mateSelCount].target = genes[i]; //set target
				mateSelCount ++;
				break;

		}
		i++;
	}

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

	mateSelCount = 0;

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

float plant::considerMatch(plant &mate){
	// return(0);
	float weightTotal = 0; //Total weight towars target
	for(int iSel = 0; iSel < mateSelCount; iSel ++){
		int tTarget = mateSels[iSel].target;

		int tIn = -1;
		switch(mateSels[iSel].trait){	//Find target for selector
			case 0:
				tIn = mate.Rgb;
				break;
			case 1:
				tIn = mate.rGb;
				break;
			case 2:
				tIn = mate.rgB;
				break;
			case 3:
				tIn = mate.height;
				tTarget = tTarget/10 + 1;
				break;
			case 4:
				tIn = mate.foliage;
				tTarget = tTarget/10 + 4;
				break;
			case 5:
				tIn = mate.roots;
				tTarget = (tTarget > 127);
				break;
		}

		float weightVal = -1; //Actual weight 
		switch(mateSels[iSel].check){ //Calculate weight of pot mate from selector
			case 0:
				weightVal = (tIn == tTarget);
				break;
			case 1:
				weightVal = 1 - (geneMax - diffWrap(tIn, tTarget, geneMax))/geneMax;
				break;
			case 2:
				weightVal = 1 - (geneMax - abs(tIn - tTarget))/geneMax;
				break;
			case 3:
				weightVal = (geneMax - diffWrap(tIn, tTarget, geneMax))/geneMax;
				break;
			case 4:
				weightVal = (geneMax - abs(tIn - tTarget))/geneMax;
				break;
			case 5:
				weightVal = ((geneMax - diffWrap(tIn, tTarget, geneMax)) < 2);
				break;
			case 6:
				weightVal = ((geneMax - diffWrap(tIn, tTarget, geneMax)) < 5);
				break;
			case 7:
				weightVal = ((geneMax - diffWrap(tIn, tTarget, geneMax)) < 10);
				break;
			case 8:
				weightVal = ((geneMax - diffWrap(tIn, tTarget, geneMax)) < 50);
				break;
			case 9:
				weightVal = ((geneMax - diffWrap(tIn, tTarget, geneMax)) < 100);
				break;
		}

		weightTotal += weightVal*mateSels[iSel].weight; 
	}
	return(weightTotal);
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

	foodGain -= ((height/20) * (foliage/2)) + roots*4 + setCount/2;

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