import math

def facto(Q, N):
    output = 1
    for i in range(Q, N):
        output *= i+1
    return output

b = []
for i in range(51):
    x = 0
    a = []
    for j in range ((1+i)/2):
        x += facto(i-j, i)/float(facto(0,j))
        a.append(int(math.ceil(100-((100*x)/2**i))))
    b.append(list(a))

def code ():
    Q = raw_input()
    dlist = [int(x) for x in Q.split(' ')]
    if dlist[2] > dlist[0]/2:
        return 0
    if dlist[0] %2 == 0 and dlist [2] == dlist[0]/2:
        return 0
    diff = dlist [1] - dlist [2]
    if diff <= 0:
        return 1
    vleft = dlist[0] - (dlist [1] + dlist [2])
    if vleft < diff:
        return 2
    if dlist [3] >= b[vleft][(vleft-diff)/2]:
        return 1
    return 2

numcases = int(raw_input())
while numcases > 0:
    r = code()
    if r == 0:
        print "RECOUNT!"
    if r == 1:
        print "PATIENCE, EVERYONE!"
    if r == 2:
        print "GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!"
    numcases -= 1
    
