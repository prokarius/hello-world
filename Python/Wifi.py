def check (R, N, K, array):
    curr = array[0]+R
    for i in xrange (N):
        if array[i] > curr:
            curr = array[i] + R
            K -= 1
            if K <= 0:
                return 0
    return 1

def cod():
    ph = raw_input()
    dlist = [int(x) for x in ph.split()]
    arr = [0]*dlist[1]
    for i in xrange(dlist[1]):
        arr[i] = input()
    if dlist[0] >= dlist[1]:
        print "0.0"
        return
    arr.sort()
    high = low = 2**20
    while (low):
        if check(high-low, dlist[1], dlist[0], arr):
            high -= low
        low /= 2
    print str(high/2) + "." + str(5*(high%2))

N = input()
while (N):
    cod()
    N -= 1
