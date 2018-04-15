import sys

def execute (N):
    if "+" in N or "*" in N:
        eval ('print ((' + N + ')%10000)')
        return
    ph = N.split()
    print (pow(int(ph[0]), int(ph[2]), 10000))

N = sys.stdin.readline()

while N:
    execute(N)
    N = sys.stdin.readline()
