def code(lst):
    global clist
    if clist [lst[0]][lst[1]] == 1:
        return 1
    summ = lst[0] + lst[1]
    diff = lst[0] - lst[1]
    for i in range(N):
        clist[lst[0]][i] = 1
        clist[i][lst[1]] = 1
    if summ < N:
        i = 0
        while i <= summ:
            clist[i][summ - i] = 1
            i += 1
    else:
        i = N-1
        while i > summ-N:
            clist[i][summ - i] = 1
            i -= 1
    if diff >= 0:
        i = 0
        while i < N - diff:
            clist[diff + i][i] = 1
            i += 1
    else:
        i = 0
        while i < N + diff:
            clist[i][i - diff] = 1
            i += 1
    return 0

N = 8
phlist = []
clist = []
for i in range(N):
    phlist.append(0)
for i in range(N):
    clist.append (list(phlist))

queens = 0
count = 0
flag = True
while count < 8:
    R = raw_input()
    for i in range(8):
        if R[i] == "*":
            queens += 1
            if code([count, i]) == 1:
                flag = False
                break
    count += 1
if queens != 8:
    flag == False
if flag == True:
    print "valid"
else:
    print "invalid"

