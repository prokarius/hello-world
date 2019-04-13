# You can use wolfram alpha to find the threshold
# For 1001, the threshold is no threshold yay
def run(n):
    out = ['2']
    n -= 1
    if n%3 == 1:
        out += ['7']
    elif n%3 == 2:
        out += ['7','13']
    out += ['7','11','13'] * (n//3)
    return out

def main():
    # Scan in input
    userin = int(input())

    for _ in range(userin):
        n = int(input())
        print (' '.join(run(n)))

main()
