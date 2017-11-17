"""
from decimal import *

getcontext().prec = 100

ph = raw_input()
N, K = [int(x) for x in ph.split()]
t = Decimal(0)
for i in range (1, N+1):
    t += Decimal(1)/Decimal(i)
phlist = []
songlist = []
sum = Decimal(0)
while (N):
    ph = raw_input()
    dlist = ph.split()
    f = Decimal(dlist[0])
    sum += f
    phlist.append((f, dlist[1]))
    N -= 1

each = sum/t

PRECISION = Decimal(10)**-40

for i in range(len(phlist)):
    q = (phlist[i][0]/each*(i+1)).quantize(PRECISION)
    ntuple = (q, -i, phlist[i][1])
    songlist.append(ntuple)

songlist.sort()

for i in songlist:
    print i

print songlist[7][0] == songlist[8][0]

for i in range(K):
    print songlist[-i-1][2]
"""

t=raw_input;r=range;q=[]
N,K=t().split()
j=1;exec"p=t().split();q.append((int(p[0])*j,-j,p[1]));j+=1;"*int(N)
q.sort()
for j in r(int(K)):print q[~j][2]
#while K:print 
#while K:print q.pop()[2];K-=1
