#[n, cost] = [int(x) for x in raw_input().split(" ")]; print(-cost+reduce(lambda x, y: (max(x[0], y), max(x[1], x[0] - y)), map(lambda x, y: x + y*cost, [100*int(x) for x in raw_input().split(" ")], range(n)), (0, cost))[1])

# But I want to golf this

[n,c]=map(int,raw_input().split());print-c+reduce(lambda x,y:(max(x[0],y),max(x[1],x[0]-y)),map(lambda x,y:x*100+y*c,map(int,raw_input().split()),range(n)),(0,c))[1]
