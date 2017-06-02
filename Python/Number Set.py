some_list = [True for i in range(1000000)]
some_list[0] = some_list[1] = False;
prime_list = []
for i in range(1000000):
    if not some_list[i]:
        continue
    prime_list.append(i)
    for j in range(i,1000000/i):
        some_list[j*i] = False

def findparent(x):
    global numlist
    if numlist[x] == x:
        return x
    else:
        numlist[x] = findparent (numlist[x])
        return numlist[x]

def union(x, y, output):
    global numlist
    xroot = findparent(x)
    yroot = findparent(y)
    if xroot != yroot:
        numlist[yroot] = xroot
        return output - 1
    return output
        
def u(p, l, output, num):
    left = (p - num) % p
    q =1+(len(l)-(1+left))/p
    for i in range (q):
        output = union (left, left + i*p, output)
    return output
    
def this(testc):
    global numlist
    R = raw_input()
    dlist = [int(x) for x in R.split(' ')]
    v = dlist[1] - dlist [0]+1
    numlist = [x for x in range(v)]
    output = v
    for i in prime_list:
        if i < dlist[1] - dlist[0]:
            if i >= dlist[2]:
                output = u(i, numlist, output, dlist[0])
    print "Case #" + str(testc+1) + ": " + str(output)


N = int(raw_input())
counter = 0
while counter < N:
    this(counter)
    counter += 1
