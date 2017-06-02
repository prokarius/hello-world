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

def code():
    empty = raw_input()
    numstep = int(raw_input())
    adjlist = []
    visitedlist = []
    placehold = []
    placeholder2 = []
    for i in range (3):
        placehold.append (False)
        placeholder2.append(list([]))
    for i in range (3):
        visitedlist.append (list(placehold))
        adjlist.append(list(placeholder2))


N = int(raw_input())
casenum = 0
while casenum < N:
    code ()
    casenum += 1

"""
