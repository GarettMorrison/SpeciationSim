from PIL import Image
import sys
import math as m
import csv

tick = 0

with open("data/plantGenes.txt","r") as inputFile:
	readCSV = csv.reader(inputFile, delimiter = ' ', )
	
	array = []

	for i in readCSV:
		array.append(i)

plants = len(array)
genes = len(array[0]) -1 #-1 to account for the space at the end of each row

output = Image.new("RGB",(plants, genes -2))
pixels = output.load()

for i in range(plants):
	print(''.join(array[i])
	if ''.join(array[i]) == ['0']*genes:
		print("AAAAA")
	pixels[i, 0] = (int(array[i][0]), int(array[i][1]), int(array[i][2]))
	for j in range(3,genes):
		pixels[i, j -2] = (int(array[i][j]), 0, 0)

output = output.resize((2000, int(2000*(genes/plants))))
print("plantDisplay output")
output.save("data/plantDisplay.png")

# print(array)