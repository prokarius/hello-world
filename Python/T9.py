"""

### T9 ###

letters = [('a','b','c'),('d','e','f'),('g','h','i'),('j','k','l'),('m','n','o'),('p','q','r','s'),('t','u','v'),('w','x','y','z'),(' ')]
def code (N):
    lastchr = 1
    outputstr = ""
    for i in N:
        counter = 2
        while i not in letters[counter -2]:
            counter += 1
        if counter == lastchr:
            outputstr += " "
        else:
            lastchr = counter
        outputstr += (letters[counter-2].index(i)+1) * str(counter%10) 
    print "Case #" + str(testcase+1) + ": " + outputstr

numcases = int(raw_input())
testcase = 0
while testcase < numcases :
    N = raw_input()
    code (N)
    testcase += 1
    
"""

"""

### Alien Numbers ###

import math

def code (N):
    datalist = [x for x in N.split(' ')]
    base = len(datalist[1])
    value = 0
    outputstr = ""
    for i in range(len(datalist[0])):
        temp = datalist[1].index(datalist[0][len(datalist[0])-i-1])
        value += temp * (base ** i)
    base2 = len(datalist[2])
    digit = int(math.log(value,base2))
    while digit >= 0:
        counter = 0
        while value - (base2 ** digit) >= 0:
            value -= (base2 ** digit)
            counter += 1
        outputstr += datalist[2][counter]
        digit -= 1
    print "Case #" + str(testcase+1) + ": " + outputstr

numcases = int(raw_input())
testcase = 0
while testcase < numcases :
    N = raw_input()
    code (N)
    testcase += 1

"""

### Text Messaging Outrage ###

def code (N):
    datalist = [int(x) for x in N.split(' ')]
    temp = raw_input()
    letterlist = [int(x) for x in temp.split(' ')]
    letterlist.sort()

    counter = 0
    output = 0
    while letterlist != []:
        chrfreq = letterlist.pop()
        output += chrfreq * (1+(counter/datalist[1]))
        counter += 1
    print "Case #" + str(testcase+1) + ": " + str(output)

numcases = int(raw_input())
testcase = 0
while testcase < numcases :
    N = raw_input()
    code (N)
    testcase += 1
