primes=[2,3,5,7,11,13,17,19,23,29,31]
while True:
  try:
    i=input()
    print i,reduce(lambda x,y:x*y,[1]+filter(lambda x:x!= 0,map(lambda x,y:y**x,primes,map(lambda n:n(i),map(lambda n:(lambda f:lambda x:f(f,x))(lambda f,x:0 if x%n!=0 else 1+f(f,x/n)),primes)))))
  except:break
