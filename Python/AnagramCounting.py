import sys
from collections import Counter

def factorial(n):
    out = 1
    while n > 1:
        out *= n
        n -= 1
    return out

# Simple combinatorics. Just brute force the factorial
def code(string):
    count = Counter(string)
    out = factorial(len(string))
    for key in dict(count):
        out //= factorial(count[key])
    print (out)

N = sys.stdin.readline()

while (N):
    code(N[:-1])
N = sys.stdin.readline()
