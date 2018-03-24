def k(a,b,m=0):
 if a==n:return(b,0)[b<200]
 if b>199:return(2*b+sum(x[a:]))<<n+~a
 while a<n:m+=k(a+1,b+x[a]);a+=1
 return m
z=input;n=int(z());x=[*map(int,z().split())]
print(sum(map(k,range(1,n+1),x)))
