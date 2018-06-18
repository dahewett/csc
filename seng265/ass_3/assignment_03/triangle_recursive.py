import sys
import math
import Line_Point

'''
purpose
	write to stdout a triangle with s sides and first vertex at (x0,y0)
preconditions
	None
'''

# process the command line arguments
if len(sys.argv) != 2:
	print >> sys.stderr, 'Syntax: ' + sys.argv[0] + ' Only 1 input(n)'
	sys.exit(1)
try:
	n = int(sys.argv[1])
	
except ValueError:
	print >> sys.stderr, 'Syntax: ' + sys.argv[0] + 'Value Error'
	sys.exit(2)

# generate first base triangle 
#x0 = float(sys.argv[1])
#y0 = float(sys.argv[2])
Ax = float(-250)
Ay = float(-250)
Cx = float(250)
Cy = float(250)
Bx = float(0)
By = float(((Cx - Ax)*(math.tan((math.pi/3)))

p0 = Line_Point.Point(Ax, Ay)
p1 = Line_Point.Point(Bx, By)
p2 = Line_Point.Point(Cx, Cy)
 
print 'line', Line_Point.Line(p0, p1)
print 'line', Line_Point.Line(p1, p2)
print 'line', Line_Point.Line(p2, p0)

'''
s = 3
x0 = 0
y0 = 250
central_angle = 2 * math.pi / s
p0 = Line_Point.Point(x0, y0)
while side > 0:
	p1 = Line_Point.Point(p0.x, p0.y)
	p1.rotate(central_angle)
	print 'line', Line_Point.Line(p0, p1)
	p0 = p1
	s = s - 1
'''