#include "organism.h"


#include <iostream>
#include <fstream>

#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// #include <string>

using namespace std;

const int mapSize = 500;
const int tickTotal = 50000;
const int printTick = 5;

int main(){
	cout << "Running sim!" << endl;
	srand(time(NULL)); //Initialize random seed



	ofstream heightData("data/plantHeightData.txt", ios::out);//init output file
	ofstream foliageData("data/plantFoliageData.txt", ios::out);//init output file



	//Init Plants
	plant plants[mapSize]; 

	//Add some simple plants
	int basePlant[20] = {100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};

	plants[3].spawnPlant(basePlant, 50);
	plants[5].spawnPlant(basePlant, 50);
	plants[mapSize -2].spawnPlant(basePlant, 50);
	plants[mapSize -5].spawnPlant(basePlant, 50);

	//Init shade
	int shade[mapSize];
	for(int i = 0; i < mapSize; i++){
		shade[i] = 0;
	}
	

	//Main Loop
	for(int tickCount = 0; tickCount < tickTotal; tickCount++){


		//Tick Plants
		for(int i = 0; i < mapSize; i++){

			int terrain = 0;	//TEMP Set bottom half of map to dry, for some possible speciation
			if(i < mapSize/2){terrain = 1;}

			plants[i].doTick(terrain, shade[i]);
		}

		//Breed plants
		for(int i = 0; i < mapSize; i++){ 
			if(!plants[i].procreate || plants[i].dead){continue;}//Test for reproduction
			int pos = rand()%21; //Get random positions
			pos += i -10;
			if(pos < 0 || pos >= mapSize || !plants[pos].dead){continue;} //Keep new plant in bounds and dont overwrite living plant

			for(int j = 0; j < mapSize; j++){
				if(j == i || !plants[j].procreate || plants[j].dead){continue;} //No inbreeding
				plants[pos].breedPlant(plants[i], plants[j]);
				break;
			}

		}




		if(tickCount % 4 == 0){
			for(int i = 0; i < mapSize; i++){ //Zero out shade
				shade[i] = 0;
			}
			
			for(int i = 0; i < mapSize; i++){
				if(plants[i].dead){continue;}
				int shadow = plants[i].height; //Add gradually reduced shadow down the array
				int pos = i-1;
				while(pos >= 0 && shadow > 0){
					if(shade[pos] < shadow){shade[pos] = shadow;}
					pos --;
					shadow --;
				}
				shadow = plants[i].height; //Add gradually reduced shadow up the array
				pos = i+1;
				while(pos < mapSize && shadow > 0){
					if(shade[pos] < shadow){shade[pos] = shadow;}
					pos ++;
					shadow --;
				}
			}
		}



		int liveCount = 0;
		if(tickCount % printTick == 0){	//Record every printTickth state
			// int heightSum = 0;
			// int foliageSum = 0;
			liveCount = 0;
			for(int i = 0; i < mapSize; i++){

				heightData << plants[i].height; //Print heights
				foliageData << plants[i].foliage;
				if(i != mapSize-1){
					heightData << ' ';
					foliageData << ' ';
				}
				
				// heightSum += plants[i].height;
				// foliageSum += plants[i].foliage;
				if(plants[i].dead != true){liveCount ++;}
			}
			heightData << endl;
			foliageData << endl;

			// if(tickCount >= 1000 && tickCount < 1000 + printTick){cout << liveCount << " plants at tick " << tickCount << endl;}
			// if(tickCount >= tickTotal - printTick){cout << liveCount << " plants at tick " << tickCount << endl;}
		}






		//Code to print diversity chart every tick
		// if(tickCount % 1000 == 0){ //Output genes and make image
		// 	cout << liveCount << " plants at tick " << tickCount << endl;

		// 	ofstream oPlant("data/plantGenes.txt", ios::out);//init output file for genes
		// 	for(int i = 0; i < mapSize; i++){
		// 		for(int j = 0; j < 20; j++){
		// 			oPlant << plants[i].genes[j] << ' ';
		// 		}
		// 		oPlant << endl;
		// 	}
		// 	oPlant.close();

		// 	string runString = "python3 py/geneticAnalysisGif.py data/geneGif/" + to_string((int)tickCount/1000) + "_geneDiff.png";
		// 	system(runString.c_str());
		// }

	} //End main loop

	// for(int i = 0; i < mapSize; i++){cout << plants[i].foliage << ' ';}

	heightData.close();
	foliageData.close();

	
	ofstream oPlant("data/plantGenes.txt", ios::out);//init output file for genes

	for(int i = 0; i < mapSize; i++){
		for(int j = 0; j < 20; j++){
			oPlant << plants[i].genes[j] << ' ';
		}
		oPlant << endl;
	}

	oPlant.close();
	
	cout << "Finished sim" << endl;
	return(0);

}