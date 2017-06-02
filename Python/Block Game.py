N = raw_input()
datalist = [int(x) for x in N.split(' ')]
datalist.sort()
state = True

while True:
    if datalist[1] % datalist[0] == 0 or datalist[1]/datalist[0] > 1:
        if state == True:
            print "win"
            break
        else:
            print "lose"
            break
    else:
        datalist[1], datalist[0] = datalist[0], datalist[1]-datalist[0]
        state = not state
