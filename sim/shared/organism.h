#ifndef ORGANISM_H
#define ORGANISM_H

#include <string>
#include <iostream>


using namespace std;

struct mateSelector{
	int weight = 0;
	int check = 0;
	int trait = 0;
	int target = 0;
};

class plant{
public:
	plant();
	void spawnPlant(int* loadData, int food);

	float considerMatch(plant &mate);
	void breedPlant(plant &parentA, plant &parentB);
	void growPlant();
	void killPlant();

	void printCode();
	// plant(int* parent1, int* parent2, int food);
	void doTick(int landType, int shadow); //Plant grows every tick

	//Traits
	int height;
	int foliage;
	bool roots;

	int setCount;
	int mateSelCount;
	mateSelector mateSels[10];


	//Color vars
	int Rgb;
	int rGb;
	int rgB;

	//Mechanical Vars
	int food;
	bool dead;
	int foodDrain;

	bool procreate;
	int splitFood; //TEMP
	
	int genes[20];

private:
};




#endif