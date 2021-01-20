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
# geneCount = int(sys.argv[2])
# fileOut = sys.argv[1]


#Open and process file
with open("data/plantGenes.txt","r") as inputFile:
	readCSV = csv.reader(inputFile, delimiter = ' ', )
	
	array = []

	for i in readCSV:
		i.remove('')
		arrInsert = [int(j) for j in i]
		if sum(arrInsert) > 0:
			array.append(arrInsert)

# plants = len(array)
genes = len(array[0]) #-1 to account for the space at the end of each row

#array is array of all plant genes, [plantID][gene]


#Convert num into what is selected
check = [
	"exact match",
	"shortest diff wrap",
	"shortest diff linear",
	"longest diff wrap",
	"longest diff linear",
	"within 2",
	"within 5",
	"within 10",
	"within 50",
	"within 100"
]

trait = [
		"Rgb",
		"rGb",
		"rgB",
		"height",
		"foliage",
		"roots"
]

sumThings = [0,0,0,0,0]

# #Make image output
with open("data/legibleGenetics.txt","w") as out:
	for plant in array:
		out.write("RGB:" + str(plant[0]) + '-' + str(plant[1]) + '-' + str(plant[2]))

		i = 3
		while i < genes-2:
			select = plant[i]
			if select == 0:
				break
			# print(select)
			select = m.floor(select/52)
			# print(select)
			sumThings[select]+=1
			if select == 0:
				i += 1
				out.write("\n   Height:" + str(m.floor(plant[i]/10 +1)))
			elif select == 1:
				i += 1
				out.write("\n   Foliage:" + str(m.floor(plant[i]/10 +4)))
			elif select == 2:
				i += 1
				out.write("\n   Roots:" + str(m.floor(plant[i] > 127)))
			elif select == 3:
				i += 1
				out.write("\n   SplitFood:" + str(m.floor(plant[i]*2)))
			elif select == 4:
				i += 1
				out.write("\n   mateSel")
				out.write("\n       Weight:" + str(m.floor(plant[i] % 5+1)))
				out.write("\n       Check:" + check[plant[i] % 5+1])#------
				i += 1
				out.write("\n       Trait:" + trait[(plant[i] % 5)])
				out.write("\n       Target:" + str(m.floor(plant[i])))#------
			i += 1
		out.write('\n\n') #Endline

out.close()
# print(sumThings)



# # print(array)