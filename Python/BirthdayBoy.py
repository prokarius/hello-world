# HAHAHAHA USING BUILTIN LIBRARIES ON KATTIS?! LOL
from datetime import date, timedelta


def printdate(dateObject):
    dateObject -= timedelta(days=1)
    print(f"{dateObject.month:02}-{dateObject.day:02}")

def main():
    gapSize = timedelta(days=0)
    bestBirthdays = []
    birthdays = []

    # Scan in input
    n = int(input())
    for i in range(n):
        dlist = input().split(" ")[1].split("-")

        # 2017 - 2019 has no leap years
        birthdays.append(date(2018, int(dlist[0]), int (dlist[1])))
        birthdays.append(date(2019, int(dlist[0]), int (dlist[1])))

    # OK we now have n dates. Find the biggest gap
    birthdays.sort()
    for i in range(n):
        gap = birthdays[i+1] - birthdays[i]
        if (gap == gapSize):
            bestBirthdays.append(birthdays[i+1])
        elif (gap > gapSize):
            gapSize = gap
            bestBirthdays = [birthdays[i+1]]

    # OK, do we only have 1 birthday?
    if len(bestBirthdays) == 1:
        printdate(bestBirthdays[0])
        return

    # If not, find the date that is closest to October 27th
    # Get all the dates that are after October 27th, and sort to see which is smallest
    # Wow this is really inefficient. Sorry
    oct28 = list(filter(lambda x: (x.month > 10 and x.year == 2018) or (x.month == 10 and x.day > 28 and x.year == 2018), bestBirthdays))
    if len(oct28) > 0:
        oct28.sort()
        printdate(oct28[0])
        return

    # If we do not have any birthdays at the end of the year, then just go to the next year and get the earliest
    else:
        bestBirthdays = list(filter(lambda x: x.year == 2019, bestBirthdays))
        bestBirthdays.sort()
        printdate(bestBirthdays[0])
        return

if __name__ == '__main__':
    main()

