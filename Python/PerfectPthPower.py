some_list = [True for i in range(66000)]
some_list[0] = some_list[1] = False;
prime_list = []
for i in range(66000):
    if not some_list[i]:
        continue
    prime_list.append(i)
    for j in range(i,66000/i):
        some_list[j*i] = False

def gcdfunc (a, b):
    if b > a:
        a,b = b,a
    if a % b == 0:
        return b
    else:
        return gcdfunc(b, a%b)

def code(N):
    if N < 0:
        negative = True
        N = abs(N)
    else:
        negative = False
    factorisation = []
    gcdlist = []
    for i in prime_list:
        if N%i == 0:
            counter = 0
            while N%i == 0:
                N = N // i
                counter += 1
            if counter != 0:
                factorisation.append ((i, counter))
            if N == 1:
                break
    if N != 1:
        factorisation.append ((0, 1))
    for i in factorisation:
        gcdlist.append (i[1])
    while len(gcdlist) > 1:
        A = gcdlist.pop()
        B = gcdlist.pop()
        gcdlist.append(gcdfunc(A,B))
    output = gcdlist [0]
    if negative:
        while output%2 == 0:
            output /= 2
        print output
    else:
        print output


N = int(raw_input())

while N != 0:
    code (N)
    N = int(raw_input())

