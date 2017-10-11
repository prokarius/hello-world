def bumper (l1, l2, d):
    c1.append (2000000)
    c2.append (2000000)
    #Assume car1 is infront
    #d is the distance difference
    i = j = 1
    t = 0
    s1 = s2 = False
    #They start out stationary
    while i < len (l1)-1 or j <len (l2)-1:
        if l1[i] < l2[j]:
            #ph = time elapsed
            ph = l1[i] - t
            if s1:
                d += ph
            s1 = not s1
            if s2:
                d -= ph
            t = l1[i]
            i += 1
        else:
            ph = l2[j] - t
            if s2:
                d -= ph
            s2 = not s2
            if s1:
                d += ph
            t = l2[j]
            j += 1
        if d < 0:
            output = (1+t) + d
            print "bumper tap at time " + str(output)
            return
    if s2 and not s1:
        output = (1+t) + d
        print "bumper tap at time " + str(output)
    else:
        print "safe and sound"

n = raw_input ()
dlist = [int (x) for x in n.split ()]
d = dlist[0]-dlist[1]
n = raw_input ()
c1 = [int (x) for x in n.split ()]
n = raw_input ()
c2 = [int (x) for x in n.split ()]

if d>0:
    bumper (c1, c2, d-5)
else:
bumper (c2, c1, -d-5)
