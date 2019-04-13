def run():
    num_children = int(input())
    candies = []
    for _ in range (num_children):
        candies.append(int(input()))
    print ("YES" if sum(candies) % num_children == 0 else "NO")

def main():
    testcases = int(input())
    for _ in range(testcases):
        input()
        run()

main()
