def main():
    # Scan in input
    dlist = input().split()
    n = int(dlist[0])
    p = int(dlist[1])
    m = int(dlist[2])

    players = {}
    winner = False
    for i in range(n):
        players[input()] = 0

    # Scan each player's score
    for i in range(m):
        dlist = input().split()
        player = dlist[0]
        score = int(dlist[1])

        # This flag is to ensure we only process each winner once
        flag = players[player] < p
        players[player] += score

        if flag and players[player] >= p:
            winner = True
            print(f"{player} wins!")

    # Bummer, no one won
    if not winner:
        print("No winner!")

if __name__ == '__main__':
    main()

