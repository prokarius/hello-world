def fastExpo(n,m,p):
    r = 1
    while (m):
        if (m%2):
            r = (r*n) % p
        m /= 2
        n = (n*n) % p
    return r

m=10**4+7
for i in range(input()):
    k = input()
    print (fastExpo(9, k-1, m) * 8) % m 
