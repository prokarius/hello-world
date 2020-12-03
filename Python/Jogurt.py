# Each layer of the tree will consist of the numbers (2**(n-1), 2**n]
# Each layer is a double of the previous layer, but +1 to elements of the right sub-tree
# The last layer is reversed

# This works because the difference in each layer is a power of 2.
# By doubling the difference is still a power of 2
# By adding one to nodes in the right subtree (from root), the individual differences 
# at the n-1th layer is still some power of two 2**k.
# Yet at the n-2th layer, it is now 2**k-1 (because we added 1 to (2**k)/2 elements)

# Reversing the last layer flips the tree on its head, so that the difference in the
# left and right subtree sum is being removed
# (i.e. it's now -2**k + 2**(k-1) + 2**(k-2) + ...)

tree = [0]
n = -1

def preorder(node, level):
    print(tree[node], end = ' ')  # Stupid python hacks

    if (level == n): return
    preorder(node*2, level+1)
    preorder(node*2 + 1, level+1)


def main():
    global tree, n
    n = int(input())

    # Tree is output. We need one indexing for pre-order traversal
    curr = [1]

    for i in range(n-1):
        prev = curr
        curr = []

        # Copy the elements of the prev layer, multiplied by 2
        for i in prev:
            curr.append(2*i)

        # And again, but this time, add 1 to it after multiplying by 2
        for i in prev:
            curr.append(2*i+1)

        # Append it to the tree and save the curr value as prev
        tree += list(prev)

    # Reverse and append:
    tree += list(reversed(curr))

    # Now to construct pre order traversal...
    preorder(1, 1)
    print()  # For the final newline


if __name__ == '__main__':
    main()

