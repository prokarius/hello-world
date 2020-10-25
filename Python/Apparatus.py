from collections import defaultdict

MOD = 1000003

# Transpose the list of strings, where each string is of a known length
def transpose(lst, length):
    return list(map(lambda x: ''.join([elem[x] for elem in lst]), range(length)))

def factorial(n):
    out = 1
    for i in range(1, n+1):
        out *= i
    return out

def main():
    # Scan in input
    n, m = list(map(int, input().split()))

    switches = []
    lights = []

    # Switches stores the list of on / off positions for the switches, lights for lights
    for i in range(m):
        s = input()
        switches.append(s)

        l = input()
        lights.append(l)

        # Check if the number of 1s are the same in s and l
        if s.count('1') != l.count('1'):
            print("0")
            return

    # For each position, ensure that the types of on and off switches are represented in lights
    switchDict = defaultdict(int)
    lightsDict = defaultdict(int)

    for position in transpose(switches, n):
        switchDict[position] += 1

    for position in transpose(lights, n):
        lightsDict[position] += 1

    if not switchDict == lightsDict:
        print("0")
        return

    out = 1

    for k, v in switchDict.items():
        out = (out * factorial(v)) % MOD

    print(out)

if __name__ == "__main__":
    main()

