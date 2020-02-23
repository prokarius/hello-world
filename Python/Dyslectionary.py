import sys

def process(word_list):
    new_list = []

    # Reverse all the words in the list and sort them
    for word in word_list:
        new_list.append(word[::-1])
    new_list.sort()

    # Get the longest word and generate the padding
    max_length = max([len(word) for word in new_list])
    return [" "*(max_length - len(word)) + word[::-1] for word in new_list]

def main():
    # Scan in input
    # Sorry, I can't remember how to read until EOF. Im just gonna try catch
    wordlist = []
    while True:
        try:
            # Scan in the word
            next_word = input()
            if next_word == "":
                print ("\n".join(process(wordlist)))
                print ("")
                wordlist = []

            # If not, just append the new word
            else:
                wordlist.append(next_word)

        # Process the last entry during EOF
        except:
            print("\n".join(process(wordlist)))
            return

if __name__ == "__main__":
    main()

