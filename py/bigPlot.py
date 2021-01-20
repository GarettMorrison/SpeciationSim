from PIL import Image
import sys
import math as m
import csv


color = Image.open("data/colorPlot.png")
height = Image.open("data/heightPlot.png")
foliage = Image.open("data/foliagePlot.png")

output = Image.new('RGB', (color.width, color.height*3+20))
output.paste(color, (0,0))
output.paste(height, (0,color.height +10))
output.paste(foliage, (0,color.height*2 +20))
output.save("data/bigPlot.png")

print("bigPlot output")