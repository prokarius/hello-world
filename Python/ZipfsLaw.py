import sys
import re

regex = '[^a-z]'

def process(lst, num):
    out = []
    count = {}

    # Count the number of words
    # Because we use shitty regex passing, we need to filter for blank words.
    for word in lst:
        if not word: continue
        if word not in count: count[word] = 1
        else: count[word] += 1

    # Find out which words have the correct frequency
    for word in count:
        if count[word] == num:
            out.append(word)

    # If there is no such word, print there is no such word and return
    if len(out) == 0:
        print "There is no such word.\n"
        return

    # Sort and print the words
    out.sort()
    for word in out:
        print word
    print ""

def main():
    line = sys.stdin.readline()
    inputWords = []
    occurances = -1

    # Keep reading until EOF
    while (line):

        # Process if we have reached "end of text"
        if line == "EndOfText\n":
            process(inputWords, occurances);
            inputWords = []
            occurances = -1

        # If not, add all words to the list of input words
        else:
            if occurances == -1:
                occurances = int(line[:-1])
            else:
                inputWords += re.split(regex, line.lower())
        line = sys.stdin.readline()

main()
