op = ["+", "-", "*", "/"]
out = {}

for i in op:
    for j in op:
        for k in op:
            exp = "4" + "4".join([i, j, k]) + "4"
            out[eval(exp)] = exp

numtests = int(raw_input())
for _ in range(numtests):
    num = int(raw_input())
    if num not in out:
        print ("no solution")
    else:
        print (" ".join(out[num]) + " = " + str(num))

