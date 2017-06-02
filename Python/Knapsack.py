

### Knapsack ###

import sys

def knapsack (N):

    #Store the shit
    datalist = [int(float(x)) for x in N.split(' ')]
    cap = datalist [0]
    numobjs = datalist [1]
    weightlist = []
    valuelist = []
    for i in range(numobjs):
        Q = raw_input()
        objdata = [int(x) for x in Q.split(' ')]
        valuelist.append (objdata[0])
        weightlist.append (objdata[1])

    # DP that shit
    dpmatrix = [[0 for x in range(cap+1)] for y in range(numobjs+1)]
    for i in range(1, numobjs+1):
        for j in range (1, cap+1):
            if weightlist[i-1] <= j:
                value = dpmatrix[i-1][j-weightlist[i-1]] + valuelist[i-1]
                if value > dpmatrix[i-1][j]:
                    dpmatrix [i][j] = value
                else:
                    dpmatrix[i][j] = dpmatrix[i-1][j]
            else:
                dpmatrix[i][j] = dpmatrix[i-1][j]

    #Find which shit we used
    used = [False for x in range(numobjs)]
    posobj = numobjs
    poscap = cap
    while posobj >= 0:
        if dpmatrix[posobj][poscap] > dpmatrix[posobj-1][poscap]:
            used[posobj-1] = True
            poscap -= weightlist[posobj-1]
        posobj -= 1
    outputnum = 0
    outputstr = ""

    # Print shit
    for i in range(numobjs):
        if used[i]:
            outputnum += 1
            outputstr += str(i) + " "
    print outputnum
    if outputnum != 0:
        print outputstr [:-1]
    else:
        print ""

#Shit starts here
N = sys.stdin.readline()
while N:
    knapsack (N)
    N = sys.stdin.readline()



"""

### Balanced Diet ###

def knapsack (N):
    valuelist = [int(x) for x in N.split(' ')]
    numobjs = valuelist.pop (0)
    tweight = 0
    for i in valuelist:
        tweight += i
    targetweight = tweight/2

    dpmatrix = [[0 for x in range(targetweight+1)] for y in range(numobjs+1)]
    for i in range(1, numobjs+1):
        for j in range (1, targetweight+1):
            if valuelist[i-1] <= j:
                value = dpmatrix[i-1][j-valuelist[i-1]] + valuelist[i-1]
                if value > dpmatrix[i-1][j]:
                    dpmatrix [i][j] = value
                else:
                    dpmatrix[i][j] = dpmatrix[i-1][j]
            else:
                dpmatrix[i][j] = dpmatrix[i-1][j]
    best = dpmatrix [-1][-1]
    best2 = tweight - dpmatrix[-1][-1]
    if best > best2:
        print str(best) + " " + str(best2)
    else:
        print str(best2) + " " + str(best)


N = raw_input()
while N!= "0":
    knapsack (N)
    N = raw_input()

"""

