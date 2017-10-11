def code (N):
    jackjill = [int(x) for x in N.split(" ")]
    counter = 0
    jack = []
    jill = []
    while counter < jackjill[0]:
        q = int(raw_input ())
        jack.append (q)
        counter += 1
    counter = 0
    while counter < jackjill[1]:
        p = int(raw_input())
        jill.append (p)
        counter += 1
    jackcount = 0
    jillcount = 0
    cd = 0
    while not((jackcount == jackjill[0]) or (jillcount == jackjill[1])):
        if jack [jackcount] == jill [jillcount]:
            cd += 1
            jackcount += 1
        elif jack [jackcount] > jill [jillcount]:
            jillcount += 1
        else:
            jackcount += 1
    print c

N = raw_input ()

while True:
    if N != "0 0":
        code (N)
        N = raw_input ()
    else:
        break
