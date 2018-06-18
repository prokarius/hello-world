def code ():
    N = raw_input()
    datalist = [int(x) for x in N.split(' ')]
    if datalist [1] == 1:
        Q = int(raw_input())
        antleft = Q
        antright = datalist [0] - Q
        fastest = min(antleft, antright)
        slowest = max(antleft, antright)
    else:
        numant = 0
        antlist = []
        while len(antlist) != datalist[1]:
            Q = raw_input()
            appendant = [int(x) for x in Q.split(' ')]
            antlist += appendant

        antlist.sort()

        slowest = max(datalist[0] - antlist[0], antlist[-1])

        middle = datalist[0]/2
        newlistleft = []
        antright = 0
        for i in antlist:
            if i < middle:
                newlistleft.append (i)
            else:
                antright = datalist[0] - i
                break
        antleft = newlistleft[-1]
        fastest = max(antleft, antright)

    print str(fastest) + " " + str(slowest)

numtest = int(raw_input())
while numtest > 0:
    code ()
    numtest -= 1
