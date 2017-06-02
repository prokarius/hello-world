import sys

N = raw_input()

word = N
countletters = {}
counts = []
listdicts = []
length = len (N)

some_list = range (2,250)
prime_list = []
while some_list:
    prime = some_list.pop(0)
    prime_list.append(prime)
    for j in some_list:
        if j % prime == 0:
            some_list.remove(j)

def gcdfunc (a, b):
    if b > a:
        a,b = b,a
    if a % b == 0:
        return b
    else:
        return gcdfunc(b, a%b)

for i in set(N):
    countletters [i] = 0

for i in list(N):
    countletters [i] = countletters [i] + 1
    listdicts.append(dict(countletters))

for key in countletters:
    counts.append(countletters[key])
    
if len (counts) == 1:
    print N[0]
else:
    while len(counts) != 1:
        a = counts.pop(0)
        b = counts.pop(0)
        counts.append(gcdfunc(a, b))
        
tempte = counts [0]
factorisation = []
for i in prime_list:
    if tempte%i == 0:
        counter = 0
        while tempte%i == 0:
            tempte = tempte // i
            counter += 1
        if counter != 0:
            factorisation.append ((i, counter))
        if tempte == 1:
            break

listfactors = set([1])
for i in factorisation:
    newlist = []
    for j in range(i[1]):
        for k in listfactors:
            newlist.append (k*(i[0]**(j+1)))
    for q in newlist:
        listfactors.add(q)
        
listfactors = list(listfactors)
listfactors.sort()
listfactors.pop(0)
listfactors.reverse()

for i in listfactors:
    dicttarget = dict(listdicts[0])
    passed = True
    for key, value in countletters.items():
        dicttarget [key] = value/i
    for j in range (i-1):
        for key2, value2 in listdicts [((j+1)*length/i)-1].items():
            if value2 != dicttarget[key2]*(j+1):
                passed = False
                break
        if passed:
            print word[:length/i]
            sys.exit()
        else:
            break
        
