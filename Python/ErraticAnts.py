import collections

def code():
    empty = raw_input()
    numstep = int(raw_input())
    if numstep == 0:
        return 0
    x = y = 60 #Start pos
    enc = {} #Hashing each position of the graph, save space!
    ver = 0 #Part of the hash
    adj = [set() for x in range (65)]
    output = [-1 for x in range(65)]
    for i in range(numstep):
        curr = x*60 + y
        q = raw_input()
        if q == "S":
            y -= 1
        elif q == "N":
            y += 1
        elif q == "W":
            x -= 1
        elif q == "E":
            x += 1
        now = x*60 + y
        try:
            curr = enc[curr]
        except (KeyError):
            enc[curr] = ver
            curr = ver
            ver += 1
        try:
            now = enc[now]
        except (KeyError):
            enc[now] = ver
            now = ver
            ver += 1
        adj[curr].add(now)
        adj[now].add(curr)

    # THE ADJLIST IS DONE HERE!

    dfs = collections.deque()
    dfs.append(0)
    visited = set([0])
    while len(dfs) != 0:
        h = dfs.popleft()
        if h == now:
            break
        for j in adj[h]:
            if j not in visited:
                visited.add(j)
                output[j] = h
                dfs.append(j)
    
    # I THINK THIS IS DFS

    ans = 0
    while (now != 0):
        now = output[now]
        ans += 1
    return ans

N = int(raw_input())
casenum = 0
while casenum < N:
    print code ()
    casenum += 1


##############################
##                          ##
##  Erratic Ants Incorrect  ##
##                          ##
##############################
"""

def code():
    empty = raw_input()
    numstep = int(raw_input())
    dijk = []
    placehold = []
    x = 0
    y = 0
    steps = 0
    for i in range (3):
        placehold.append (-1)
    for i in range (3):
        dijk.append (list(placehold))
    (dijk [0])[0] = 0
    while numstep > 0:
        dire = raw_input()
        numstep -= 1
        if dire == "N":
            y += 1
        elif dire == "S":
            y -= 1
        elif dire == "E":
            x += 1
        elif dire == "W":
            x -= 1
        steps += 1
        if (dijk [x])[y] == -1:
            (dijk [x])[y] = steps
        elif (dijk[x])[y] > steps:
            (dijk [x])[y] = steps
        else:
            steps = (dijk[x])[y]
        for i in dijk:
            print i
        
    print steps

N = int(raw_input())
casenum = 0
while casenum < N:
    code ()
    casenum += 1

"""
