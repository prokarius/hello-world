"""

### Bit by Bit ###

def code (N):
    buff = ["?" for i in range (32)]
    while N > 0:
        N -= 1
        Q = raw_input()
        datl = [x for x in Q.split(' ')]
        if datl [0] == "SET":
            buff [int(datl[1])] = "1"
        elif datl [0] == "CLEAR":
            buff [int(datl[1])] = "0"
        elif datl[0] == "AND":
            if buff [int(datl[2])] == "0":
                buff [int(datl[1])] = "0"
            elif buff [int(datl[2])] == "?":
                if buff [int(datl[1])] != "0":
                    buff [int(datl[1])] = "?"
        elif datl[0] == "OR":
            if buff [int(datl[2])] == "1":
                buff [int(datl[1])] = "1"
            elif buff [int(datl[2])] == "?":
                if buff [int(datl[1])] != "1":
                    buff [int(datl[1])] = "?"
    outputstr = ""
    buff.reverse()
    for i in buff:
        outputstr += i
    print outputstr

N = int(raw_input())
while N != 0:
    code (N)
    N = int(raw_input())

"""

"""
### Catalan ###

catalan = [1]
new = 1
for i in range (5000):
    new *= (4*i +2)
    new /= (i+2)
    catalan.append(new)

numcase = int(raw_input())
while numcase > 0:
    Q = int(raw_input())
    print catalan[Q]
    numcase -= 1

### Catalan Square ###


numcase = int(raw_input())
output = 0
for i in range(numcase+1):
    output += catalan[i]*catalan[numcase-i]

print output

"""

"""
### Bits ###

def bits (N):
    maxi = 0
    while N != 0:
        count = 0
        test = str(bin(N))
        for i in test:
            if i == "1":
                count += 1
        if count > maxi:
            maxi = count
        N /= 10
    print maxi

numcase = int(raw_input())
while numcase > 0:
    Q = int(raw_input())
    bits(Q)
    numcase -= 1
"""

### Bits Equalizer ###

def biteq(N):
    line1 = raw_input()
    line2 = raw_input()
    num01 = 0
    num10 = 0
    numq1 = 0
    numq0 = 0
    for i in range(len(line1)):
        if line1[i] == "1" and line2[i] == "0":
            num10 += 1
        elif line1[i] == "0" and line2[i] == "1":
            num01 += 1
        elif line1[i] == "?":
            if line2[i] == "1":
                numq1 += 1
            else:
                numq0 += 1
    if num10 > (numq1 + num01):
        print "Case " + str(N+1) + ": -1"
    else:
        mismatch = numq0 + numq1
        numqto1 = numq1 + num01 - num10
        if numq1 >= numqto1:
            numq1 -= numqto1
            num01 += numq1
        else:
            numqto1 -= numq1
            num10 += numqto1
        mismatch += num01

    
        print "Case " + str(N+1) + ": " + str(mismatch)

numcases = int(raw_input())
counter = 0
while counter < numcases:
    biteq(counter)
    counter += 1
