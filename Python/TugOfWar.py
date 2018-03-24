'''
r=range,d=[]
n=int(input())
for i in r(n): d.append(int(input()))
x=[[0 for i in r(45000)] for y in r(50)]
x[0][0]=1
for z in d:
 for i,j in zip(r(50),r(45000)):
  if x[j][i]:x[j+1][i+z]:
   pass
'''
###

n = int (input())
x=[[0 for i in range(30)] for y in range(3)]
x[0][0] = 1
t=0
for i in range(n):
 d=int(input())
 t+=d
 for j in range(n//2)[::-1]:
  for k in range (30-d):
   x[j+1][k+d] += x[j][k]
a=t//2+1;i=0
print(x)
while 1:
 if x[n//2][a+i]: print (a-i, t-a+i);break
 elif x[n//2][a-i]: print (a+i, t-a-i);break
 else: i+=1
