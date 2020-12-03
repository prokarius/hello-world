def order(color, e):
    if color == 'black':
        value = 90 - e[1]*10
    else:
        value = e[1]*10

    value += e[2]

    mapping = {
        'K': 300,
        'Q': 400,
        'R': 500,
        'B': 600,
        'N': 700,
        '': 800
    }


    value += mapping[e[0]]
    return value

def convert(x):
    mapping = {
        1: 'a',
        2: 'b',
        3: 'c',
        4: 'd',
        5: 'e',
        6: 'f',
        7: 'g',
        8: 'h',
    }

    return f"{x[0]}{mapping[x[2]]}{x[1]}"


def main():
    white_pieces = []
    black_pieces = []

    # Scan in input
    for i in range(8, 0, -1):
        input()  # Useless
        row = input()

        # Literally just check each of the rows lol
        # There should be a more elegant way, but nyeeh
        for x in range(1, 9):
            j = x*4 - 2
            if row[j] == 'P':
                white_pieces.append(('', i, x))
            elif row[j] == 'p':
                black_pieces.append(('', i, x))
            elif row[j] == 'N':
                white_pieces.append(('N', i, x))
            elif row[j] == 'n':
                black_pieces.append(('N', i, x))
            elif row[j] == 'B':
                white_pieces.append(('B', i, x))
            elif row[j] == 'b':
                black_pieces.append(('B', i, x))
            elif row[j] == 'R':
                white_pieces.append(('R', i, x))
            elif row[j] == 'r':
                black_pieces.append(('R', i, x))
            elif row[j] == 'Q':
                white_pieces.append(('Q', i, x))
            elif row[j] == 'q':
                black_pieces.append(('Q', i, x))
            elif row[j] == 'K':
                white_pieces.append(('K', i, x))
            elif row[j] == 'k':
                black_pieces.append(('K', i, x))

    # Right, now we just need to sort
    white_pieces.sort(key=lambda x: order('white', x))
    black_pieces.sort(key=lambda x: order('black', x))

    print(f"White: {','.join(map(convert, white_pieces))}")
    print(f"Black: {','.join(map(convert, black_pieces))}")

if __name__ == '__main__':
    main()

