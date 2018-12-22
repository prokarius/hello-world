import sys

def mycode (N1, N2):
    row1 = [int(x) for x in N1.split(' ')]
    row2 = [int(x) for x in N2.split(' ')]
    det = row1[0]*row2[1] - row1[1]*row2[0]
    newrow1 = [row2[1]/det, 0-row1[1]/det]
    newrow2 = [0-row2[0]/det, row1[0]/det]
    string1 = str(newrow1[0]) + " " + str(newrow1[1])
    string2 = str(newrow2[0]) + " " + str(newrow2[1])
    print "Case " + str(casenum) + ":"
    print string1
    print string2

N1 = sys.stdin.readline()
casenum = 1
while N1:
    N2 = sys.stdin.readline()
    mycode (N1, N2)
    casenum += 1
    worthless = sys.stdin.readline()
    N1 = sys.stdin.readline()
