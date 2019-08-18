# Store the current time in seconds
currTime = 0
currSpeed = 0
totalDistance = 0

def processtime(string):
    dlist = string.split(":")
    hour = int(dlist[0])
    mins = int(dlist[1])
    secs = int(dlist[2])
    return secs + mins*60 + hour*3600

while 1:
    try:
        dlist = input().split(" ")
    except:
        break

    # Get the time
    time = processtime(dlist[0])

    # Get the distance travelled
    deltaTime = time - currTime
    totalDistance += (deltaTime * currSpeed) / 3600

    # If we have a speed, then set the speed
    if len(dlist) == 2:
        currSpeed = int(dlist[1])

    # Else output the total distance
    else:
        print ("{} {:0.2f} km".format(dlist[0], totalDistance))

    # Set the current time as the new time
    currTime = time
