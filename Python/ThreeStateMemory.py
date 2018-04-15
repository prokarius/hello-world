'''
#TLE Solution 2

import sys

sys.setrecursionlimit(10000)

MOD = 1000000009

def F(n):
    if n in memo:
        return memo[n]
    else:
        while n&1:
            if n <= 2:
                return memo[n]
            n = n>>1
        ph = (F(n>>1) + F((n>>1)-1)) % MOD
        memo[n] = ph
        return ph

n = int(input(), 2)
memo = {0:1, 1:1, 2:2}
print (F(n))


TLE Solution 1

stack = []
MOD = 1000000009
memo = {0:1, 1:1, 2:2}

def F(n):
    if n in memo:
        return memo[n]
    if n%2:
        ph = F(n/2) % MOD
        memo[n] = ph
        return ph
    else:
        ph = (F(n/2) + F((n/2)-1)) % MOD
        memo[n] = ph
        return ph

n = int(raw_input(), 2)
stack.append(n)
stackhead = 0
while len(stack) != stackhead:
    head = stack[stackhead]
    if head < 2:
        stackhead += 1
        continue
    if head % 2:
        stack.append(head/2)
    else:
        stack.append(head/2)
        stack.append((head/2)-1)
    stackhead += 1

while not stack:
    F(stack.pop())

print F(n)
'''
