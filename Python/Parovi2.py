def gcd (a,b):
    if b == 0:
        return a
    else:
        return gcd(b, a%b)

n = int(raw_input())

dp = [0 for x in range (2**(n-1))]
dp [0] = 1

drange = range(2**(n-1))
drange.reverse()

for i in range (1, n+1):
    for j in range (i+1, n+1):
        if gcd(i,j) == 1:
            cover = 2**(j-1) - 2**(i-1)
            for k in drange:
                if dp[k] > 0:
                    ph = k|cover
                    dp[ph] = (dp[ph] + dp[k]) % 1000000000

print dp[2**(n-1)-1]
