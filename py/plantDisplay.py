from PIL import Image
import sys
import math as m
import csv

tick = 0

#Open and process file
with open("data/plantGenes.txt","r") as inputFile:
	readCSV = csv.reader(inputFile, delimiter = ' ', )
	
	array = []

	for i in readCSV:
		array.append(i)

plants = len(array)
genes = len(array[0]) -1 #-1 to account for the space at the end of each row

#Remove dead creatures
for i in range(plants-1, -1, -1):

	strTest = ''.join(array[i])
	strComp = ''.join(["0"]*genes)
	if strTest == strComp:
		array.pop(i)

#Make image output
plants = len(array)
output = Image.new("RGB",(plants, genes -2))
pixels = output.load()

#Print Codes
for i in range(plants):
	pixels[i, 0] = (int(array[i][0]), int(array[i][1]), int(array[i][2]))
	for j in range(3,genes):

		if j % 3 == 0:
			pixels[i, j -2] = (int(array[i][j]), 0, 0)
		if j % 3 == 1:
			pixels[i, j -2] = (0, int(array[i][j]), 0)
		if j % 3 == 2:
			pixels[i, j -2] = (0, 0, int(array[i][j]))

output = output.resize((plants*8, (genes-2)*8))
print("plantDisplay output")
output.save("data/plantDisplay.png")

# print(array)