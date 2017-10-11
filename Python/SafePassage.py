n = raw_input()
dlist = [int(x) for x in n.split()]
plist = dlist [1:]
plist.sort()
plist.reverse() #sorted from longest to shortest
p1 = plist[-1]
p2 = plist[-2]

dp = [999999999 for x in range (dlist[0])]
dp[0] = 0
dp[1] = plist[0]+p1

for i in range (2, dlist[0]-1):
    dp[i] = min(dp[i-1] + p1 + plist[i-1], dp[i-2] + p1 + plist[i-2] + 2*p2)

print dp[dlist[0]-2] + plist[-2]
