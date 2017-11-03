# Made by Christian Oliveros on the 11/03/17 for Service Robotics

# Used Imports
from PIL import Image
import os

# Constants
map_types = {"wall" : 0, "walk" : 1, "entrance" : 2, "target" : 3, "target_line" : 4}
# this names will be used to get their respective colors

final_map = [] # final loaded map
color_mapper = {} # map from color to type
type_mapper = {} # map from type to color
width = 0
height = 0
start_pos = (0,0)
target_pos = [] # target positions
target_line_pos = [] # line where there could be a target 
mov_arr = [(0, 1), (1, 0), (0, -1), (-1, 0)] # movement array
pixel_size = (1, 1) # (width, height) of a pixel in real world measures
infinity = 10000000 # infinity for dijkstra
infinity_post = -1 # infinity for other calculations

picture_folder = "Pictures"



def getMap():
	global final_map, color_mapper, type_mapper, width, height, start_pos, target_pos, target_line_pos

	def colorGetter(color):
		return (color[0], color[1], color[2])

	def getColor(name):
		path = os.path.join(picture_folder, name+".png")
		im = Image.open(path)
		color = colorGetter(list(im.getdata())[0]) # from the first pixel
		im.close()
		return color

	for maptype, number in map_types.items():
		color = getColor(maptype)
		color_mapper[color] =  number # map from color to type
		type_mapper[number] = color # map from type to color

	map_file = "map.png"
	map_path = os.path.join(picture_folder, map_file)

	im = Image.open(map_path)
	width, height = im.size
	color_map = list(im.getdata())
	counter = 0
	for y in range(height):
		final_map.append([])
		for x in range(width):
			color = colorGetter(color_map[counter])
			number = color_mapper[color]
			final_map[y].append(number)
			if number == map_types["entrance"]:
				start_pos = (x, y)
			elif number == map_types["target"]:
				target_pos.append((x, y))
			elif number == map_types["target_line"]:
				target_line_pos.append((x, y))
			counter += 1

	im.close()


def getNeighbors(pos):
	neighbors = []
	for mov in mov_arr:
		x = pos[0] + mov[0]
		y = pos[1] + mov[1]
		if 0 <= x and 0 <= y and x < width and y < height and final_map[y][x] != map_types["wall"]:
			neighbors.append((x,y))
	return neighbors


def getDist(pos, otherPos):
	# We moved in y direction if the x direction stayed the same
	if pos[0] == otherPos[0]:
		return pixel_size[1]
	return pixel_size[0]


def dijkstra():
	dist = {}
	prev = {}
	Q = set()
	for y in range(height):
		for x in range(width):
			current_pos = (x, y)
			dist[current_pos] = infinity # distance, equivalent to infinity
			prev[current_pos] = None
			Q.add(current_pos)

	dist[start_pos] = 0
	while len(Q) != 0:
		u = min(Q, key=lambda x: dist[x]) # not the fastest way but works
		Q.remove(u) 
		for v in getNeighbors(u):
			alt = dist[u] + getDist(u, v)
			if alt < dist[v]:
				dist[v] = alt
				prev[v] = u

	for key, val in dist.items():
		if val == infinity:
			dist[key] = infinity_post

	return dist, prev


def getPath(prev, target):
	S = []
	u = target
	while u is not None:
		S.append(u)
		u = prev[u]
	return S[::-1]


def drawDistanceMap(dist):
	close_color = (0, 0, 255)
	far_color = (255, 0, 0)
	impossible_color = (100, 100, 100)
	max_distance = min(dist.items(), key=lambda x: -dist[x[0]])[1]

	def interpolateColor(pos):
		if pos == start_pos:
			return type_mapper[map_types["entrance"]]
		distance = dist[pos]
		if distance == infinity_post:
			wall_number = map_types["wall"]
			if final_map[pos[1]][pos[0]] != wall_number:
				return impossible_color
			return type_mapper[wall_number]
		t = float(distance) / float(max_distance)

		def interpolate(i):
			return int(float(far_color[i]) * t + (1.0 - t) * float(close_color[i]))

		return (interpolate(0), interpolate(1), interpolate(2))

	color_image = Image.new("RGB", (width, height))
	for y in range(height):
		for x in range(width):
			pos = (x,y)
			color_image.putpixel(pos, interpolateColor(pos))

	color_image.save(os.path.join(picture_folder, "distance_map.png"), "png")
	color_image.close()


def main():
	getMap()
	print("Map")
	for y in range(height):
		print(final_map[y])

	print("Start Position: ", start_pos)

	print("Calculating shortest paths")
	dist, prev = dijkstra()
	print("Calculations Done")

	print("Printing Distance Map on Console")
	for y in range(height):
		line = ""
		for x in range(width):
			line += str(dist[(x,y)]) + " "
		print(line)
	print("Printing Distance Map on Console Done")

	print("Saving distance map as image in Pictures folder")
	drawDistanceMap(dist)
	print("Saving distance map as image in Pictures folder Done")

	target_line_farthest = min(target_line_pos, key=lambda x: -dist[x])
	target_line_closest = min(target_line_pos, key=lambda x: dist[x])

	final_targets = [(x, dist[x], 0) for x in target_pos] # 0 at the end means its not a line target
	final_targets.append((target_line_closest, dist[target_line_farthest], 1)) # 1 at the end means its a line target
	ordered_target_pos = sorted(final_targets, key=lambda x: -x[1])

	print("Paths Order")
	for x in ordered_target_pos:
		print("Point: %s, Distance %s, Type: %s" % (x[0], x[1], x[2]))
		print(getPath(prev, x[0]))
		print("")



if __name__ == '__main__':
	main()