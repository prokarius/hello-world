import re
import sys

def makeSentences(words):
    out = []
    curr = []

    for i in words:
        if i in ['.', ',', ':', ';', '?', '!', '*', '#']:
            out.append(curr)
            curr = []
        else:
            curr.append(i)

    return out

def scan_into_words(end_char):
    words = []

    # Scan in input until we reach the '*' character
    line = sys.stdin.readline().rstrip().lstrip()
    while (line != end_char):
        out = re.split(' +', line)
        words += out
        line = sys.stdin.readline().rstrip().lstrip()

    words.append(end_char)
    return words

def solve(n):
    known_words = set({'joe'})
    known_phrases = set()

    # Scan the training data:
    words = scan_into_words('*')
    sentences = makeSentences(words)

    # Do processing
    for sentence in sentences:

        # Make lower, so we process a little faster
        sentence = list(map(lambda x: x.lower(), sentence))

        # Learn all the words:
        for word in sentence:
            known_words.add(word)

        # Learn all the phrases
        for length in range(2, n+1):

            # Short circuit if the sentence is too short
            if len(sentence) < length:
                break

            # Make all the phrases
            for i in range(len(sentence) - length + 1):
                phrase = " ".join(sentence[i:i+length])

                known_phrases.add(phrase)

    # Scan the test data
    words = scan_into_words('#')
    sentences = makeSentences(words)

    # Process the test set
    for original_sentence in sentences:
        known = True
        sentence = list(map(lambda x: x.lower(), original_sentence))

        # Check each word:
        for word in original_sentence:
            if word.lower() not in known_words:
                known = False
                sys.stdout.write(f'What does the word "{word}" mean?\n')
                known_words.add(word.lower())

        # Check each phrase:
        for length in range(2, n+1):

            # Short circuit if the sentence is too short
            if len(sentence) < length:
                break

            # Make all the phrases
            for i in range(len(sentence) - length + 1):
                phrase = " ".join(sentence[i:i+length])

                if phrase not in known_phrases:
                    known = False
                    known_phrases.add(phrase)

        # Do we know the sentence?
        if not known and len(sentence) != 1:
            sys.stdout.write(f'What does the sentence "{" ".join(original_sentence)}" mean?\n')

def main():
    training = 1
    line = sys.stdin.readline()
    while (line):
        sys.stdout.write(f"Learning Case {training}\n")
        training += 1
        solve(int(line))
        line = sys.stdin.readline()
        sys.stdout.write('\n')

if __name__ == "__main__":
    main()

