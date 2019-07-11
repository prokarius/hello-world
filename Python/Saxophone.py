mapping = {
    'c': [1, 2, 3, 6, 7, 8, 9],
    'd': [1, 2, 3, 6, 7, 8],
    'e': [1, 2, 3, 6, 7],
    'f': [1, 2, 3, 6],
    'g': [1, 2, 3],
    'a': [1, 2],
    'b': [1],
    'C': [2],
    'D': [0, 1, 2, 3, 6, 7, 8],
    'E': [0, 1, 2, 3, 6, 7],
    'F': [0, 1, 2, 3, 6],
    'G': [0, 1, 2, 3],
    'A': [0, 1, 2],
    'B': [0, 1]
}

def solve():
    output = [0]*10
    curr = set()

    song = input()
    for note in song:
        for finger in mapping[note]:
            if finger not in curr:
                output[finger] += 1
        curr = set(mapping[note])

    print (" ".join(map(str, output)))

testcases = int(input())
for _ in range(testcases):
    solve()
