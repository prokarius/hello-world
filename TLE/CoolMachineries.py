n = int(raw_input())
cmd = raw_input()
M = []
pos = (0,0)
for i in range(n):
    q = raw_input()
    ri = q.find('R')
    if ri != -1:
        pos = (i, ri)
    M.append(q)
res = -1
trail_length = [[[0 for x in range(n)] for y in range(n)] for z in range(n)]
found = False
newcmd = ""
loopStartState = [-1,-1,-1]
current = [pos[0], pos[1], 0]
while True:
    skipped = False
    if found:
        print current
        print loopStartState
        if current == loopStartState:
            if len(newcmd) == 0:
                res = 1
                break
            res = len(newcmd)
            for i in range (2, n+1):
                if len(newcmd)%i == 0:
                    cmplen = len(newcmd)/i
                    matched = 0
                    for j in range (0, len(newcmd),cmplen):
                        flag = True
                        for k in range (cmplen):
                            if newcmd[k] != newcmd[j+k]:
                                flag = False
                        if flag == True:
                            matched += 1
                    if matched == i:
                        res = cmplen
            break
    else:
        if trail_length[current[0]][current[1]][current[2]] != 0:
            loopStartState = current
            found = True
        else:
            trail_length[current[0]][current[1]][current[2]] = 1
    if cmd[current[2]] == "<":
        current = (current[0], current[1]-1, current[2])
        if M[current[0]][current[1]] == "#":
            current = (current[0], current[1]+1, current[2])
            skipped = True
    elif cmd[current[2]] == ">":
        current = (current[0], current[1]+1, current[2])
        if M[current[0]][current[1]] == "#":
            current = (current[0], current[1]-1, current[2])
            skipped = True
    elif cmd[current[2]] == "^":
        current = (current[0]-1, current[1], current[2])
        if M[current[0]][current[1]] == "#":
            current = (current[0]+1, current[1], current[2])
            skipped = True
    elif cmd[current[2]] == "v":
        current = (current[0]+1, current[1], current[2])
        if M[current[0]][current[1]] == "#":
            current = (current[0]-1, current[1], current[2])
            skipped = True
    if (not skipped) and found:
        newcmd += cmd[current[2]]
    current = [current[0], current[1], (current[2]+1)%len(cmd)]

if res == 0:
    res == 1
print res


"""

#PART 2#

print "192"
outputstr = ""
outputstr += "vv<<<^^^>>"
for i in range (91):
    outputstr += "v^"
print outputstr

outputstr = ""
for i in range(192):
    outputstr += "#"
print outputstr

outputstr = "##"
for i in range(38):
    outputstr += ".####"
print outputstr

outputstr = "##"
for i in range(38):
    outputstr += "....#"
print outputstr

outputstr1 = ""
for i in range(38):
    outputstr1 += "#..#."
outputstr1 += "##"

outputstr2 = ""
for i in range(38):
    outputstr2 += "##.#."
outputstr2 += "##"

for i in range(92):
    print outputstr1
    print outputstr2

outputstr = "#.."
for i in range(37):
    outputstr += "#...."
outputstr += "#..#"
print outputstr

outputstr = "##."
for i in range(186):
    outputstr += "#"
outputstr += "R##"
print outputstr

outputstr = "#"
for i in range(189):
    outputstr += "."
outputstr += "##"
print outputstr

outputstr = "##"
for i in range(94):
    outputstr += "#."
outputstr += "##"
print outputstr

outputstr = ""
for i in range(192):
    outputstr += "#"
print outputstr

"""
