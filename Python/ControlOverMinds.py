potset = dict()
inglist = [-1 for x in range(500003)]
output = 0
counter = 0
numpots = int(raw_input())
while counter < numpots:
    R = raw_input()
    dlist = [int(x) for x in R.split(" ", 1)[1].split(' ')]
    dset = set(dlist)
    ph = set(dset)
    flag = True
    while len(dset) != 0:
        i = dset.pop()
        if inglist[i] != -1:
            dset.add(i)
            for j in potset[inglist[i]]:
                if j not in dset:
                    flag = False
                    break
                else:
                    dset.discard(j)
        if flag == False:
            break
    if flag == True:
        output += 1
        for i in ph:
            inglist [i] = counter
        potset[counter] = ph
    counter += 1
print output
