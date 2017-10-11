n = input()
while (n != 0):
    ph = raw_input()
    d = [int(x) for x in ph.split()]
    d.sort()
    o = [str(d[0])+"-A"]
    h = True
    for i in range(len(d)-1, 0, -1):
        h = not h
        if h:
            o.append(str(d[i]) + "-A")
        else:
            o.append(str(d[i]) + "-B")
    print " ".join(o)
    n = input()
