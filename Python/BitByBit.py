def code (N):
    buff = ["?" for i in range (32)]
    while N > 0:
        N -= 1
        Q = raw_input()
        datl = [x for x in Q.split(' ')]
        if datl [0] == "SET":
            buff [int(datl[1])] = "1"
        elif datl [0] == "CLEAR":
            buff [int(datl[1])] = "0"
        elif datl[0] == "AND":
            if buff [int(datl[2])] == "0":
                buff [int(datl[1])] = "0"
            elif buff [int(datl[2])] == "?":
                if buff [int(datl[1])] != "0":
                    buff [int(datl[1])] = "?"
        elif datl[0] == "OR":
            if buff [int(datl[2])] == "1":
                buff [int(datl[1])] = "1"
            elif buff [int(datl[2])] == "?":
                if buff [int(datl[1])] != "1":
                    buff [int(datl[1])] = "?"
    outputstr = ""
    buff.reverse()
    for i in buff:
        outputstr += i
    print outputstr

N = int(raw_input())
while N != 0:
    code (N)
N = int(raw_input())
