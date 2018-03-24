# RightPrice
# Given up to K <= 4 rooms with N<=100 items each, choose 1 item in each room
# such that the total sum of items is as close as possible to a target value T.
# If there are ties, output the largest total sum.

######
######

# This function returns the absolute value of the input number
def abs(num):
    return num if num > 0 else -num


# Lets bring the check to outside the function.
# Returns true if we need to update our best.
def check(target, currbest, curritem, room2item):
    # First lets calculate the minimum difference
    # And also calculate the current difference
    mindiff = abs(target - currbest)
    nowdiff = abs(target - (curritem + room2item))

    # If we have found something definitely better, return true
    if mindiff > nowdiff:
        return True

    # Else, maybe we found something the same, but it could be that total value
    # is bigger than what we have before! We need to update if that's the case
    if mindiff == nowdiff:
        if currbest < (room2item + curritem):
            return True

    # Aww, it's not any better...
    return False


# This will be the function we use for binary search
# Given two rooms room1, room2, their elements are the items in sorted order
# Given a target value target, we will search for the closest element to the
# target, and update best as we go along.
# Finally, we will return the best that we have ever found.
def binsearch(room1, room2, target):
    best = -1
    for item in room1:

        # Set up my binary search conditions.
        low = 0
        high = len(room2)-1

        # We will not stop searching until the distance between high and low is 1.
        while low <= high:
            mid = (low + high)//2

            # No matter what, we should check if the current mid would give us
            # a better result. That is the point of check.
            if check(target, best, item, room2[mid]):
                best = room2[mid] + item

            # We have two cases here, either the value is too large,
            # or the value is too small. Update the search accordingly
            if room2[mid] > (target - item):
                high = mid-1
            else:
                low = mid+1

    # After we have iterated through everything, we can simply return the best
    # that we have ever found.
    return best


def simulateEvent():
    # We will scan in the input.
    # Python has this weird input thing where it's basically sc.next()
    # So we will use string.split() method to split the string at the spaces
    # This will return us a list of strings, where each string is a number
    ph = input()

    # Here, we use list comperhension. Essentially we are doing
    # for (str i : ph.split()){
    #     phlist.pushBack(Integer.parseInt(i))
    # }
    phlist = [int(x) for x in ph.split()]

    # Then we can pull the number of rooms and the target value from our new list
    numrooms = phlist[0]
    targetvalue = phlist[1]

    # roomslist is a list of rooms, where a room is a list of numbers.
    # Yes python is awesome. I know.
    roomslist = []

    # For each room, we scan in the values of the items in the room
    # Then we use the parseInt thing I mentioned above to convert the strings
    # into actual numbers. Store those in a place holder list.
    # Then we push that list into the list of rooms that we have.
    for i in range (numrooms):
        useless = input()
        values = input()
        itemsinroom = [int(x) for x in values.split()]
        roomslist.append(itemsinroom)

    # # # # # # # # # # # # # #
    #  Now the input is done  #
    # # # # # # # # # # # # # #

    # There are 2 major cases:
    # Case 1 is when numrooms == 1
    # Then simply, we just find the elements closest to the target value.
    # Print the best one of them and then return
    if numrooms == 1:
        # So sort the elements in the room
        # We can just do a linear seach in this case tbh
        # The time complexity is like O(n) anyways...
        # Then print the answer and return to subtract 1 from query.
        roomslist[0].sort()
        out = binsearch(roomslist[0], [0], targetvalue)
        print (out)
        return

    # Or else it will be case 2: Where we have more than 2 rooms.
    # Here is the trick to the problem:
    # Notice that if we have only 2 rooms, we can just iterate through  -- (*)
    # the items in the first room, binary search for the second item
    # in the next room (where the target to find is (target - 1st item).
    # Suppose the number of items in this room is C.
    # Then time complexity is O(C log C)

    # The problem comes when we have more than 2 rooms.
    # How do we do the same process for, say 4 rooms?
    # You could say to brute force the first 3 rooms (therefore N**3) and then
    # binary search for the final element in the last room. (log N)
    # And you'd be almost right, sans the 25/50 brutal markscheme.

    # The missing link is to realise that you can combine the objects in the
    # room and the time complexity will not reduce.
    # What if we made 2 new rooms as in (*). Then we can do it in O(C log C).
    # So what is C? Question gives us a clue: N**2 log N.
    # Hence C should be N**2
    pairwisesum1 = []
    pairwisesum2 = []

    # OK whew that was a lot of shit to process. Let's start easy.
    # If we have 2 rooms, then very simple, we can use the method of (*).
    # Let's push the elements of my datalist
    if numrooms == 2:
        pairwisesum1 = roomslist[0]
        pairwisesum2 = roomslist[1]

    # Now if we have 3 rooms, we will need to combine 2 rooms together.
    # Take 2 arbitrary rooms and calculate the cross product of their elems.
    # i.e. For each element in the first room, add it to every element of
    # the second room, and push that result into a new list.
    if numrooms == 3:
        for i in roomslist[0]:
            for j in roomslist[1]:
                pairwisesum1.append(i+j)

        # Note that the third room can just be itself.
        # We don't need to do any summing, so we just set the pointer of the
        # second list to be the third room.
        pairwisesum2 = roomslist[2]

    # Same for the case with 4 rooms, except you will need to calculate two
    # cases of pairwise sums.
    if numrooms == 4:
        for i in roomslist[0]:
            for j in roomslist[1]:
                pairwisesum1.append(i+j)

        for i in roomslist[2]:
            for j in roomslist[3]:
                pairwisesum2.append(i+j)

    # Now that we have 2 lists, we just have to sort the lists.
    # Note that because each list has N*N items, sorting will take
    # O(N**2 log (N**2)) = O(2 N**2 log N) = O(N**2logN)
    pairwisesum1.sort()
    pairwisesum2.sort()

    # Call the binary search function.
    # The function itself will process the data and return us the best price
    best = binsearch(pairwisesum1, pairwisesum2, targetvalue)

    # Then simply print the best.
    # Without return value is ok.
    # Python will automatically return null and move on to the next case after.
    print (best)

def main():
    # Scan in the number of queries
    # For each query, we will simulate the event by calling another method.
    q = int(input())
    while (q>0):
        throwaway = input()
        simulateEvent()
        q-=1

main()
