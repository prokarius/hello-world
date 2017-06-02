N = int(raw_input())
counter = 0
temperature = [-1, 1000]
templist = []
while N > 0:
    N -= 1
    temp = raw_input()
    minions = templist.append(tuple(int(x) for x in temp.split(' ')))
templist.sort()
templist.reverse()
while templist != []:
    minion = templist.pop()
    temperature [0] = max (minion [0], temperature [0])
    temperature [1] = min (minion [1], temperature [1])
    if temperature [1] < temperature [0]:
        counter += 1
        temperature = [minion [0], minion [1]]
counter += 1
print counter
