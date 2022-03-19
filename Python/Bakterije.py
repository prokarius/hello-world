from functools import reduce

class Equation():
    def __init__(self, a, b):  # ax + b
        self.a = a
        self.b = b

    def __repr__(self):
        return str(self.a) + 'x + ' + str(self.b)

best = 10**50
primes = [x for x in range(2, 20000) if not 0 in map(lambda z : x % z, range(2, int(x**0.5+1)))]

# Copied. Sorry not sorry 
def extended_euclid(a, b):
    if b == 0:
        return (1, 0)
    (x, y) = extended_euclid(b, a % b)
    k = a // b
    return (y, x - k * y)

def crt(eqn1, eqn2):
    n1, r1 = eqn1.a, eqn1.b
    n2, r2 = eqn2.a, eqn2.b
    (x, y) = extended_euclid(n1, n2)
    m = n1 * n2
    n = r2 * x * n1 + r1 * y * n2
    return Equation(m, (n % m + m) % m)

# Decomposes eqn.a into prime factors:
# input 500, output: [(2, 2), (5, 3)] because 500 = 2**2 * 5**3
def prime_powers(eqn):
    out = []
    for prime in primes:
        if eqn.a % prime != 0: continue
        count, temp = 0, eqn.a
        while temp % prime == 0:
            count += 1
            temp /= prime
        out.append((prime, count))
    return out

# Chinese remainder theorem
# Damn this code is not elegant because Im tired already
def CRT(eqns):
    coprime = {}  # prime: (power, mod)
    lowest = -1  # Keep track of greatest value of b.
    for eqn in eqns:
        lowest = max(eqn.b, lowest)

        primePowers = prime_powers(eqn)
        for prime in primePowers:

            # Coprime to everythings
            if prime[0] not in coprime:
                coprime[prime[0]] = (prime[1], eqn.b % (prime[0]**prime[1]))
                continue

            # There is a clash!
            clash = coprime[prime[0]]
            lower = min(clash[0], prime[1])
            if (clash[1] % (prime[0]**lower) != eqn.b % (prime[0]**lower)):
                return 10**50

            if (prime[1] > clash[0]):
                coprime[prime[0]] = (prime[1], eqn.b % (prime[0]**prime[1]))

    # Cool, now we have a list of coprime integers, time to CRT
    lst = map(lambda x: Equation(x[0]**x[1][0], x[1][1]), coprime.items())
    out = reduce(lambda a, b: crt(a, b), lst)

    # Also if out[0] < the highest value so far, add out[1] until above
    while (out.b < lowest):
        out.b += out.a
    return out.b

def process(eqns):
    global best
    # Of all the eqns are there anywhere it is constant?
    ans = set(map(lambda eqn: eqn.b, filter(lambda eqn: eqn.a == 0, eqns)))
    if len(ans) >= 1: return

    # OK can all the equations reach this?
    if len(ans) == 1:
        ans = list(ans)[0]
        for eqn in filter(lambda eqn: eqn.a != 0, eqns):
            if (ans - eqn.b) % eqn.a != 0: return

        # Oh this fixed point works
        best = min(best, ans)
        return

    # No fixed point, so we loop forever. Time to CRT
    if len(ans) == 0:
        best = min(best, CRT(eqns))
        return


def recurse(idx, end, eqns, currEqns = []):
    if (idx == end):
        process(currEqns)
        return

    # For each equation, add it to the list of eqns, recurse, then pop
    for i in range(len(eqns[idx])):
        currEqns.append(eqns[idx][i])
        recurse(idx+1, end, eqns, currEqns)
        currEqns.pop()

def main():
    direction = {'R': 0, 'D': 1, 'L': 2, 'U': 3}
    dr = [0, 1, 0, -1, 0]

    # Scan in input
    n, m, k = map(int, input().split())
    trapx, trapy = map(lambda x: int(x) - 1, input().split())
    eqns = []

    # Repeat for each bacteria
    for i in range(k):
        dlist = input().split()
        bx, by = int(dlist[0])-1, int(dlist[1])-1
        face = direction[dlist[2]]

        board = []
        for j in range(n):
            board.append([int(x)%4 for x in input().rstrip()])

        # Simulate the bacteria
        # dp[x][y][direction] = steps to that point
        dp = [[[-1, -1, -1, -1] for i in range(m)] for j in range(n)]
        steps = 0
        while(dp[bx][by][face] == -1):
            dp[bx][by][face] = steps
            face = (face + board[bx][by]) % 4
            newx = bx + dr[face]
            newy = by + dr[face + 1]

            # Out of bounds checks...
            if (newx < 0 or newy < 0 or newx >= n or newy >= m):
                face = (face + 2) % 4

            bx += dr[face]
            by += dr[face+1]
            steps += 1

        # OK We have looped. This should not take more than 4 * 50 * 50 = 10000 steps
        loopStartSteps = dp[bx][by][face]
        currSteps = steps
        loopLen = currSteps - loopStartSteps

        print(loopStartSteps, loopLen)
        # Now for each of the 4 directions we can land on the trap
        # Form the equation of on whichth step we land on the trap
        eqns.append([])
        for direct in range(4):
            trapStep = dp[trapx][trapy][direct]
            print(trapStep)

            # Have we reached the trap in this direction?
            if (trapStep != -1):

                # Is this part of a loop?
                if trapStep < loopStartSteps:
                    eqns[i].append(Equation(0, trapStep))
                else:
                    eqns[i].append(Equation(loopLen, trapStep))

    # Solve all possible CRT equations
    print(eqns)
    recurse(0, k, eqns)
    print(best if best != 10**50 else -1)

if __name__ == '__main__':
    main()

