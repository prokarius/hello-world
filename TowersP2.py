##########################
#                        #
#   TOWERS OF POWERS 2   #
#    ~ POWER HARDER ~    #
#                        #
##########################

import math
#math.log10 (x) -> returns log b10 (x)

# Read the input into a list
dlist = []
n = int(raw_input())
for i in range (n):
    ph = raw_input()
    phl = [int(x) for x in ph.split('^')]
    dlist.append(phl)

# Clean up the list, remove elements which are just 1s.
for i in range (n):
    length = len(dlist[i])
    for j in range(length):
        if (dlist[i][j] == 1):
            break
    while (j<length):
        dlist.pop()

# Solution idea:
# Using log rule: log(a^b^c) = b^c log(a)
# log^2(a^b^c) = log^2(a) + c log(b)
# log(a+b) = log(a (1 + b/a)) = log(a) log(1 + b/a)
# if a is large ~(2^60), then b/a is inconsequential, and log (1+b/a) == 0
# But we need to keep track of where we have to take a into account.

# high stores value of number in a tuple: (rem, nth log power)
# i.e. recover the number by doing (10 ^^ n) ^ rem
high = []

# For each tower, we see when a becomes consequential
# We store this in the variable j.
# it also doubles to keep track of the power of the tower

print dlist

for i in range (n):
    x = dlist [i][-1]    
    treshold = -2   
    try:
        while (x * math.log(dlist[i][j], 2) < 64):
            x = dlist[i][j] ** x
            treshold -= 1
    except IndexError:
        treshold = len(dlist[i])
    treshold = len(dlist[i]) - treshold

    cur = 1
    index = 0
    power = 0

    # Now we power harder
    while (index < len (dlist[i])-2):
        if (index < treshold):
            cur = math.log(dlist[i][power],2) + 
        

        index += 1

    a += dlist[i][-1]*math.log(dlist[i][-2], 2)
    while a > 2:
        a = math.log(a, 2)
        power += 1
    high.append ((index, a, i))

print high
# Lastly, we gotta sort by the value of j, then the value of rem


