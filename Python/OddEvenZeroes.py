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
