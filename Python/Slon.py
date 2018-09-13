'''
# My attempt at golfing this question (TLE)
e=input();p,m=map(int,input().split());x=0;
while(eval(e)%m-p):x+=1
print(x)

# My second attempt at golfing this question (TLE)
e=input();p,m=map(int,input().split());x=0;b=eval(e);x=1;a=eval(e)-b;f=str(a)+'*x+'+str(b)
while(eval(f)%m-p):x+=1
print(x)
'''

# Solution? Don't eval!
e=input();p,m=map(int,input().split());x=0;b=eval(e);x=1;a=eval(e)-b
while(a*x+b)%m-p:x+=1
print(x)
