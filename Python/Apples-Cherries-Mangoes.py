"""

### NAIVE METHOD. CALCULATES FACTORIALS TOO MANY TIMES ###

def inverse (q):
    modlist = []
    a = factorial (q, 0)
    modlist.append(a)
    output = 1
    for i in range (29):
        a = a ** 2
        a = a % 1000000007
        modlist.append(a)
    modlist.reverse()
    for i in range(30):
        if "111011100110101100101000000101"[i] == "1":
            output *= modlist[i]
            output = output % 1000000007
    return output
        
def factorial (N,a):
    if N > 200000:
        print N
    if N < 0:
        return 0
    else:
        num = 1
        for i in range(a,N):
            num *= i+1
            num = num % 1000000007
        return num

def chose(N, r):
    if N>=r:
        if r < N-r:
            r = N-r
        g = (factorial(N,r)*inverse(N-r)) % 1000000007
        return g
    else:
        return 0

def ways (A, x, y, z):
    if x < 0 or y < 0 or z < 0:
        return 0
    output = (factorial (A,x)* inverse(y)) % 1000000007
    output = (output * inverse(z)) % 1000000007
    return output

def buckets (A, C, M):
    if A == 0:
        return 0
    if A > C+M:
        return 0
    output = 0
    i = 0
    while i <= 1+(A+M-C)/2:
        j = C - M + i
        k = A - (i + j)
        if M-i-k < 0 or k < 0:
            output += 0
        else:
            new = ways(A,i,j,k)*chose(M-i-k+A-1,A-1) %1000000007
            new = (new *(2**k)) % 1000000007
            output += new
            output = output % 1000000007
        i += 1
    return output

def code(A,C,M):
    print (buckets(A+1, C, M)+buckets(A-1, C, M)+2 * buckets(A, C, M)) % 1000000007


N = raw_input()
datl = [int(x) for x in N.split()]
datl.sort()
code (datl[2] ,datl[1], datl[0])



"""


factorial = [1]
inverse = [1]
p2 = [1]

MOD = 1000000007

na = 1
for w in range (1, 400004):
    na = (na*w) % MOD
    factorial.append(na)

for l in range (1, 200004):
    a = factorial[l]
    output = 1
    for p in '101000000101001101011001110111':
        if p == '1':
            output = (output*a) % MOD
        a = (a*a) % MOD
    inverse.append(output)

ph = 1
for y in range (200005):
    ph = (ph*2) % MOD
    p2.append(ph)

def chose(N, r):
    if N>=r:
        g = (factorial[N]*inverse[N-r]) % MOD
        return (g*inverse[r]) % MOD        
    return 0

def ways (A, x, y, z):
    if x < 0 or y < 0 or z < 0:
        return 0
    output = (factorial [A]*inverse[x]) % MOD
    output = (output * inverse[y]) % MOD
    output = (output * inverse[z]) % MOD
    return output

def buckets (A, C, M):
    if A == 0:
        return 0
    if A > C+M:
        return 0
    output = 0
    i = 0
    while i <= 1+(A+M-C)/2:
        j = C - M + i
        k = A - (i + j)
        if M-i-k >= 0 and k >= 0:
            new = ways(A,i,j,k)*chose(M-i-k+A-1,A-1) % MOD
            new = new*p2[k] % MOD
            output = (output + new) % MOD
        i += 1
    return output

def code(A,C,M):
    print (buckets(A+1, C, M) + buckets(A-1, C, M) + 2*buckets(A, C, M)) % MOD


N = raw_input()
datl = [int(x) for x in N.split()]
datl.sort()
code (datl[2] ,datl[1], datl[0])

