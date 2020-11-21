import itertools

def solve(numbers):
    # Get all the required values out
    numbers = list(map(int, numbers.split(" ")))
    n = numbers[0]
    total = numbers[-1]
    variables = numbers[1: -1]
    permutations = itertools.permutations(variables)

    # Scan in the equation
    equation = input()
    compiled = compile(equation, '<string>', 'eval')
    letters = []

    # What are the variables?
    for letter in equation:
        if (ord(letter) > 96 and ord(letter) < 123):
            letters.append(letter)

    # Now we just need to try all permutations
    for permutation in permutations:
        mapping = {}
        for i in range(n):
            mapping[letters[i]] = permutation[i]

        output = eval(compiled, {}, mapping)

        if output == total:
            print("YES")
            return

    # Ok no such mapping. Return false
    print ("NO")

def main():
    numbers = input()
    while (numbers != '0 0'):
        solve(numbers)
        numbers = input()

if __name__ == '__main__':
    main()

