import math

def pad (l):
    l -= 1
    counter = 0
    while l != 0:
        l = l >> 1
        counter += 1
    return 2**counter

def fft (a,m,w):
    if m == 1:
        return a
    ae = [a[2*i] for i in range (m/2)]     
    ao = [a[2*i+1] for i in range (m/2)]
    fe = fft (ae, m/2, w*w)
    fo = fft (ao, m/2, w*w)
    F = [0 for i in range(m)]
    x = 1
    for j in range (m/2):
        F[j] = fe[j] + x*fo[j]
        F[j+m/2] = fe[j] - x*fo[j]
        x *= w
    return F
    
def code():
    Q = raw_input()
    R = raw_input()
    Q = raw_input()
    S = raw_input()
    dlist1 = [int(x) for x in R.split(' ')]
    dlist2 = [int(x) for x in S.split(' ')]
    final = len (dlist1) + len (dlist2) - 1
    variable = pad(final)
    while len (dlist1) < variable:
        dlist1.append(0)
    while len (dlist2) < variable:
        dlist2.append(0)
    w = complex(math.cos(2*math.pi/variable), math.sin(2*math.pi/variable))
    newd1 = fft (dlist1, variable, w)
    newd2 = fft (dlist2, variable, w)
    outputlist = []
    for i in range(variable):
        outputlist.append(newd1[i]*newd2[i])
    P = fft(outputlist, variable, 1.0/w)
    print str(final-1)
    outputstr = ""
    for i in range(final):
        P[i] /= variable
        b = P[i].real + 0.5
        if b < 0:
            b -= 1
        outputstr += str(int(b)) + " "
    print outputstr[:-1]
        
    
N = int(raw_input())
while N > 0:
    code ()
    N -= 1
    
