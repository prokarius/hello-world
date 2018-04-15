primes = [x for x in xrange(2, 432) if not 0 in map(lambda z : x % z, xrange(2, int(x**0.5+1)))]
while 1:
 try:
  d = [int(x) for x in raw_input().split()]
  print (reduce(lambda x, y: x*y, map(lambda x: x(d[0])-x(d[1])-x(d[0]-d[1])+1, map(lambda n: (lambda f: lambda x: f(f,x))(lambda k, x:0 if x//n==0 else x//n+k(k,x//n)), primes))))
 except: break
