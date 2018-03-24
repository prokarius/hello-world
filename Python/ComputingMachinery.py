N = raw_input()
datalist = [int(x) for x in N.split(' ')]
Q = raw_input()
qnlist = [int(x) for x in Q.split(' ')]

timer = 0
penalty = 0
numqn = 0

if qnlist [datalist[1]] > 301:
    print "0 0"
else:
    timer += qnlist [datalist[1]]
    qnlist.pop(datalist[1])
    qnlist.sort()
    while timer < 301:
        try:
            penalty += timer
            numqn += 1
            timer += qnlist[0]
            qnlist.pop(0)
        except (IndexError):
            break
    print str(numqn) + " " + str(penalty)
