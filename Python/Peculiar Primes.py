def code (N):
    Q = raw_input()
    primelist = [int(x) for x in Q.split (' ')]
    R = raw_input()
    bounds = [int(x) for x in R.split(' ')]
    output1 = [1]
    output2 = []
    for i in primelist:
        for j in output1:
            counter = j*i
            while counter <= bounds[1]:
                output2.append(counter)
                counter *= i
        for k in output2:
            output1.append(k)
        output2 = []
    output1.sort()

    outputstr = ""
    for i in output1:
        if i >= bounds[0] and i<= bounds[1]:
            outputstr += str(i) + ","
    if outputstr == "":
        print "none"
    else:
        print outputstr[:-1]

N = int(raw_input())
while N != 0:
    code(N)
    N = int(raw_input())
