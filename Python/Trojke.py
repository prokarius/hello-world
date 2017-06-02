numlines = int(raw_input())
pos = []
linecount = 0
while linecount < numlines:
    dataline = raw_input()
    for i in range(len(dataline)):
        if dataline[i] != ".":
            pos.append((linecount, i))
    linecount += 1

length = len(pos)

counter = 0
for i in range(length-2):
    for j in range(i+1, length-1):
        for k in range(j+1, length):
            v1 = (pos[i][0]-pos[j][0],pos[i][1]-pos[j][1])
            v2 = (pos[i][0]-pos[k][0],pos[i][1]-pos[k][1])
            if v1[0]*v2[1] == v1[1]*v2[0]:
                counter += 1
print counter
