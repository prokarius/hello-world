passwordlist = []
output = 0.0

num = int(raw_input())
i = 0

while i < num:
    N = raw_input()
    data = [x for x in N.split()]
    prob = float(data[1])
    passwordlist.append (prob)
    i += 1


passwordlist.sort()
passwordlist.reverse()


for i in range(len(passwordlist)):
    output += passwordlist[i]*(i+1)

print output
