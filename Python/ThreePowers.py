end_of_file = "0"

threes = []
sub = 1

for i in range (64):
    threes.append (str(sub))
    sub *= 3

def code(N):
    if N == 1:
        print "{ }"
        return
    
    outputset = "{ "
    placeholder = N-1
    bin_str = str(bin(placeholder))
    binary_str = bin_str [2:]
    lengthy = len(binary_str)
    for i in range(lengthy):
        if binary_str[lengthy - 1 - i] == "1":
            outputset = outputset + threes[i] + ", "
    outputset = outputset[:-2] + " }"
    print outputset
    
while True:
    N = raw_input ()
    if N != end_of_file:
        code (int(N))
    else:
        break
