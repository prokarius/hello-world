from collections import defaultdict

def default_value():
    return (8008, 0)

def solve():
    # Scan in input
    m = int(input())
    distances = list(map(int, input().split(' ')))
    dist_left = sum(distances)

    dp = {0: (0,0)}

    # For each distance, save the position spiderman could end up at
    for dist in distances:
        new_dp = defaultdict(default_value)
        dist_left -= dist

        for curr, state in dp.items():
            if curr < 0 : continue  # Duct tape

            # Try climbing down:
            # continue if we are underground
            if (curr - dist < 0): continue

            # continue if we have been here before, but used a shorter building
            new_dist = state[0]
            if new_dp[curr - dist][0] < new_dist: continue

            new_dp[curr - dist] = (new_dist, state[1]*2)

        for curr, state in dp.items():
            if curr < 0 : continue  # Duct tape

            # Try climbing up
            # continue if we climbed so high, we can't ever reach back to street
            if (curr + dist > dist_left): continue

            # continue if we have been here before, but used a shorter building
            new_dist = max(state[0], curr + dist)
            if new_dp[curr + dist][0] < new_dist: continue

            new_dp[curr + dist] = (new_dist, state[1]*2+1)

        # Save the results of the dp table
        dp = new_dp


    # Do we have 0?
    if len(dp) == 0:
        print("IMPOSSIBLE")
    else:
        action = dp[0][1]
        out = []
        while action:
            if (action % 2 == 1):
                out.append('U')
            else:
                out.append('D')
            action >>= 1
        print (''.join(reversed(out)))

def main():
    n = int(input())
    for _ in range(n):
        solve()

if __name__ == '__main__':
    main()

