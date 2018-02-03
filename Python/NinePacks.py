def buildlist (thesum, alist):
    thelist = [10000 for i in range(thesum+1)]
    for i in alist:
        for j in range(thesum):
            if thelist[thesum-j] != 10000:
                if thelist[i+thesum-j] > thelist[thesum-j] + 1:
                    thelist[i+thesum-j] = thelist[thesum-j] + 1
        thelist[i] = 1
    return thelist

N = raw_input()
M = raw_input()

dog = [int(x) for x in N.split()]
bun = [int(x) for x in M.split()]

dog.reverse()
bun.reverse()

dog.pop()
bun.pop()

sumdog = 0
for i in dog:
    sumdog += i

doglist = buildlist(sumdog, dog)

sumbun = 0
for i in bun:
    sumbun += i

bunlist = buildlist(sumbun, bun)

themax = 100000
for i in range(min(sumdog, sumbun)+1):
    if bunlist[i] < 10000 and doglist[i] < 10000:
        check = bunlist[i] + doglist[i]
        themax = min(themax, check)
if themax != 100000:
    print themax
else:
    print "impossible"
