from PIL import Image
import sys
import math as m
import csv


tick = 0


#get arguments
fileOut = sys.argv[1]

with open("data/plantColorData.txt","r") as inputFile:
	readCSV = csv.reader(inputFile, delimiter = ' ', )
	
	array = []

	for i in readCSV:
		i.remove('')
		arrInsert = [int(j) for j in i]
		array.append(arrInsert)

ticks = len(array)
mapSize = m.floor(len(array[0])/3)

output = Image.new("RGB",(ticks, mapSize))
pixels = output.load()

for i in range(ticks):
	for j in range(mapSize):
		pixels[i, j] = (array[i][j*3], array[i][j*3+1], array[i][j*3+2])


scale = m.ceil(1000/mapSize)
output = output.resize((ticks*scale, mapSize*scale))
print("colorData output")
output.save(fileOut)

# print(array)