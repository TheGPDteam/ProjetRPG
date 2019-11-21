#! /usr/bin/env python3
# coding: utf-8

import sys, json, os

def getTileId(id):
	"""
        Get the absolute identifier of the tile of a tileset in case of multiple tilesets

        :param id: tile id given by Tiled
        :return: new tile id specific to current tileset
        :rtype: int
        """
	newTileId = id
	for a in range(1, len(mapData["tilesets"])):
		firstTile = mapData["tilesets"][a]["firstgid"]
		if (id >= firstTile):
			newTileId = id - firstTile +1
	return newTileId

# Check if there where enough passed arguments
if (len(sys.argv) != 2):
	print("/!\\ Missing arguments : run '" + sys.argv[0] + " {INPUT_MAP_FILE}'")
	sys.exit()

inputFile = sys.argv[1]		# We store name of file to open
outputFile = "output/" + os.path.splitext(os.path.basename(inputFile))[0] + ".txt"

# Try to load map data from the file given in input
try:
	mapData= json.load(open(inputFile))
except FileNotFoundError:
	print("/!\\ Input file not found !")
	sys.exit()

# Warn the user if there is less than two layers in map data
if len(mapData["layers"]) < 2:
	print("/!\\ Warning : Missing layers : there is only " + str(len(mapData["layers"])) + " layer(s) in map file.")
	print("    Map file must have 2 layers : one layer named 'sol', and another named 'decoration'")

# Create the base map object
map = {
	"nom": str(input("[?] What is the name of this map (press <Enter> to get it from filename) ? ") or outputFile.split("/")[-1].split(".")[-2]),
	"dimensions": (mapData["layers"][0]["width"], mapData["layers"][0]["height"]), 
	"sol": [],
	"decoration": []
}

# Add initial map data
mapText = "#Nom " + map["nom"] + "\n#Dimensions " + str(map["dimensions"][0]) + " " + str(map["dimensions"][1]) + "\n"

for layer in mapData["layers"]:

	if "data" in layer:  # Check if it's a layer of blocks

		lines = []
		for i in range(0, layer["height"]):
			line = []
			for a in range(0, layer["width"]):
				line.append(getTileId(layer["data"][layer["width"] * i + a]))
			lines.append(line)

		if layer["name"] == "sol":
			mapText+= "#Sol\n"
			map["sol"].append(lines)
		elif layer["name"] == "decoration":
			mapText+= "#Decoration\n"
			map["decoration"].append(lines)

		for key, line in enumerate(lines):
			for index, tile in enumerate(line):
				if index < len(line)-1:
					mapText+= str(tile) + " "
				else:
					mapText+= str(tile) + "\n"

# Write map data to desired output file
with open(outputFile, 'w') as outfile:
	outfile.write(mapText)
	outfile.close()

# Show map data to the user
print(mapText)
