def DFS (x, y):
    global visited, colour, cur, d
    cur += 1
    queue = []
    queue.append((x,y))
    while len(queue) != 0:
        coords = queue.pop()
        z = coords[0]*d[1]+coords[1]
        if not visited[z]:
            visited[z] = True
            colour[z] = cur
            if coords[0]<d[0]-1:
                if grid[z] == grid[z+d[1]]:
                    queue.append ((coords[0]+1,coords[1]))
            if coords[0]>0:
                if grid[z] == grid[z-d[1]]:
                    queue.append ((coords[0]-1,coords[1]))
            if coords[1]<d[1]-1:
                if grid[z] == grid[z+1]:
                    queue.append ((coords[0],coords[1]+1))
            if coords[1]>0:
                if grid[z] == grid[z-1]:
                    queue.append ((coords[0],coords[1]-1))

n = raw_input ()
d = [int (x) for x in n.split()]
grid = ""
visited = [False for x in range(1000005)]
colour = [0 for x in range (1000005)]
cur = 0
for i in range (d[0]):
    q = raw_input ()
    grid += q
nqueries = int (raw_input ())
while (nqueries >0):
    m = raw_input()
    query = [int(x)-1 for x in m.split ()]
    a = query[0]*d[1]+query[1]
    b = query[2]*d[1]+query[3]
    if (colour [a] == 0):
        DFS(query[0], query [1])
    if (colour[b] == 0):
        DFS(query[2], query [3])
    if (colour [a] == colour [b]):
        if grid [a] == "0":
            print ("binary")
        else:
            print ("decimal")
    else:
        print ("neither")
nqueries -= 1
