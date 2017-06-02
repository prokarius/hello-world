worthless = raw_input()
N = raw_input()
datalist = [int(x) for x in N.split(' ')]
newdata = list(datalist)
largenumlist = []
maxi = newdata [0]
for i in newdata:
    if maxi < i:
        maxi = i
    largenumlist.append(maxi)

newdata.sort()

counter = 0
for i in range(len(datalist)):
    if newdata[i] == datalist[i]:
        if newdata [i] == largenumlist [i]:
            counter += 1

print counter
