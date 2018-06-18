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
