def decbin (num):
    outputstr = ""
    while num != 0:
        if num%2 == 0:
            outputstr += "0"
        else:
            outputstr += "1"
        num /= 2
    q = ""
    for i in range(len(outputstr)-1):
        q += outputstr[len(outputstr)-i-2]
    return q

def bindec (string):
    mul = 1
    output = 0
    for i in string:
        output += int(i)*mul
        mul *= 2
    return output

def takef (string):
    a = 1
    b = 1
    for i in string:
        if i == "0":
            b += a
        else:
            a += b
    return str(a) + "/" + str(b)

def getf (a,b, outputstr):
    if (a == 0 or b == 0):
        q = outputstr[:-1] + "1"
        return q
    if (a > b):
        outputstr += a/b * "1"
        return getf(a%b, b, outputstr)
    else:
        outputstr += b/a * "0"
        return getf(a, b%a, outputstr)
    

def cod():
    raw = raw_input()
    d = [x for x in raw.split()]
    dlist = [int(x) for x in d[1].split('/')]
    result = getf(dlist[0], dlist[1], "")
    print result
    the = bindec (result)+1
    print the
    answer = decbin (the)
    print answer
    print str(d[0]) + " " + takef(answer)

numtest = int(raw_input())
while (numtest > 0):
    cod ()
    numtest -= 1
