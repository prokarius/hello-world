def check (N, num, i):
    test = N*i
    newnum = 0
    while test != 0:
        newnum += test%10
        test /= 10
    return num == newnum

def code (N):
    num = 0
    number = N
    while N != 0:
        num += N%10
        N /= 10
    i = 11
    while not check(number, num, i):
        i += 1
    print i

N = int(raw_input())
while N != 0:
    code (N)
    N = int(raw_input())
