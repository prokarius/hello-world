def code(N):
    datalist = [int(x) for x in N.split(' ')]
    counter = 0
    winloselist = []
    while counter < datalist[0]:
        winloselist.append ([0,0])
        counter += 1
    numgames = datalist[0]*(datalist[0]-1)*datalist[1]/2
    counter = 0
    while counter < numgames:
        game = raw_input()
        gamedata = [str(x) for x in game.split(' ')]
        for i in [1,3]:
            gamedata [i-1] = int (gamedata[i-1])-1
            if gamedata [i] == "rock":
                gamedata [i] = 0
            elif gamedata [i] == "paper":
                gamedata [i] = 1
            else:
                gamedata [i] = 2
        state = (gamedata [1] - gamedata [3])%3
        if state == 1:
            winloselist[gamedata[0]][0]+=1
            winloselist[gamedata[2]][1]+=1
        elif state == 2:
            winloselist[gamedata[2]][0]+=1
            winloselist[gamedata[0]][1]+=1
        counter += 1
    for i in winloselist:
        if i[0]+i[1] != 0:
            if i[1] != 0:
                if i[0] != 0:
                    newvalue = ""
                    value = 10000*i[0]/(i[0]+i[1])
                    print value
                    if value%10 > 4:
                        newvalue = str((value/10) + 1)
                    else:
                        newvalue = str(value/10)
                    length = len(newvalue)
                    print "0." + (3-length)*"0" + newvalue
                else:
                    print "0.000"
            else:
                print "1.000"
        else:
            print "-"
            
N = raw_input()

while True:
    if N != "0":
        code (N)
        N = raw_input()
    else:
        break
