datalist = []
numlist = []
square = [0,0]

for i in range (3):
    N = raw_input()
    M = [int (x) for x in N.split (' ')]
    datalist.append(list(M))
    for i in M:
        numlist.append (i)

print numlist

'''
if datalist [0][0] == datalist [1][0] and datalist [1][0] == datalist [2][0]:
    if (datalist [0][1]+datalist [1][1]+ datalist [2][1] == datalist [1][0]):
        print "YES"
'''
    
for i in range(6):
    for j in range (i):
        if numlist [i] = numlist [i+j]
