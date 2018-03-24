# For a mobile to be correct, 2**depth * weight has to be equal for all weights
# Hence we populate a dict. Then take N - max(values), N is total number of weights

m = [2**x for x in range(18)]

def output (lst, depth):
    if type(lst) != list:
        # It is a number
        z = m[depth]*lst
        if z in b:
            b[z] = b[z] + 1
        else:
            b[z] = 1
    else:
        # It is a list
        output (lst[0], depth + 1)
        output (lst[1], depth + 1)

T = int(input())
while T>0:
    a = eval(input())
    b = {}
    N = 0
    c = 0
    output (a, 0)
    for k,v in b.items():
        N += v
        c = max(c, v)
    print (N-c)
    T -= 1
