"""

####################
####################
##                ##
##      Ants      ##
##                ##
####################
####################

def code ():
    N = raw_input()
    datalist = [int(x) for x in N.split(' ')]
    if datalist [1] == 1:
        Q = int(raw_input())
        antleft = Q
        antright = datalist [0] - Q
        fastest = min(antleft, antright)
        slowest = max(antleft, antright)
    else:
        numant = 0
        antlist = []
        while len(antlist) != datalist[1]:
            Q = raw_input()
            appendant = [int(x) for x in Q.split(' ')]
            antlist += appendant

        antlist.sort()

        slowest = max(datalist[0] - antlist[0], antlist[-1])

        middle = datalist[0]/2
        newlistleft = []
        antright = 0
        for i in antlist:
            if i < middle:
                newlistleft.append (i)
            else:
                antright = datalist[0] - i
                break
        antleft = newlistleft[-1]
        fastest = max(antleft, antright)

    print str(fastest) + " " + str(slowest)

numtest = int(raw_input())
while numtest > 0:
    code ()
    numtest -= 1
    
"""



####################
####################
## Andrew the Ant ##
####################
####################

"""

import sys

def code(N):
    datalist = [int(x) for x in N.split(' ')]
    datalist[0] *= 2
    leftants = []
    rightants = []
    for i in range (datalist[1]):
        ant = raw_input()
        datant = ant.split(' ')
        if datant [1] == "L":
            leftants.append(int(datant[0])*2)
        else:
            rightants.append(int(datant[0])*2)
    leftants.sort()
    rightants.sort()
    rightants.reverse()
    if len(leftants) == 0:
        outputtime = (datalist[0] - rightants[-1])/2
        outputstr = "The last ant will fall down in " + str(outputtime) + " seconds - started at " + str(rightants[-1]/2) + "."
        return outputstr
    elif len (rightants) == 0:
        outputtime = leftants[-1]/2
        outputstr = "The last ant will fall down in " + str(outputtime) + " seconds - started at " + str(leftants[-1]/2) + "."
        return outputstr
    lastant = max ((datalist[0] - rightants[-1]), leftants[-1])
    dual = (datalist[0] - rightants[-1]) == leftants[-1]
    left = (datalist[0] - rightants[-1]) < leftants[-1]
    outputtime = lastant/2
    leftplace = list (leftants)
    rightplace = list (rightants)
    lefty = not left
    L = leftplace.pop()
    R = rightplace.pop()
    while L > R:
        if left:
            try:
                L = leftplace.pop()
            except (IndexError):
                left = not left
                break
        else:
            try:
                R = rightplace.pop()
            except (IndexError):
                left = not left
                break
        left = not left
    if left:
        antpos = L/2
    else:
        antpos = R/2
    if not dual:
        outputstr = "The last ant will fall down in " + str(outputtime) + " seconds - started at " + str(antpos) + "."
        return outputstr
    else:
        L = leftants.pop()
        R = rightants.pop()
        while L > R:
            if lefty:
                try:
                    L = leftants.pop()
                except (IndexError):
                    lefty = not lefty
                    break
            else:
                try:
                    R = rightants.pop()
                except (IndexError):
                    lefty = not lefty
                    break
            lefty = not lefty
        if lefty:
            antpos2 = L/2
        else:
            antpos2 = R/2
        if antpos > antpos2:
            antpos, antpos2 = antpos2, antpos
        outputstr = "The last ant will fall down in " + str(outputtime) + " seconds - started at " + str(antpos) + " and " + str(antpos2) + "."
        return outputstr
        
N = sys.stdin.readline()

while N:
    print code (N)
    N = sys.stdin.readline()
    


"""

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

"""
##############################
##                          ##
##   Erratic Ants Correct   ##
##                          ##
##############################

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

"""
