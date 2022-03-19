from collections import Counter
import math

def main():
    # Scan in input
    n = int(input())
    people = list(map(int, input().split()))

    # Sort the peoples and get rid of Julia
    julia = people[0]
    people = list(Counter(people[1:]).items())
    people.append((-10**17, 0))  # Sentinel value
    people.sort()

    # This is the gap between the closest group and Julia
    divide = julia - people[-1][0]

    # Starting from the back, the group of people will take floor(log(n)) rounds to
    # catch up to Julia by floor(log(n)) points.
    # Everyone else will close the gap by 1 point.
    numPeople = 0
    out = 0


    while(True):
        numPeople += people[-1][1]
        rounds = numPeople.bit_length() - 1
        difference = people[-1][0] - people[-2][0]

        # The first group will catch up before the next group appears
        if (rounds * difference > divide):
            out += divide

            # Every round, the group catches up round-1 points
            # => An additional divide / round times
            out += divide // rounds
            break

        divide -= rounds * difference
        out += (rounds+1) * difference
        people.pop()

    print(out)

if __name__ == '__main__':
    main()

