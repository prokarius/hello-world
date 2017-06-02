numcases = int(raw_input ())
while numcases > 0:
    worthless = raw_input()
    numteams = int(raw_input())
    somelist = []
    while numteams > 0:
        team = raw_input()
        teamdata = [x for x in team.split(' ')]
        somelist.append (int (teamdata [1]))
        numteams -= 1
    somelist.sort()
    output = 0
    for i in range(len(somelist)):
        output += abs(somelist[i]-(i+1))
    print output
    numcases -= 1
