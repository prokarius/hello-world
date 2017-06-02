def calcgames0 (dlist):
    dlist[0] = dlist[1] + dlist[2] + dlist[3]
    return dlist

def calcgames1 (dlist):
    dlist[1] = dlist[0] - (dlist[2] + dlist[3])
    return dlist

def calcgames2 (dlist):
    dlist[2] = dlist[0] - (dlist[1] + dlist[3])
    return dlist
    
def calcgames3 (dlist):
    dlist[3] = dlist[0] - (dlist[1] + dlist[2])
    return dlist

def calcscore4 (dlist):
    dlist[4] = dlist[1]*3 + dlist[2]
    return dlist

def calcscore2 (dlist):
    dlist[2] = dlist[4] - dlist[1]*3
    return dlist

def calcscore1 (dlist):
    dlist[1] = (dlist[4] - dlist[2])/3
    return dlist

def code():
    R = raw_input()
    dlist = []
    data = R.split(" ")
    case = 0
    for t in range(len(data)):
        try:
            dlist.append(int(data[t]))
        except (ValueError):
            dlist.append(-1)
            case += (2**(4-t))

    while case != 0:
        if (case % 2 == 1 and (case/4)%4 == 0):
            dlist = calcscore4(dlist)
            case -= 1
        elif (case % 2 == 0 and (case/4)%4 == 1):
            dlist = calcscore2(dlist)
            case -= 4
        elif (case % 2 == 0 and (case/4)%4 == 2):
            dlist = calcscore1(dlist)
            case -= 8
        if ((case/2)%16 == 8):
            dlist = calcgames0 (dlist)
            case -= 16
        elif ((case/2)%16 == 4):
            dlist = calcgames1 (dlist)
            case -= 8
        elif ((case/2)%16 == 2):
            dlist = calcgames2 (dlist)
            case -= 4
        elif ((case/2)%16 == 1):
            dlist = calcgames3 (dlist)
            case -= 2
        if case == 13:
            l = dlist [3]
            dlist = [l, 0, 0, l, 0]
            case -= 13
        elif case == 11:
            l = dlist [2]
            dlist = [l, 0, l, 0, l]
            case -= 11
        elif case == 7:
            l = dlist [1]
            dlist = [l, l, 0, 0, 3*l]
            case -= 7
        elif case == 14:
            dlist[2] = (dlist [4] - dlist[0] * 3)%3
            case -= 4
        elif case == 12:
            dlist[1] = (dlist[4]-(dlist[0]-dlist[3]))/2
            dlist = calcgames2 (dlist)
            case -= 12
        elif case == 18:
            dlist [3] = 0
            dlist = calcgames0 (dlist)
            case -= 18
        elif case == 23:
            dlist = [100, 100, 0, 0, 300]
            case -= 23
        elif case == 27:
            dlist = [100, 0, 100, 0, 100]
            case -= 27
        elif case == 29:
            dlist = [100, 0, 0, 100, 0]
            case -= 29
        elif case == 30:
            if dlist[4]%3 == 0:
                dlist = [100, 100, 0, 0, 300]
            elif dlist[4]%3 == 1:
                dlist = [100, 99, 1, 0, 298]
            elif dlist[4]%3 == 2:
                dlist = [100, 98, 2, 0, 296]
            case -= 30
        elif case == 21:
            dlist [0] = 100
            dlist [2] = 0
            dlist [4] = dlist[1]*3
            case -= 21
        elif case == 25:
            dlist [0] = 100
            dlist [1] = 0
            dlist [4] = dlist[2]
            case -= 25
        elif case == 28:
            if dlist[4] % 3 == 0:
                dlist [2] = 0
            elif dlist[4] % 3 == 1:
                dlist [2] = 1
            elif dlist[4] % 3 == 2:
                dlist [2] = 2
            dlist [1] = (dlist[4]-dlist[2])/3
            dlist = calcgames0 (dlist)
            case -= 28
        elif case == 15:
            dlist = [0,0,0,0,0]
            case -= 15
    outputstr = ""
    for i in dlist:
        outputstr += str(i) + " "
    print outputstr [:-1]
    
N = int(raw_input())
while N > 0:
    code()
    N -= 1
