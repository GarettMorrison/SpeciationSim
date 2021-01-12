This is an evolution simulator with an objective of evolving distinct species of plants. 
The sim itself is the C++ program in /sim, and it outputs various data into /data. 
There are several python scripts in /py that create visualizations, also in /data.
Everything can be run with run.sh, which will compile, run, and visualize the sim. 

The genetics are reasonably simple: a string of ints from 0-255.
New plants are born from a combination of the genes of 2 parents
There are only 7 that are implemented currently. 

1-3 Are RGB values, currently useful only for approximating species
4 is height. Plants can cast shadows on nearby plants and reduce their food intake. 
5 is foliage It increases food production, but can be expensive when combined with high height.
6 is roots. The top half of the map is designated as sandy, where it is advantageos to have roots.
7 is splitFood. It determines how much food a plant will stockpile before procreating. 


TODO:
Implement sexual selection
Implement terrain
Implement creatures