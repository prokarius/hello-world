def code (statement):
    dparray = []
    for i in "welcome to code jam":
        dparray.append (0)
    for i in statement:
        if i == "w":
            dparray[0] += 1
        elif i == "e":
            dparray[1] += dparray[0]
            dparray[6] += dparray[5]
            dparray[14] += dparray[13]
        elif i == "l":
            dparray[2] += dparray[1]
        elif i == "c":
            dparray[3] += dparray[2]
            dparray[11] += dparray[10]
        elif i == "o":
            dparray[4] += dparray[3]
            dparray[9] += dparray[8]
            dparray[12] += dparray[11]
        elif i == "m":
            dparray[5] += dparray[4]
            dparray[18] += dparray[17]
        elif i == " ":
            dparray[7] += dparray[6]
            dparray[10] += dparray[9]
            dparray[15] += dparray[14]
        elif i == "t":
            dparray[8] += dparray[7]
        elif i == "d":
            dparray[13] += dparray[12]
        elif i == "j":
            dparray[16] += dparray[15]
        elif i == "a":
            dparray[17] += dparray[16]
    output = str(dparray [-1] + 10000)
    print "Case #" + str(counter+1) + ": " + output [-4:]

N = int(raw_input())
counter = 0
while counter < N:
    statement = raw_input()
    code(statement)
    counter += 1
