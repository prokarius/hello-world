def main():
    axioms = set()

    # Scan in input
    lines = int(input())

    # For each line, ensure all the LHS stuff has been proven before
    for i in range(1, 1+lines):
        proof = input().split()

        contradiction = True
        rhs = False

        # For each piece, there are 3 options:
        for prop in proof:

            # If rhs is active, then we are good. Add it to output
            if rhs:
                axioms.add(prop)

            # Else, if the current item is '->', swap to rhs
            elif prop == '->':
                rhs = True

            # Else, we are still on LHS. Check if it exists in axioms
            else:
                if (prop not in axioms):
                    print(i)
                    break

        # If we didn't break out of the inner loop, there was no contradiction
        else:
            contradiction = False

        if contradiction:
            break

    # If we didn't break out of the loop, then the conclusions are correct
    else:
        print("correct")

if __name__ == '__main__':
    main()

