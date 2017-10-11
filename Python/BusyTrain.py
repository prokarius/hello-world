import collections

# statid = {}
# destination = raw_input()
# lst = [{"name": "Punggol","passengers": 80,"connections": [{"station": "Sengkang","line": "purple"}]}, {"name": "Sengkang","passengers": 40,"connections": [{"station": "Punggol","line": "purple"}, {"station": "Serangoon","line": "purple"}]}, {"name": "Serangoon","passengers": 40,"connections": [{"station": "LittleIndia","line": "purple"}, {"station": "Sengkang","line": "purple"}, {"station": "PayaLebar","line": "orange"}, {"station": "Bishan","line": "orange"}]}, {"name": "LittleIndia","passengers": 40,"connections": [{"station": "Serangoon","line": "purple"}, {"station": "DhobyGhaut","line": "purple"},]}, {"name": "DhobyGhaut","passengers": 20,"connections": [{"station": "LittleIndia","line": "purple"}, {"station": "HarbourFront","line": "purple"}, {"station": "Somerset","line": "red"}, {"station": "MarinaBay","line": "red"}, {"station": "Esplanade","line": "orange"}]}, {"name": "HarbourFront","passengers": 90,"connections": [{"station": "DhobyGhaut","line": "purple"}]}, {"name": "Somerset","passengers": 0,"connections": [{"station": "DhobyGhaut","line": "red"}, {"station": "Orchard","line": "red"}]}, {"name": "Orchard","passengers": 30,"connections": [{"station": "Somerset","line": "red"}, {"station": "Novena","line": "red"}]}, {"name": "Novena","passengers": 10,"connections": [{"station": "Orchard","line": "red"}, {"station": "Bishan","line": "red"}]}, {"name": "Bishan","passengers": 20,"connections": [{"station": "Novena","line": "red"}, {"station": "Woodlands","line": "red"}, {"station": "Serangoon","line": "orange"}]}, {"name": "Woodlands","passengers": 40,"connections": [{"station": "Bishan","line": "red"}]}, {"name": "MarinaBay","passengers": 100,"connections": [{"station": "DhobyGhaut","line": "red"}]}, {"name": "Esplanade","passengers": 0,"connections": [{"station": "DhobyGhaut","line": "orange"}, {"station": "PayaLebar","line": "orange"}]}, {"name": "PayaLebar","passengers": 75,"connections": [{"station": "Esplanade","line": "orange"}, {"station": "Serangoon","line": "orange"}]}]
## Gotta get rid of the hard code next time

def busybody(destination, lst):

    statid = {}
    idstat = {}
    numpass = {}
    dictcount = 0
    adjlist = {}

    for i in lst:
        output = set()
        p = i["passengers"]
        statname = i["name"]
        try:
            currid = statid[statname]
        except (KeyError):
            statid[statname] = dictcount
            currid = dictcount
            dictcount += 1

        idstat[currid] = statname

        numpass[currid] = p

        for j in i["connections"]:
            statname = j["station"]
            try:
                con = statid[statname]
            except (KeyError):
                statid[statname] = dictcount
                con = dictcount
                dictcount += 1
            output.add(con)
        adjlist[currid] = output

    destinationid = statid[destination]

    colour = [-1 for x in range(len(statid))]
    dfs = collections.deque()
    colour[destinationid] = 999

    for i in adjlist[destinationid]:
        colour[i] = i
        dfs.append((i,i)) 

    while dfs:
        pp = dfs.popleft()
        for i in adjlist[pp[0]]:
            if colour[i] != -1:
                continue
            colour[i] = pp[1]
            dfs.append((i, pp[1]))

    final = [0 for x in range(len(statid))]

    for i in range(len(colour)):
        if colour[i] == 999:
            continue
        final[colour[i]] += numpass[i]

    paess = -1
    for i in range(len(final)):
        if final[i] > paess:
            paess = final[i]
            theindex = i

    strat = idstat[theindex]
    for i in lst:
        if i["name"] == strat:
            for j in i["connections"]:
                if j["station"] == destination:
                    out = j["line"]

    return {"line": out,
            "totalNumOfPassengers": max(final),
            "reachingVia": strat}
    




# print busybody(destination, lst)

"""
Input format: busybody(destination, lst)
Destination: Destination Station Name
lst: List of dicts of json shit
"""

