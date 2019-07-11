def solve():
    noises = input().split(" ")
    sentence = input()
    while sentence != "what does the fox say?":
        word = sentence.split(" ")[-1]
        noises = list(filter(lambda x: x != word, noises))
        sentence = input()

    print (" ".join(noises))

testcases = int(input())

for i in range(testcases):
solve()
