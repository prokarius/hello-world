# Solution sketch by Kurumi chan, who claimed this is not a 9.1
# This solution reeks of a "why didn't I think of this" smell...

import collections

# Given a list of numbers and positions, generate all possible multiset permutations from the positions.
# Adapted from a stack overflow question
# https://stackoverflow.com/questions/61956964/generate-unique-permutations-from-a-multiset-using-backtracking-and-in-lexicogra
def getMultisetPermutations(numPos, lst):

    def recurse(depth, counter, permutation, mapping):
        # Base case: If we used up all the numbers
        if depth == 0:
            yield permutation
            return

        # For each number we have in the multiset
        for num, value in counter.items():

            # Prune: if we have no more instances of it, give up
            if value == 0: continue

            counter[num] -= 1
            pos = mapping[num].pop()
            permutation.append(pos)

            # Recurse
            yield from [
                list(i) for i in recurse(depth - 1, counter, permutation, mapping)
            ]

            permutation.pop()
            mapping[num].append(pos)
            counter[num] += 1

    # Get the list of numbers
    listNums = [lst[index] for index in numPos]

    # Create a mapping for the numbers to position
    mapping = {}
    for i in range(10):
        mapping[i] = []

    for index, num in zip(numPos, listNums):
        mapping[num].append(index)

    counter = collections.Counter(listNums)

    # Actually call the recurse function
    return list(recurse(len(listNums), counter, [], mapping))

def dfs(lst, swaps):
    # Make a duplicate of the list so we can screw around with it
    lst = list(lst)

    # Base case: If we do not have anymore swaps, give up and return the number
    if swaps == 0:
        return lst

    # Base case: If we have <= 1 element left in the number, something probably went wrong...
    if (len(lst) <= 1):
        return lst

    # Base case: If we have 2 elements left and have swaps left, as long as at least one number in
    # the original input is duplicated, we can always keep the better of the two arrangements
    if (len(lst) == 2):
        if duplicated:
            return sorted(lst, reverse = True)
        elif swaps % 2 == 1:
            return list(reversed(lst))
        else:
            return lst

    # We want to swap all the largest number to the front.
    # Then for the rest of the numbers do a sort of complete search for the ordering of the numbers
    # that were swapped with the largest numbers

    # Find the number of instances of the largest number
    largest_pos = [index for index, num in enumerate(lst) if num == max(lst)]
    num_max = len(largest_pos)

    # Then find out where they live in the array, and what numbers you're swapping for
    largest_pos_to_swap = [index for index in largest_pos if index >= num_max][::-1]
    other_nums_pos_to_swap = [index for index, num in enumerate(lst[:num_max]) if num != max(lst)]

    # The best case with this set of numbers is itself (if there exists a duplicate)
    # or we need to take whatever comes out
    best = lst if duplicated else []

    # Prune: If all the largest numbers are already at the front
    # Then we can move on to the next higher number
    if (len(largest_pos_to_swap) == 0):
        return max(best, lst[:num_max] + dfs(lst[num_max:], swaps))

    # Find out how many swaps we need to use here
    num_swaps = min(swaps, len(largest_pos_to_swap))

    # Get all the multiset permutations. And swap them.
    # Then see if it beats the best we have so far
    all_perms = getMultisetPermutations(other_nums_pos_to_swap[:num_swaps], lst)
    for permutation in all_perms:
        newLst = swap(lst, largest_pos_to_swap[:num_swaps], permutation)
        best = max(best, newLst[:num_swaps] + dfs(newLst[num_swaps:], swaps - num_swaps))

    return best

def swap(lst, from_lst, to_lst):
    out = list(lst)
    for from_val, to_val in zip(from_lst, to_lst):
        out[from_val], out[to_val] = out[to_val], out[from_val]
    return out

def main():
    global duplicated
    # Scan in input
    n, swaps = input().split()
    swaps = int(swaps)

    duplicated = len(set(n)) != len(n)

    # We will be doing a sort of DP DFS search
    print("".join(map(str, dfs(list([int(i) for i in n]), swaps))))

if __name__ == '__main__':
    main()

