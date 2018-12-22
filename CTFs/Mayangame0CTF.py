xs = []
game = []
dr = [0,1,0,-1,0]
success = 0
size = -1

def removebuffer():
    n = raw_input()
    while "-----------------------------------------" not in n:
        n = raw_input()

def solve(xs, game, cord):
    global success
    for i in range(4):
        coord = [cord[0] + dr[i], cord[1] + dr[i+1]]
        if coord[0] < 0 or coord[0] >= size or coord[1] < 0 or coord[1] >= size:
            continue
        if game[coord[0]][coord[1]] == "#":
            continue
        elif game[coord[0]][coord[1]] == "X":
            game[coord[0]][coord[1]] = "#"
            xs.remove(coord)
            if len(xs) == 0:
                success += 1
            else:
                save = xs[-1]
                game[save[0]][save[1]] = "#"
                solve(xs[:-1], game, save)
                game[save[0]][save[1]] = "X"
            xs.append(coord)
            game[coord[0]][coord[1]] = "X"
        else:
            game[coord[0]][coord[1]] = "#"
            solve(xs, game, coord)
            game[coord[0]][coord[1]] = "."

def reset():
    global xs, game, success
    success = 0
    xs = []
    game = []

def start():
    reset()
    global size
    n = raw_input()
    l = n.split(' ')
    size = int(l[4][:-1])
    n = raw_input()
    n = raw_input()
    counter = 0
    for i in range(size):
        ph = n.split("|")
        for i in range(len(ph)):
            if ph[i] == "X":
                xs.append([counter, i])
        game.append(ph)
        counter += 1
        n = raw_input()
    size = len(ph)
    game[xs[-1][0]][xs[-1][1]] = "#"
    solve(xs[:-1], game, xs[-1])
    print (success)
    removebuffer()
    start()

removebuffer()
start()
