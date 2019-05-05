def main():
    score = int(input())

    mapping = ["", "single", "double", "triple"]

    # Just try all possible combination
    for dart1 in range(1, 21):
        for multiplier1 in range(1, 4):
            for dart2 in range(1, 21):
                for multiplier2 in range(1, 4):
                    for dart3 in range(1, 21):
                        for multiplier3 in range(1, 4):
                            if (dart1 * multiplier1 +
                                dart2 * multiplier2 +
                                dart3 * multiplier3 == score):
                                print (mapping[multiplier1] + " " + str(dart1))
                                print (mapping[multiplier2] + " " + str(dart2))
                                print (mapping[multiplier3] + " " + str(dart3))
                                return

    for dart2 in range(1, 21):
        for multiplier2 in range(1, 4):
            for dart3 in range(1, 21):
                for multiplier3 in range(1, 4):
                    if (dart2 * multiplier2 +
                        dart3 * multiplier3 == score):
                        print (mapping[multiplier2] + " " + str(dart2))
                        print (mapping[multiplier3] + " " + str(dart3))
                        return

    for dart3 in range(1, 21):
        for multiplier3 in range(1, 4):
            if(dart3 * multiplier3 == score):
                print (mapping[multiplier3] + " " + str(dart3))
                return

    print("impossible")

main()
