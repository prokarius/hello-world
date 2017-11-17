def gcd(x, y):
    while y:
        x, y = y, x%y
    return x

T = int(raw_input())
while (T):
    # Scan in input
    n = int(raw_input())
    ph = raw_input()
    dlist = [int(x) for x in ph.split(' ')]

    # Initialise the variables
    res = 0
    mapping = {}

    # This problem is a DP problem.
    # You want to find the left most point of each distinct GCD that happens.
    # This data structure allows you to calculate k*GCD quickly
    # This can be stored in a dict that maps a unique GCD to a left most point.

    for i in range(n):
        elem = dlist[i]
        # For each element, it could be the best, so we compare it to the result
        # While we are at it, we store it in a new dictionary.
        # This will help with the iterating
        res = max(res, elem)
        tempmapping = {elem: i}

        # If not, for each of the old possible gcds
        for k,v in mapping.iteritems():
            # See if it updates our gcd estimates
            newgcd = gcd(k, elem)
            res = max(res, (i-v+1)*newgcd)

            # Also, see if it changes any older distances
            # We choose to keep the min.
            try:
                tempmapping[newgcd] = min(v, mapping[newgcd])
            except (KeyError):
                # If we are here, is means this gcd didn't ever exist.
                # Then this gcd has the left point equal to left point of current value
                tempmapping[newgcd] = v

        # Finally copy the dict to the previous:
        mapping = tempmapping

    # To end the code, print out the results
    print res
    T -= 1
