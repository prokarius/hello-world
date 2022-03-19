class Node:
    def __init__(self):
        self.word = None
        self.left = None
        self.right = None

# dp[wordnode][start_idx] = end_idx
dp = {}

def check_subword(word_node, target):
    global dp
    # Find out how far node can reach
    if id(word_node) in dp:
        return

    lst = {len(target): len(target)}

    # If the node is a end node, find out
    if word_node.word is not None:
        for start in range(len(target)):
            end = start
            for letter in word_node.word:
                if target[end] == letter:
                    end += 1
                    if end == len(target):
                        break
            lst[start] = end

    # If the node is a branch node, dfs into the subnode
    else:
        check_subword(word_node.left, target)
        check_subword(word_node.right, target)

        # The end point is given by how far in the right node we can get from the
        # end of the left node
        for start in range(len(target)):
            lst[start] = dp[id(word_node.right)][dp[id(word_node.left)][start]]

    dp[id(word_node)] = lst

def get_node(var, mapping):
    if var in mapping:
        return mapping[var]
    new_node = Node()
    mapping[var] = new_node
    return new_node

def solve():
    global dp

    # Scan in input
    k = int(input())
    nodes_mapping = {}

    dp = {}
    for i in range(k):
        eqn = input().split(" = ")
        eqn[1] = eqn[1].split(" + ")

        # Get or set the node
        lhs = get_node(eqn[0], nodes_mapping)

        # Leaf node
        if len(eqn[1]) == 1:
            lhs.word = eqn[1][0]

        # Branch
        else:
            lhs.left = get_node(eqn[1][0], nodes_mapping)
            lhs.right = get_node(eqn[1][1], nodes_mapping)

    # Read in the final word
    var = get_node(input(), nodes_mapping)
    target = input()
    check_subword(var, target)
    print("YES" if dp[id(var)][0] == len(target) else "NO")


def main():
    testcases = int(input())

    for i in range(testcases):
        solve()

if __name__ == '__main__':
    main()

