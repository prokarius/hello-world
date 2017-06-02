import sys

def code (N):
    if N == 0:
        print 0
    elif N == 1:
        print 1
    else:
        summod = 1
        currmod = 1
        length = 1
        while summod != 0:
            currmod =(currmod * 10)%N
            summod += currmod
            summod = summod % N
            length += 1
        print length

N = sys.stdin.readline()

while N:
    code (int(N))
    N = sys.stdin.readline()
