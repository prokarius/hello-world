def main():
    # Scan in input
    dlist = input().split(" ")

    n = int(dlist[0])
    k = int(dlist[1])

    competitors = []

    for _ in range(n):
        dlist = input().split(" ")
        competitors.append((int(dlist[1]), dlist[0]))

    # Sort dlist
    competitors.sort()
    competitors.reverse()

    winners = []
    # Note that since each competitor needs to at least double the previous bet,
    # we can just use a greedy solution
    curr = 0
    while (curr < len(competitors)):
        if (k >= competitors[curr][0]):
            winners.append(competitors[curr][1])
            k -= competitors[curr][0]
        curr += 1

    # Check if the sum to k
    if (k != 0):
        print ("0")
        return

    # Else print the list of names
    print (len(winners))
    print ("\n".join(winners))

main()
