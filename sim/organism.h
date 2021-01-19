#ifndef ORGANISM_H
#define ORGANISM_H

#include <string>
#include <iostream>


using namespace std;


class plant{
public:
	plant();
	void spawnPlant(int* loadData, int food);
	void breedPlant(plant &parentA, plant &parentB);
	void growPlant();
	void killPlant();

	void printCode();
	// plant(int* parent1, int* parent2, int food);
	void doTick(int landType, int shadow); //Plant grows every tick

	int height;
	int foliage;
	bool roots;

	int Rgb;
	int rGb;
	int rgB;

	int food;
	bool dead;
	int foodDrain;

	bool procreate;
	int splitFood; //TEMP
	
	int genes[20];

private:
};




#endif