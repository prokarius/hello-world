namedict = {} #Dict of names to dict
count = {} #Dict of words

n = input()
while (n):
    ph = raw_input()
    dlist = ph.split()
    name = dlist[0]
    # Try to push words into each name
    # If it not there create the new name
    # Do the same for the count of each word
    for i in range (1, len(dlist)):
        word = dlist[i]
        try:
            namedict[name].add(word)
        except KeyError:
            a = set()
            a.add(word)
            namedict[name] = a

        try:
            count[word] = count[word] + 1
        except KeyError:
            count[word] = 1
    n -= 1

flag = True
intersect = {}

# Find the intersection of all sets (efficiently)
for k, v in namedict.iteritems():
    if flag:
        intersect = v
        flag = False
    else:
        newset = set()
        for i in intersect:
            if i in v:
                newset.add(i)
        intersect = newset

# Append, sort, print
outlist = []
for i in intersect:
    outlist.append((-count[i], i))

outlist.sort()

if len(outlist) == 0:
    print "ALL CLEAR"
else:
    for i in outlist:
        print i[1]
