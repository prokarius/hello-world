slut = [0,0,1,3,6,10,15,21,28,36,45]

def ds (N):
    output = 0
    mult = 1
    N += 1
    t = N
    while t != 0:
        output += mult * 45 * (t/10) + mult * slut [t%10] + (N%mult)*(t%10)
        mult *= 10
        t /= 10
    return output

def code():
    R = raw_input()
    dlist = [int (x) for x in R.split(' ')]
    print ds(dlist [1]) - ds(dlist [0]-1)

numcases = int(raw_input())
while numcases > 0:
    code ()
    numcases -= 1
