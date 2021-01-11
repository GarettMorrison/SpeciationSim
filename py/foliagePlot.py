from PIL import Image
import sys
import math as m
import csv


tick = 0

with open("data/plantFoliageData.txt","r") as inputFile:
	readCSV = csv.reader(inputFile, delimiter = ' ', )
	
	array = []

	for i in readCSV:
		array.append(i)

ticks = len(array)
mapSize = len(array[0])

output = Image.new("RGB",(ticks, mapSize))
pixels = output.load()

for i in range(ticks):
	for j in range(mapSize):
		gVal = 0
		if(int(array[i][j]) > 0):
			gVal = int(array[i][j])*18 + 60
		bVal = 0
		if(gVal > 255):
			bVal = gVal - 255
			gVal = 255
		# print(newVal)
		pixels[i, j] = (0, bVal, gVal)


scale = m.ceil(1000/mapSize)
output = output.resize((ticks*scale, mapSize*scale))
print("foliagePlot output")
output.save("data/foliagePlot.png")

# print(array)