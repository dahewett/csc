import sys
import math
import Line_Point
 
'''
purpose
    write to stdout a triangle that is recursive with variable n entered on cmd line
preconditions
     n >= 0
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
     
#Draws the triangle
def draw_tri(L, H, x0, y0):
 
    p0 = Line_Point.Point(x0, y0)
    p1 = Line_Point.Point((x0 - (L/2)), (y0 + H))
    p2 = Line_Point.Point((x0 + (L/2)), (y0 + H))
     
    print 'line', Line_Point.Line(p0, p1)
    print 'line', Line_Point.Line(p1, p2)
    print 'line', Line_Point.Line(p2, p0)
    return
     
#Recursive call n times, creates 3(n-1) triangles for each n
def tri_rec(n, L, H, x0, y0):
    # make sure n is a positive integer
    n = n - 1
    if (n <= 0):
        return
    #Top
    draw_tri(L/2, H/2, x0, y0)
    #bottom left
    draw_tri(L/2, H/2, (x0 - (L/2)), (y0 - H))
    #bottom right
    draw_tri(L/2, H/2, (x0 + (L/2)), (y0 - H))
     
    #recursivle call tri_rec to draw 
    tri_rec(n, L/2, H/2, x0, (y0 + (H/2)))
    tri_rec(n, L/2, H/2, (x0 - (L/2)), (y0 - (H/2)))
    tri_rec(n, L/2, H/2, (x0 + (L/2)), (y0 - (H/2)))
    return
     
# THIS IS THE MAIN METHOD
# generate first base triangle 
Ax = float(-250)
Ay = float(-250)
Cx = float(250)
Cy = float(-250)
Bx = float(0)
By = float(183)
 
p0 = Line_Point.Point(Ax, Ay)
p1 = Line_Point.Point(Bx, By)
p2 = Line_Point.Point(Cx, Cy)
  
print 'line', Line_Point.Line(p0, p1)
print 'line', Line_Point.Line(p1, p2)
print 'line', Line_Point.Line(p2, p0)
 
# if n is greater than 1 draws first upside down triangle and then calls the tri_rec function
if (n >= 1) :
    Ax0 = ((Ax - Bx)/2)
    Ay0 = (By + ((Ay - By)/2))
    Bx0 = ((Cx - Bx)/2)
    By0 = (Cy +((By - Cy)/2))
    Cx0 = ((Ax + Cx)/2)
    Cy0 = (Cy+((Ay - Cy)/2))
     
    p0 = Line_Point.Point(Ax0, Ay0)
    p1 = Line_Point.Point(Bx0, By0)
    p2 = Line_Point.Point(Cx0, Cy0)
     
    print 'line', Line_Point.Line(p0, p1)
    print 'line', Line_Point.Line(p1, p2)
    print 'line', Line_Point.Line(p2, p0)
     
    L = (Bx0 - Ax0)
    H = (By0 - Cy0)
    x0 = Cx0
    y0 = Ay0
     
    # Call the recursive function
    tri_rec(n, L, H, x0, y0) 