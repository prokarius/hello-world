# Set all the values as globals because we dont want to pass them
# into each function that we call as arguments
# This just to make it less messy.
n = 0
target = 0
points = []
numpoints = 0

# Function to do n choose k for small k.
# In this question we only need to consider k = 4 and 3 anyways
def choose(n, k):
    out = 1
    divide = 1
    while k > 0:
        out *= n
        divide *= k
        k -= 1
        n -= 1
    return out//divide

# Given x additional points on n segments, find the max number of intersections
def findIntersection(n, x):
    global points
    # The idea is that we should spread out all the points evenly.
    # That will give the largest number of intersection point.
    points = [x//n] * n
    for i in range(x % n):
        points[i] += 1

    # The absolute number of additional points to be generated is xC4.
    # This is because every additional point is created using 2 lines.
    # Since we need 4 points to create 2 lines, we can set that as the upper bound.
    totalPoints = choose(x, 4)
    
    # Now what combinations of points do not cause 2 lines to intersect?
    # A) When all 4 points are on the same line segment!
    for i in range(n):
        totalPoints -= choose(points[i], 4)

    # B) When 3 line segments lie on one segment and one lies on another
    for i in range (n):
        ways3 = choose(points[i], 3)
        for j in range(n):
            if i == j: continue
            totalPoints -= ways3 * points[j]

    return totalPoints

# Clever use of Euler's theorem for flat planar graphs:
# #Vertices - #Edges + #Faces = 2
# The idea is to convert all the fence posting to a planar graph
# then we can run Euler's theorem on it.
def check(addpoints):
    # Find out the number of intersecrions of all the posts
    newVertices = findIntersection(numpoints, addpoints)

    # For each additional point, it generates 2 new edges
    newEdges = 2 * newVertices

    totalVertices = newVertices + addpoints + numpoints

    # Find the total number of edges
    # The number of edges is the number of segments on the fencr
    # Plus the number of pairwise edges
    # Plus the number of new edges
    fenceEdges = numpoints + addpoints
    pairwiseEdges = choose(addpoints, 2)
    for i in range (n):
        pairwiseEdges -= choose(points[i], 2)
    totalEdges = fenceEdges + pairwiseEdges + newEdges

    # Find out the total number of edges there is
    # Then we apply Euler's formula here:
    faces = 2 + totalEdges - totalVertices

    return faces <= target

# This is for binary sesrching the range of the input.
# Because python doesnt have the overflow problem (all big integers),
# we can safely just over shoot the correct value without fear of reprecussions.
def binsearch(lo, hi):
    if lo > hi:
        return lo
    mid = lo + (hi - lo)//2
    if check(mid):
        return binsearch(mid+1, hi)
    else:
        return binsearch(lo, mid-1)

def main():
    global n, target, numpoints
    # Read in input
    target = int(input())
    n = int(input())

    # Read in the points
    for i in range(n):
        ph = input().split(' ')
        points.append((int(ph[0]),int(ph[1])))
    numpoints = len(points)

    # Looks like they can give collinear fence posts. Tsk.
    # So we need to put together collinear fence posts and treat them as only 1.
    # Since there will be at most 100 fence posts, we can use remove method.
    candidate = 0
    while candidate < len(points):
        x1 = points[candidate - 2][0]
        y1 = points[candidate - 2][1]
        x2 = points[candidate - 1][0]
        y2 = points[candidate - 1][1]
        x3 = points[candidate][0]
        y3 = points[candidate][1]

        dx1 = x2 - x1
        dy1 = y2 - y1
        dx2 = x3 - x2
        dy2 = y3 - y2

        # Do cross multiply technique to check for collinearity
        if (dx1 * dy2 == dx2 * dy1):
            numpoints -= 1

        candidate += 1

    n = numpoints
    
    # We will do binary search on the range 1 to 2**17
    out = binsearch(0, 2**17)
    print (out)

main()
