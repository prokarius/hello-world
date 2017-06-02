N = raw_input()
datalist = [int(x) for x in N.split(' ')]

dpmatrix = [[0 for x in range (datalist[1]+1)] for y in range (datalist[0]+1)]
summatrix = [[0 for x in range (datalist[1]+2)] for y in range (datalist[0]+1)]

dpmatrix [0][0] = 1
for i in range (1, datalist[1]+2):
    summatrix [0][i] = 1

for i in range (1,datalist[0]+1):
    summation = 0
    subtracts = 0
    for j in range (1, datalist[1]+2):
        subtracts = j - i
        if subtracts < 0:
            subtracts = 0   
        dpmatrix[i][j-1] = (1000000007 + summatrix[i-1][j]-summatrix[i-1][subtracts])%1000000007
        summation += (summatrix[i-1][j]-summatrix[i-1][subtracts])%1000000007
        summatrix [i][j] = summation
        
print dpmatrix [-1][-1]
