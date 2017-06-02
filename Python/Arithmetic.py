N = raw_input()
binstr = ""
for i in N:
    if i == "0":
        binstr += "000"
    elif i == "1":
        binstr += "001"
    elif i == "2":
        binstr += "010"
    elif i == "3":
        binstr += "011"
    elif i == "4":
        binstr += "100"
    elif i == "5":
        binstr += "101"
    elif i == "6":
        binstr += "110"
    elif i == "7":
        binstr += "111"

binstr = (4-(len(binstr)%4))* "0" + binstr

output = ""

while binstr:
    totest = binstr [-4:]
    binstr = binstr [:-4]
    if totest [0] == "0":
        if totest [1] == "0":
            if totest [2] == "0":
                if totest [3] == "0":
                    output = "0" + output
                else:
                    output = "1" + output
            else:
                if totest [3] == "0":
                    output = "2" + output                
                else:
                    output = "3" + output
        else:
            if totest [2] == "0":
                if totest [3] == "0":
                    output = "4" + output
                else:
                    output = "5" + output
            else:
                if totest [3] == "0":
                    output = "6" + output                
                else:
                    output = "7" + output
    else:
        if totest [1] == "0":
            if totest [2] == "0":
                if totest [3] == "0":
                    output = "8" + output
                else:
                    output = "9" + output
            else:
                if totest [3] == "0":
                    output = "A" + output                
                else:
                    output = "B" + output
        else:
            if totest [2] == "0":
                if totest [3] == "0":
                    output = "C" + output
                else:
                    output = "D" + output
            else:
                if totest [3] == "0":
                    output = "E" + output                
                else:
                    output = "F" + output

try:
    while output [0] == "0":
        output = output [1:]
    print output
except (IndexError):
    print "0"
