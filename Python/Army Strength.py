def code ():
    worthless2 = raw_input()
    data = raw_input()
    NG = [int(x) for x in data.split(' ')]
    data = raw_input()
    NM = [int(x) for x in data.split(' ')] 
    NG.sort()
    NG.reverse()
    NM.sort()
    NM.reverse()
    while (NG != []) and (NM != []):
        if NM[-1] <= NG[-1]:
            NM.pop()
        else:
            NG.pop()
    if NM == []:
        print "Godzilla"
    else:
        print "MechaGodzilla"

numcases = int(raw_input())
while numcases > 0:
    worthless = raw_input()
    code()
    numcases -= 1
