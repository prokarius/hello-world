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
