d = {}
c = []
f = []
topolist = []
visited = []

def dfs(x):
    global visited, topolist
    try:
        for i in d[x]:
            if (not visited[i]):
                visited[i] = True
                dfs(i)
    except (KeyError):
        pass
    topolist.append(x)

def cod():
    global d, c, f, topolist, visited
    topolist = []
    k = int(raw_input())
    d = {}
    c = []
    f = []
    visited = [False for i in range(401)]
    dp = [0 for i in range(401)]
    dp[1] = 1
    visited[1] = True
    while (k):
        ph = raw_input()
        dlist = ph.split()
        if dlist[1] == "favourably":
            f.append(int(dlist[0]))
        elif dlist[1] == "catastrophically":
            c.append(int(dlist[0]))
        else:
            d[int(dlist[0])] = [int(x) for x in dlist[1:]]
        k -= 1
    dfs(1)
    topolist.reverse()
    o = 0
    for i in topolist:
        if i in f:
            o += dp[i]
        elif i in c:
            pass
        else:
            for j in d[i]:
                dp[j] += dp[i]
    print o

n = input()
while (n):
    cod()
    n -= 1

