from PIL import Image
import sys
import math as m
import csv

tick = 0

fileOut = sys.argv[1]

with open("data/plantHeightData.txt","r") as inputFile:
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
		rVal = 0
		if(int(array[i][j]) > 0):
			rVal = int(array[i][j])*18 + 60
		bVal = 0
		if(rVal > 255):
			bVal = rVal - 255
			rVal = 255
		# print(newVal)
		pixels[i, j] = (rVal, bVal, 0)



scale = m.ceil(1000/mapSize)
output = output.resize((ticks*scale, mapSize*scale))
print("heightPlot output")
output.save(fileOut)

# print(array)