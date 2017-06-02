N = raw_input()
outputstr = ""
i = 0
while i < len(N)-2:
    r = b = l = False
    for j in range(3):
        if N[i+j] == "R":
            r = True
        elif N[i+j] == "B":
            b = True
        else:
            l = True
    if (r and b) and l:
        outputstr += "C"
        i += 3
    else:
        if N[i] == "R":
            outputstr += "S"
        elif N[i] == "B":
            outputstr += "K"
        else:
            outputstr += "H"
        i+= 1

while i < len(N):
    if N[i] == "R":
        outputstr += "S"
    elif N[i] == "B":
        outputstr += "K"
    else:
        outputstr += "H"
    i+= 1

print outputstr
