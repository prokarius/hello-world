from collections import Counter

def main():
    # Scan in input
    n = int(input())

    DOM = []
    Kattis = []

    for i in range(n):
        DOM.append(input())
    DOM = Counter(DOM)

    for i in range(n):
        Kattis.append(input())
    Kattis = Counter(Kattis)

    out = 0

    for key, DOM_value in DOM.items():
        Kattis_value = Kattis.get(key, 0)
        out += min(DOM_value, Kattis_value)

    print (out)

if __name__ == '__main__':
    main()

