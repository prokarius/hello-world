def mainc(N):
    coords = [int(x) for x in N.split()]
    print "Total " + str (coords[0] * coords[1])
    office = [[[] for i in range(coords[1])] for j in range(coords[0])]
    numemp = int(raw_input())
    emp = []
    output =[0 for x in range(numemp+2)]
    cunt = 0
    while cunt < numemp:
        R = raw_input()
        dlist = [x for x in R.split(' ')]
        emp.append(dlist[0])
        for i in range(int(dlist[1]),int(dlist[3])):
            for j in range (int(dlist[2]),int(dlist[4])):
                office[i][j].append(cunt)
        cunt += 1
    for i in range(coords[0]):
        for j in range(coords[1]):
            if len(office[i][j]) == 0:
                output[-1] += 1
            elif len(office[i][j]) > 1:
                output[-2] += 1
            else:
                output[office[i][j][0]] += 1
    print "Unallocated " + str(output[-1])
    print "Contested " + str(output[-2])
    for i in range(numemp):
        print emp[i] + " " + str(output[i])

while True:
    try:
        N = raw_input()
        mainc(N)
    except (EOFError):
        break


