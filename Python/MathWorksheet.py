def main(n):
    # n holds the number of equations
    sollist = []
    maxlength = 0

    # Solve each equation
    for _ in range(n):
        answer = str(input())
        sollist.append(answer)
        maxlength = max(maxlength, len(answer) + 1)

    # Find out how many equations in a line, and how many lines
    eqninline = 50 / maxlength
    numlines = ((n-1) / eqninline) + 1

    # Build each line and print
    counter = 0
    for i in range(numlines):
        out = []
        try:
            for j in range(eqninline):
                output = sollist[counter]
                out.append(" " * (maxlength - len(output) - 1))
                out.append(output)
                out.append(" ")
                counter += 1
            print "".join(out)[:-1]
        except IndexError:
            print "".join(out)[:-1]

# Scan in input
n = input()
while n != 0:
    main(n)
    n = input()
    if n != 0:
        print("")
