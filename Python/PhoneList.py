def solve():
    # Scan in input
    n = int(input())

    numbers = []
    for i in range(n):
        numbers.append(input())

    # Cheese this by sorting
    numbers.sort()

    # For each number, it can only potentially be a prefix of the next number:
    for i in range(n-1):
        if len(numbers[i]) > len(numbers[i+1]):
            continue
        if numbers[i+1][:len(numbers[i])] == numbers[i]:
            print ("NO")
            return

    # The list is OK
    print("YES")


def main():
    numTestcases = int(input())
    for i in range(numTestcases):
        solve()

if __name__ == '__main__':
    main()

