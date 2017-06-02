listmat = [[[3,5],[1,3]]]
r = [[3,5],[1,3]]

def matmul (r1, r2):
    a = (r1[0][0]*r2[0][0]+r1[0][1]*r2[1][0])%1000
    b = (r1[0][0]*r2[0][1]+r1[0][1]*r2[1][1])%1000
    c = (r1[1][0]*r2[0][0]+r1[1][1]*r2[1][0])%1000
    d = (r1[1][0]*r2[0][1]+r1[1][1]*r2[1][1])%1000
    return [[a,b],[c,d]]

for i in range(30):
    r = matmul (r, r)
    listmat.append(r)
    
def code (num):
    curmat = [[1,0],[0,1]]
    bina=(bin(num)[::-1])[:-2]
    for i in range(len(bina)):
        if bina[i] == "1":
            curmat = matmul(curmat, listmat[i])
    return (2*curmat[0][0] - 1)+1000

numcases = int(raw_input())
casenum = 0
while casenum < numcases:
    cur = int(raw_input())
    outputstr = code (cur)
    casenum += 1
    print "Case #" + str(casenum) + ": " + str(outputstr)[1:]
