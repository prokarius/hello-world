"""

import sys
import math

length = 1
lengthlist = [1]

for i in range (1,1000001):
    length += math.log(i,10)
    lengthlist.append(int(length))

def code (N):
    number = int(N)
    print lengthlist [number]

N = sys.stdin.readline()

while N:
    code (N)
    N = sys.stdin.readline()

"""

### Inverse Factorial ###

import math

length = 1
lengthlist = [1]

for i in range (1,1000001):
    length += math.log(i,10)
    lengthlist.append(int(length))

N = raw_input()
if N == "1":
    print 1
elif N == "2":
    print 2
elif N == "6":
    print 3
elif N == "24":
    print 4
elif N == "120":
    print 5
elif N == "720":
    print 6
else:
    length = len (N)
    print lengthlist.index(length)
