import sys
import math
import Line_Point_colour

'''
purpose
	write to stdout a triangle that is recursive with variable n and up to four colours taken with the last entered continuing for rest of the smaller recursive triangles; all entered on cmd line.
preconditions
	 n >= 0, n < 11; the colour must begin with capital and be accepted by lines_to_svg_colour

FORMAT: python colour_triangle_generator.py (n-integer [>= 0 & < 11]) (c1-Colour [String with capital first letter eg. Red]) c2 c3 c4 
'''

# process the command line arguments
if len(sys.argv) < 2:
	print >> sys.stderr, 'Syntax: ' + sys.argv[0] + ' need at least input int(n)'
	sys.exit(1)
i = len(sys.argv) -2

try:
	n = int(sys.argv[1])
	if (n >= 11 or n < 0):
		print >> sys.stderr, 'Syntax: ' + sys.argv[0] + ' n must be between the range of 0 - 10'
		sys.exit(3)
	
	
	if (i >= 0):
		if (i == 0):
			c = ['Black']
			c1 = 'Black'
		else:
			c1 = str(sys.argv[2])
			c = sys.argv[2:]
		try:
			colours_file = open('css_colours.txt', 'r')
			for c in colours_file:
				c = sys.argv[2:]
		except IOError:
			print >> sys.stderr, 'Cannot open file: css_colours.txt'
			sys.exit(4)

			
except ValueError:
	print >> sys.stderr, 'Syntax: ' + sys.argv[0] + ' Value Error'
	sys.exit(5)
	
#Draws the triangle
def draw_tri(L, H, x0, y0, c):

	p0 = Line_Point_colour.Point(x0, y0)
	p1 = Line_Point_colour.Point((x0 - (L/2)), (y0 + H))
	p2 = Line_Point_colour.Point((x0 + (L/2)), (y0 + H))
	
	print 'line', Line_Point_colour.Line(p0, p1, c)
	print 'line', Line_Point_colour.Line(p1, p2, c)
	print 'line', Line_Point_colour.Line(p2, p0, c)
	return
	
#Recursive call n times, creates 3(n-1) triangles for each n
def tri_rec(i, n, L, H, x0, y0, c):
	# make sure n is a positive integer
	n = n - 1
	if (n <= 0):
		return
	#Top
	draw_tri(L/2, H/2, x0, y0, c[i%len(c)])
	#bottom left
	draw_tri(L/2, H/2, (x0 - (L/2)), (y0 - H), c[i%len(c)])
	#bottom right
	draw_tri(L/2, H/2, (x0 + (L/2)), (y0 - H), c[i%len(c)])
	
	#recursivle call tri_rec to draw 
	tri_rec(i + 1, n, L/2, H/2, x0, (y0 + (H/2)), c)
	tri_rec(i + 1, n, L/2, H/2, (x0 - (L/2)), (y0 - (H/2)), c)
	tri_rec(i + 1, n, L/2, H/2, (x0 + (L/2)), (y0 - (H/2)), c)
	return
	
# THIS IS THE MAIN METHOD
# generate first base triangle 
Ax = float(-250)
Ay = float(-250)
Cx = float(250)
Cy = float(-250)
Bx = float(0)
By = float(183)

p0 = Line_Point_colour.Point(Ax, Ay)
p1 = Line_Point_colour.Point(Bx, By)
p2 = Line_Point_colour.Point(Cx, Cy)


print 'line', Line_Point_colour.Line(p0, p1, c1)
print 'line', Line_Point_colour.Line(p1, p2, c1)
print 'line', Line_Point_colour.Line(p2, p0, c1)

# if n is greater than 1 draws first upside down triangle and then calls the tri_rec function
if (n >= 1) :
	Ax0 = ((Ax - Bx)/2)
	Ay0 = (By + ((Ay - By)/2))
	Bx0 = ((Cx - Bx)/2)
	By0 = (Cy +((By - Cy)/2))
	Cx0 = ((Ax + Cx)/2)
	Cy0 = (Cy+((Ay - Cy)/2))
	
	p0 = Line_Point_colour.Point(Ax0, Ay0)
	p1 = Line_Point_colour.Point(Bx0, By0)
	p2 = Line_Point_colour.Point(Cx0, Cy0)
	
	if len(c) == 0:
		c = ['Black']
	print 'line', Line_Point_colour.Line(p0, p1, c[1%len(c)])
	print 'line', Line_Point_colour.Line(p1, p2, c[1%len(c)])
	print 'line', Line_Point_colour.Line(p2, p0, c[1%len(c)])
	
	L = (Bx0 - Ax0)
	H = (By0 - Cy0)
	x0 = Cx0
	y0 = Ay0
	
	# Call the recursive function
	tri_rec(2, n, L, H, x0, y0, c) 

	
