def solve():
    string = input()
    length = len(string)

    # Do KMP
    LPS = [0]*length
    prefix = 0
    i = 1;
    while(i < length):
        if (string[i] == string[prefix]):
            prefix += 1
            LPS[i] = prefix
            i += 1
        elif (prefix > 0):
            prefix = LPS[prefix-1]
        else:
            LPS[i] = 0
            i += 1

    print(length - LPS[length-1])

def main():
    testcases = int(input())
    for i in range(testcases):
        solve()

if __name__ == '__main__':
    main()

