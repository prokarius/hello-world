import sys

n = sys.stdin.readline()

while n:
    n = int(n)
    ans = 0
    diff = n
    high = n
    low = 1
    guess = (high + low) / 2

    while low <= high:
        c = guess ** 3
        if abs(n-c) < diff:
            diff = abs(n-c)
            ans = guess

        if c < n:
            low = guess+1
        else:
            high = guess-1
        guess = (high + low)/2

    print ans
    n = sys.stdin.readline()
