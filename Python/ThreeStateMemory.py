import sys

sys.setrecursionlimit(20000)

MOD = 1000000009

def F(n):
    try:
        return memo[n]
    except:
        if n%2:
            ph = F(n/2) % MOD
            memo[n] = ph
            return ph
        else:
            ph = (F(n/2) + F((n/2)-1)) % MOD
            memo[n] = ph
            return ph

n = int(raw_input(), 2)
memo = {0:1, 1:1, 2:2}
print F(n)
