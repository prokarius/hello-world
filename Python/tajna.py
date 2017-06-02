import math

N = raw_input()
length = len(N)
numrows = 0
listrows = int(math.sqrt (length))

for i in range (listrows):
    if length % (listrows-i) == 0:
        numrows = (listrows-i)
        break

columns = length / numrows

listostrs = []
placeholder = []
for i in range (numrows):
    placeholder = []
    for j in range (columns):
        placeholder.append (N[i + j*numrows])
    listostrs.append (placeholder)

output = ""
for i in range (numrows):
    for j in range (columns):
        output = output + listostrs[i][j]
print output
