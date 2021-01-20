from PIL import Image
import sys
import math as m
import csv

tick = 0

def averageWrap(in1, in2, maxVal): #Get average accounting for wraparound
	#Order nums
	small = in1
	big = in2
	if(in1 > in2):
		big = in1
		small = in2
	

	val = 0
	if(big - small < small + maxVal - big):
		val = (big - small)/2 + small
	
	else:
		val = (small + maxVal - big)/2 + big
	

	if(val > maxVal):
		val -= maxVal
	

	return val

def diffWrap(in1, in2, maxVal): #Get difference accounting for wrapping
	#Order nums
	small = in1
	big = in2
	if(in1 > in2):
		big = in1
		small = in2
	

	val = 0
	if(big - small < small + maxVal - big):
		val = big - small
	
	else:
		val = small + maxVal - big
	

	return val


def geneDiff(gene1, gene2, len): #Calculate total differences between genes
	# print(gene1)
	# print(gene2)
	# print(' ')
	diffSum = 0
	for i in range(0, len):
		diffSum += abs(diffWrap(gene1[i], gene2[i], 255))
	return(diffSum)






#Starting actual code

#get arguments
geneCount = int(sys.argv[2])
fileOut = sys.argv[1]


#Open and process file
with open("data/plantGenes.txt","r") as inputFile:
	readCSV = csv.reader(inputFile, delimiter = ' ', )
	
	array = []

	for i in readCSV:
		i.remove('')
		arrInsert = [int(j) for j in i]
		if sum(arrInsert) > 0:
			array.append(arrInsert)

plants = len(array)
genes = len(array[0]) #-1 to account for the space at the end of each row

#array is array of all plant genes, [plantID][gene]


# for i in range(0, plants):
# 	diff =geneDiff(array[0], array[i], geneCount)
# 	print(str(i) + ' ' + str(diff))


# #Make image output
output = Image.new("RGB",(plants, plants))
pixels = output.load()


minimum = 0
maximum = 0
#Get max
for i in range(plants):
	for j in range(plants):
		if geneDiff(array[i], array[j], geneCount) > maximum:
			maximum = geneDiff(array[i], array[j], geneCount)


#Make image
for i in range(plants):
	for j in range(plants):
		blue = geneDiff(array[i], array[j], geneCount) * (510/maximum)
		green = 0
		if blue > 255:
			green = (blue-255)
			blue = 255

		pixels[i, j] = (0, int(green), int(blue))

output = output.resize((plants*4, plants*4))
print("geneDiff output")
output.save(fileOut)

# # print(array)