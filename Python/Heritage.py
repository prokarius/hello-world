MOD = 1000000007

def numcombi(s):
    l = len(s) + 1
    for i in range (l):
        if not (s[:i] in d) and dp[i] == 0:
            continue
        if s[:i] in d:
            dp[i] = dp[i] + d[s[:i]] % MOD

        for j in range(i, l):
            new = s[i:j]
            if not (new in d):
                continue
            dp[j] = (dp[j] + d[new] * dp[i]) % MOD

    return dp[l-1] % MOD

t = raw_input()
ph = [x for x in t.split()]
n = int(ph[0])
name = ph[1]
d = {}
while (n>0):
    t = raw_input()
    ph = [x for x in t.split()]
    v = int(ph[1])
    k = ph[0]
    d[k] = v
    n -= 1

dp = [0 for i in range(34)]
print numcombi(name)
