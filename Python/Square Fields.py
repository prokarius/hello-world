def calc (num_points, num_boxes, min_size):
    global output, boxlist
    if (num_boxes > k) or (min_size >= output):
        return
    if (num_points == n):
        output = min(output,min_size)
        return
    for i in range (num_boxes+1):
        ph = list(boxlist[i])
        boxlist[i][0] = min(boxlist[i][0], x[num_points])
        boxlist[i][1] = max(boxlist[i][1], x[num_points])
        boxlist[i][2] = min(boxlist[i][2], y[num_points])
        boxlist[i][3] = max(boxlist[i][3], y[num_points])
        calc (num_points+1, max(num_boxes, i+1), max(min_size, boxlist[i][1]-boxlist[i][0], boxlist[i][3]-boxlist[i][2]))
        boxlist[i] = ph
        

def clean ():
    global output, boxlist, x, y
    output = 1000000
    boxlist = [[65000, 0, 65000, 0] for w in range(16)]
    x = [0 for w in range (16)]
    y = [0 for w in range (16)]

T = int(raw_input())
q = 1
while (q <= T):
    clean()
    a = raw_input()
    dlist = [int(w) for w in a.split()]
    n = dlist[0]
    k = dlist[1]
    for l in range(n):
        c = raw_input()
        dlist = [int(w) for w in c.split()]
        x[l] = dlist[0]
        y[l] = dlist[1]
    calc(0,0,0)
    print "Case #" + str(q) + ": " + str(output)
    q += 1
