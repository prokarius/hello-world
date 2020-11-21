mapping = {
    "a": "2",
    "b": "2",
    "c": "2",
    "d": "3",
    "e": "3",
    "f": "3",
    "g": "4",
    "h": "4",
    "i": "4",
    "j": "5",
    "k": "5",
    "l": "5",
    "m": "6",
    "n": "6",
    "o": "6",
    "p": "7",
    "q": "7",
    "r": "7",
    "s": "7",
    "t": "8",
    "u": "8",
    "v": "8",
    "w": "9",
    "x": "9",
    "y": "9",
    "z": "9",
}

# Scan in input
num_words = int(input())

out = 0

words = []
for i in range(num_words):
    words.append(input())

numbers = input()

# For each word, check if each letter is correct
for word in words:
    if len(word) != len(numbers):
        continue
    flag = True
    for i in range(len(word)):
        if mapping[word[i]] != numbers[i]:
            flag = False
            break

    out += flag

print(out)

