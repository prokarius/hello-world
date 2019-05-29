def solve(letters, weight):
    # Too letter weight
    if (weight < letters):
        return "impossible"

    # Too much weight
    if (weight > letters * 26):
        return "impossible"

    out = []

    # Keep subtracting letters until weight < 52
    while (weight >= 26):
        letters -= 1
        weight -= 26
        out.append("z")

    # If we have less weight than letters, remove a z
    if (weight < letters):
        out.pop()
        weight += 26
        letters += 1

    # Append a's until we have 1 letter left
    while (letters > 1):
        out.append("a")
        letters -= 1
        weight -= 1

    # Last letter (if present) will be what's left
    if (letters == 1):
        out.append(chr(96 + weight))

    return "".join(out)


dlist = input().split(' ')
print (solve(int(dlist[0]), int(dlist[1])))
