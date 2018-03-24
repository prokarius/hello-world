def zerocount(Q):
    result = 0
    while Q != 0:
        result += ((Q%10) == 0)
        Q = Q/10
    return result

def zero (Q):
    if Q<10:
        return 0
    if ((Q%10)!= 9):
        return (zerocount (Q)) + zero (Q-1)
    else:
        return 10*zero(Q/10) + (Q/10)
    
def code (N):
    if N == "0 0":
        print 1
    datalist = [int(x) for x in N.split(' ')]
    zerolarge = zero(datalist[1])
    if datalist[0] == 0:
        zerosmall = -1
    else:
        zerosmall = zero(datalist[0]-1)
    print zerolarge - zerosmall

N = raw_input()
while N != "-1 -1":
    code (N)
    N = raw_input()
