import math

def bungee (data):
    datl = [float(x) for x in data.split(' ')]
    datl[3] *= 1000000000
    datl[0] *= 1000000000
    Ebottom = 9.81*datl[3]*datl[2] - datl[0]*((datl[2]-datl[1])**2)/2.0
    if Ebottom < 0:
        print "Stuck in the air."
    else:
        speed = math.sqrt(2.0*Ebottom/datl[3])
        print speed
        if speed > 10:
            print "Killed by the impact."
        else:
            print "James Bond survives."

N = raw_input()
while N != "0 0 0 0":
    bungee (N)
    N = raw_input()
