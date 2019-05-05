mapping = {
    "+" : lambda x, y:(x+y),
    "-" : lambda x, y:(x-y),
    "*" : lambda x, y:(x*y),
    "/" : lambda x, y:(x/y if x%y == 0 else -37)
}

alphabet = "0123456789abcdefghijklmnopqrstuvwxyz0"

def run():
    # Scan in input
    dstr = input()
    eqn = dstr.split(" ")
    a = eqn[0]
    b = eqn[2]
    c = eqn[4]

    op = mapping[eqn[1]]

    possible = True

    # Find which of the traditional bases works
    bases=[]
    for base in range(36,1,-1):
        try:
            x = int(a, base)
            y = int(b, base)
            z = int(c, base)

            if op(x,y) == z:
                bases.append(base)

        # If they dont, dont bother checking Base 1
        except:
            possible = False
            break

    # Recall base 1 is only possible if there are no 0s
    if possible and '0' not in dstr:
        if op(len(eqn[0]), len(eqn[2])) == len(eqn[4]):
            bases.append(1)

    # We appended backward, reverse to make it forward again.
    bases.reverse()

    # Check to see if we have any possible bases
    if (len(bases) > 0):
        print("".join(map(lambda x: alphabet[x], bases)))
    else:
        print("invalid")

def main():
    # Scan in testcases
    testcases = int(input())
    for i in range(testcases):
        run()

main()

