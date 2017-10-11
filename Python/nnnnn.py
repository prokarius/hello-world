"""

### NAIVE SOLUTION ###

output = 0
run = 1
N = int(raw_input())

while (output * len(str(output))) < N:
    output += run
    run *= 2

run /= 2
while run != 0:
    output -= run
    if (output * len(str(output))) < N:
        output += run
    run /= 2

print output


### STILL NAIVE SOLUTION ###

def code(N):
    output = 1048576
    run = 524288
    while run != 0:
        output -= run
        if (output * 10**output) < N:
            output += run
        run /= 2

    print N/output


q = int(raw_input())
if q == 0:
    print 0
else:
    code(q)


### WORKING ON THIS ###

import math
import time

def code(N):
    start = time.time()
    P = len(N)
    output = P - len(str((P+1)))
    now = time.time()
    print now - start
    start = now
    while (math.log10(output) + output) < P:
        output += 1
    d = int(q)
    now = time.time()
    print now - start
    start = now
    d = d/output
    now = time.time()
    print now - start
    start = now


q = raw_input()
if len(q) == 1:
    print q
else:
    code(q)

"""
"""

### SLIGHTLY BETTER NAIVE SOLUTION ###

import math

def code(P):
    output = (int(P)+1) - len(str((int(P)+1)))
    while (math.log10(output) + output) < P:
        output += 1
    print q/output


q = input()
if q == 0:
    print 0
else:
    P = math.log10(q)
    if P < 1:
        print q
    else:
        code(P)

"""
"""

### CURRENT SOLUTION ###


import math

def cod ():
    n = int(input())
	if n == 0:
	    return 0
	d = math.log10(n)
	if d < 1:
		return n
	d = int(d) + 1
	c = 0
	while c < 8:
	    if n % (d-c) == 0:
	        return n//(d-c)
			break
		c += 1
print (cod())


"""

n = list((raw_input()))
if len (n) == 1:
	print n[0]
else:
	for i in range(len(n), len(n)-8, -1):
		print i
		curr = 0
		not_zero = -1
		y = list (n)
		for j in range(len(n)):
			curr = curr * 10 + int(n[j])
			y[j] = str(curr/i)
			if y[j] !='0' and not_zero < 0:
				not_zero = j
			curr = curr%i
		if curr == 0 and len(n) - not_zero == i:
			print ("".join(y[not_zero:]))
			break


