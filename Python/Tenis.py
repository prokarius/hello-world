def check(player1, score1, player2, score2, num_set):
    # Swap so that score1 > score2
    if (score1 < score2):
        player1, player2, score1, score2 = player2, player1, score2, score1

    # Federer check
    if (player2 == 'federer' and score2 < score1):
        return False

    # Check that the winner has won at least 6
    if score1 < 6:
        return False

    # If the winner scores 6 points, then opponent needs to score <4 for a valid game
    if score1 == 6:
        return score2 < 5

    # If this is only the 1st or 2nd game then it can only be true if 7:5 or 7:6
    if (num_set < 3):
        if (score1 > 7):
            return False
        # score1 == 7, check that score2 == 5 or 6
        if (score2 == 5) or (score2 == 6):
            return True
        return False

    # If this is the 3rd game, then the winner needs to win by +2 points
    if (num_set == 3):
        return (score1 == score2 + 2)

def main():
    # Scan in input
    player1, player2 = input().split(' ')
    num_matches = int(input())

    for match in range(num_matches):
        out = True
        matches = input().split(' ')
        wins1 = wins2 = 0

        # Guard: If there are more than 3 matches or only 1 match, something is wrong
        if (len(matches) > 3) or (len(matches) < 2):
            print('ne')
            continue

        for idx, match in enumerate(matches):
            # First check if someone already won. Why are we still playing?
            if wins1 == 2 or wins2 == 2:
                out = False
                break

            score1, score2 = map(int, match.split(':'))

            # Check if the set is valid
            out = out and check(player1, score1, player2, score2, idx+1)

            # Break if the game is not valid
            if not out:
                break

            # Add to their score
            if score1 > score2:
                wins1 += 1
            elif score2 > score1:
                wins2 += 1

        # Did anyone even win?
        out = out and ((wins1 == 2) or (wins2 == 2))
        print("da" if out else "ne")


if __name__ == '__main__':
    main()

