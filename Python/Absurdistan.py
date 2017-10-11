def choose (n, r):
    r = min (r, n-r)
    if ch [n][r] != 0:
        return ch[n][r]
    else:
        ch[n][r] = (ch[n][r-1]*(n-r+1))/r
        return ch[n][r]

N = int(raw_input())
if (N < 4):
    print 1.0

else:
    ch = [[0 for x in range((1+N)/2)] for y in range (N)]
    for i in range (N):
        ch[i][0] = 1

    d = (N-1)**N

    numways = [0 for x in range(N+1)]
    numways[2] = 1
    numways[3] = 8
    for i in range (4, N+1):
        ph = 0
        for j in range (2, i-1):
            ph += numways[j]*((i-j-1)**(i-j))*choose(i-1, j-1)
        numways[i] = ((i-1)**i) - ph
    print float(numways[N])/d
