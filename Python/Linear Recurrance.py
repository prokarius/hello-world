import math

def makemat (n):
    phmat = []
    matrix = []
    for i in range(n):
        phmat.append(0)
    for i in range(n):
        matrix.append(list(phmat))
    return matrix

def trans(n, data):
    matrix = makemat(n)
    for i in range(n-1):
        matrix[i][i+1] = 1
    for i in range(n-1):
        matrix[-2][i] = data[n-i-1]
    matrix [-1][-1] = 1
    return matrix

def matmul (matrix1, matrix2, modulo,n):
    newmatrix = makemat(n)
    for i in range(n):
        for j in range (n):
            for k in range (n):
                newmatrix [i][j] = (newmatrix [i][j] + matrix1[i][k]*matrix2[k][j]) % modulo
    return newmatrix

def cod(initmatrix):
    newmat = transform
    outputmat = makemat(N)
    for i in range(N):
        outputmat[i][i] = 1
    A = raw_input()
    dlist = [int(x) for x in A.split(' ')]
    if dlist[0] < N-1:
        return initmatrix[dlist[0]]%dlist[1]
    dlist[0] -= (N-2)
    P = int(math.log(dlist[0], 2))+1
    while dlist[0] != 0:
        if dlist[0]%2 == 1:
            outputmat = matmul(newmat, outputmat, dlist[1], N)
        newmat = matmul(newmat, newmat, dlist[1], N)
        dlist[0] = dlist[0] >> 1
    output = 0
    for i in range(N-1):
        output = (output + outputmat[-2][i]*initmatrix[i])%dlist[1]
    output = (output + outputmat[-2][-1]*data[0])%dlist[1]
    return output
    
N = int(raw_input())+1
P = raw_input()
Q = raw_input()
inimat = [int(x) for x in Q.split(" ")]
data = [int(x) for x in P.split(" ")]
T = int(raw_input())
transform = trans(N, data)
for i in range(T):
    print cod(inimat)
