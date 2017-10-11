import math

def bungee (data):
    datl = [float(x) for x in data.split(' ')]
    Ebottom = 9.81*datl[3]*datl[2]
    if datl[2] > datl[1]:
        Ebottom -= datl[0]*((datl[2]-datl[1])**2)/2.0
    if Ebottom < 0:
        print "Stuck in the air."
    else:
        speed = 2.0*Ebottom/datl[3]
        if speed > 100:
            print "Killed by the impact."
        else:
            print "James Bond survives."

N = raw_input()
while N != "0 0 0 0":
    bungee (N)
    N = raw_input()
