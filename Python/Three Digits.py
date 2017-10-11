
### Three Digits ###

def recursion (number):
    if number <= 10:
        lastthreedigits = [0, 1, 2, 6, 24, 12, 72, 504, 32, 288, 288]
        return lastthreedigits [number]
    else:
        leftovers = number % 10
        a = (number/10)-1
        fivefacts = number/5
        threedigits = 1
        while a != 0:
            threedigits *= 144
            threedigits = threedigits %1000
            a -= 1
        if leftovers > 4:
            threedigits *= 72
        else:
            threedigits *= 144
        for i in range ((number - leftovers)%1000, (number)%1000):
            if i % 10 != 4:
                threedigits *= (i+1)
                threedigits = threedigits % 1000
        return (threedigits * recursion(fivefacts)) % 1000

N = int(raw_input())
if N == 8:
    print "032"
elif N < 10:
    print recursion (N)
else:
    T = str(recursion (N) + 1000)
    print T[-3:]


"""
Brute Force Method

Q = int(raw_input())
numFive = 0
numTwo = 0
n = 1
for i in range (1, Q):
    m = i+1

    while ((m%2 == 0) or (m%5 == 0)):
        if m%2 == 0:
            m = m/2
            numTwo += 1
        if m%5 == 0:
            m = m/5
            numFive +=1
    n = (n*m) % 1000

while numFive < numTwo:
    n = n*2 % 1000
    numTwo -= 1

if Q > 7:
    n = str(n+1000)
    print n[-3:]
else:
    numlist = [0, 1, 2, 6, 24, 12, 72, 504]
    print numlist [Q]
"""
"""

### Low Order Zeros ###

def recursion (number):
    if number <= 10:
        lastthreedigits = [0, 1, 2, 6, 4, 2, 2, 4, 2, 8, 8]
        return lastthreedigits [number]
    else:
        leftovers = number % 10
        a = (number/10)-1
        fivefacts = number/5
        threedigits = 1
        while a != 0:
            threedigits *= 4
            threedigits = threedigits %10
            a -= 1
        if leftovers > 4:
            threedigits *= 72
        else:
            threedigits *= 144
        for i in range ((number - leftovers)%10, (number)%10):
            if i % 10 != 4:
                threedigits *= (i+1)
            threedigits = threedigits % 10
        return (threedigits * recursion(fivefacts)) % 10
    
N = int(raw_input())
while N != 0:
    print recursion (N)
    N = int(raw_input())


"""
"""
### Odd And Even Zeros ###

fives = [1]
staring = 1
steps = 13
for i in range (1,steps):
    staring = (staring*5 + (2*(5**(2*i - 1))))
    fives.append(staring)

def code (N):
    fivedecomp = []
    output = 0
    parity = True
    while N != 0:
        fivedecomp.append(N%25)
        N = N/25
    length = len (fivedecomp)
    for i in range(len(fivedecomp)):
        tensfive = fivedecomp[length-i-1]/10
        onesfive = fivedecomp[length-i-1]%10
        output += tensfive * 10 * (25 ** (length-i-1))
        if onesfive < 4:
            print 1
            if parity:
                output += fives[length-i-1] * onesfive
            else:
                output += (25 ** (i+1) - fives[length-i-1]) * onesfive
        else:
            print 2
            if parity:
                output += fivedecomp[length-i-1] * 5
                output += (25 ** (i +1) - fives[length-i-1]) * onesfive

            parity = not parity
    print output

N = int(raw_input())
while N != -1:
    code (N+1)
    N = int(raw_input())


"""
