from fractions import Fraction
import sys

def check_unique(dlist):
    dlist[4] -= (dlist[0] + dlist[2])
    if dlist[4] == 0:
        print "1 1"
        return
    if dlist[2] == dlist[0]:
        print "?"
        return
    output = [1, 1]
    swap = False
    if dlist[2] < dlist[0]:
        swap = True
        dlist[0], dlist[2] = dlist[2], dlist[0]
    found = False
    while dlist[4] >= 0:
        if dlist[4] == 0:
            found = True
            break
        if dlist[4] % dlist[0] == 0:
            k = dlist[4]/dlist[0]
            if k < dlist[2] :
                output[0] += k
                found = True
            break
        output[1] += 1
        dlist[4] -= dlist[2]
    if found:
        if swap:
            output = [output[1], output[0]]
        print str(output[0]), str(output[1])
    else:
        print "?"
    return

def code():
    R = sys.stdin.readline()
    dist = [Fraction(int(x), 1) for x in R.split()]
    dlist = list(dist)
    output = [-1, -1]
    dlist[2] = (dlist[2] * dlist[1])/dlist[0]
    dlist[4] = (dlist[4] * dlist[1])/dlist[0]
    dlist[0] = dlist [1]
    dlist[1] = 0
    dlist[3] -= dlist[2]
    dlist[5] -= dlist[4]
    if dlist[3] == 0:
        if dlist[5] == 0:
            check_unique(dist)
        else:
            print "?"
        return
    else:
        output[1] = dlist[5]/dlist[3]
        if int(output[1]) != output[1] or output[1] <= 0:
            print "?"
            return
    dlist[5] = (dlist[5] * dlist[2])/dlist[3]
    dlist[4] -= dlist[5]
    output[0] = dlist[4]/dlist[0]
    if int(output[0])!= output[0] or output[0] <= 0:
        print "?"
        return
    print str(output[0]), str(output[1])
    
numcase = int(raw_input())
while numcase > 0:
    code ()
    numcase -= 1
