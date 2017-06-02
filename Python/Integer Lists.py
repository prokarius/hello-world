def cod ():
    rev = False
    delf = 0
    delb = 0
    R = raw_input()
    q = int(raw_input())
    D = raw_input()
    if D == "[]":
        dl = []
    else:
        dl = [int(x) for x in (D[1:-1].split(','))]
    for i in range(len(R)):
        if R[i] == "D":
            if rev:
                delb += 1
            else:
                delf += 1
        else:
            rev = not rev
    if delb + delf > q:
        print "error"
        return
    plist = dl[delf:q-delb]
    if len(plist) == 0:
        print "[]"
        return
    if rev:
        plist.reverse()
    outputstr = "["
    for i in plist:
        outputstr += str(i) + ","
    outputstr = outputstr[:-1] +"]"
    print outputstr

numtest = int(raw_input())
while numtest != 0:
    cod()
    numtest -= 1
