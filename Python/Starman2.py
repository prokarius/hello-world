"""
Given N points, find the rectangle with the smallest width that covers all points.

Input:
1 line containing N
N lines of x and y coords

Output:
1 number to 6 dp
"""

# Scan in input
N = int(raw_input())
dlist = []
for i in range(N):
    ph = [float(x) for x in raw_input().split(' ')]
    dlist.append((ph[0], ph[1]))

# I just pulled this off wikibooks haha shit
def convex_hull(points):
    """Computes the convex hull of a set of 2D points.

    Input: an iterable sequence of (x, y) pairs representing the points.
    Output: a list of vertices of the convex hull in counter-clockwise order,
      starting from the vertex with the lexicographically smallest coordinates.
    Implements Andrew's monotone chain algorithm. O(n log n) complexity.
    """

    # Sort the points lexicographically (tuples are compared lexicographically).
    # Remove duplicates to detect the case we have just one unique point.
    points = sorted(set(points))

    # Boring case: no points or a single point, possibly repeated multiple times.
    if len(points) <= 1:
        return points

    # 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
    # Returns a positive value, if OAB makes a counter-clockwise turn,
    # negative for clockwise turn, and zero if the points are collinear.
    def cross(o, a, b):
        return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])

    # Build lower hull 
    lower = []
    for p in points:
        while len(lower) >= 2 and cross(lower[-2], lower[-1], p) <= 0:
            lower.pop()
        lower.append(p)

    # Build upper hull
    upper = []
    for p in reversed(points):
        while len(upper) >= 2 and cross(upper[-2], upper[-1], p) <= 0:
            upper.pop()
        upper.append(p)

    # Concatenation of the lower and upper hulls gives the convex hull.
    # Last point of each list is omitted because it is repeated at the beginning of the other list. 
    return lower[:-1] + upper[:-1]

# LOL I hope this works
chull = convex_hull(dlist)

# For each side of the convex hull, find the furthest point
# This is using rotating calipers
def furthest (a, b):
    # a and b are vectors
    # returns d**2
    dot = (a[0]*b[0] + a[1]*b[1])/(a[0]*a[0] + a[1]*a[1])
    c0 = b[0] - dot*a[0]
    c1 = b[1] - dot*a[1]
    return c0*c0 + c1*c1

def min(a,b):
    if a < b:
        return a
    else:
        return b

best = 99999999999999999999999999
last = 99999999999999999999999999
curr = 0
head = 2
l = len(chull)
i = 0

if l == 2:
    best = 0
    l = 0

while i < l:
    if head%l == i+1:
        head = (head + 1)%l
    a = (-chull[(i+1)%l][0]+chull[i][0], -chull[(i+1)%l][1]+chull[i][1])
    b = (-chull[(i+1)%l][0]+chull[head][0], -chull[(i+1)%l][1]+chull[head][1])
    new = furthest(a, b)
    if new >= curr:
        curr = new
        head = (head + 1)%l
    else:
        best = min(best, curr)
        head = (head - 1)
        i += 1
        curr = 0

print '{0:.6f}'.format(best**0.5)
