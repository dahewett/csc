'''
purpose
	Read a from stdin: a shape consisting of a list of lines.
	Write to stdout number_of_rings rings.
	Each ring consists of the lines in the shape arranged in a ring around the origin.
preconditions
	stdin contains a legal line file
'''

import sys
import copy
import math
import Line_Point

'''
purpose
	write to stdout a ring consisting of n copies of the shape in lines,
	translated by vertically by delta_y
preconditions
	lines is a list of Line objects
	n > 0
'''
def draw_ring(lines, delta_y, n):
	new_lines = copy.deepcopy(lines)

	for line in new_lines:
		line.translate(0.0, delta_y)
		print 'line', line

	for i in range(n-1):
		for line in new_lines:
			line.rotate(2*math.pi/n)
			print 'line', line

'''
purpose
	convert the lines in stdin to a list of Line objects
	return the list
preconditions
	file_object is a reference to a readable file containing legal lines
'''
def load_line_file(file_object):
	line_objects = [ ]
	for line in file_object:
		# convert text line to a Line object
		line_object = line.split()
		point0 = Line_Point.Point(float(line_object[1]), float(line_object[2]))
		point1 = Line_Point.Point(float(line_object[3]), float(line_object[4]))
		line_object = Line_Point.Line(point0, point1)

		line_objects.append(line_object)
	
	return line_objects

# ***** process command line arguments

if len(sys.argv) != 2:
	print >> sys.stderr, 'Syntax: ' + sys.argv[0] + ' number_of_rings'
	sys.exit(1)
try:
	number_of_rings = int(sys.argv[1])
except ValueError:
	print >> sys.stderr, 'Syntax: ' + sys.argv[0] + ' number_of_rings'
	sys.exit(2)
if number_of_rings < 1 or number_of_rings > 5:
	print >> sys.stderr, 'Syntax: ' + sys.argv[0] + ' number_of_rings'
	sys.exit(3)

L = load_line_file(sys.stdin)

# ***** generate the rings

ring_parameters = [
#	delta_y		number of items in ring
	[0.0,		1],
	[50.0,		6],
	[100.0,		12],
	[150.0,		18],
	[200.0,		24],
]

for i in range(number_of_rings):
	draw_ring(L, ring_parameters[i][0], ring_parameters[i][1])
