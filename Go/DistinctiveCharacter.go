package main

import ("fmt";
        "strconv";
        "bufio";
        "os")

var visited[1<<20 + 5] int

var ghettoQueue[1<<20 + 5] int
var ghettoQueueHead int = 0
var ghettoQueueTail int = 0

func push(value int) {
    ghettoQueue[ghettoQueueHead] = value
    ghettoQueueHead++
}

func pop() int{
    var out = ghettoQueue[ghettoQueueTail]
    ghettoQueueTail++
    return out
}

func size() int{
    return ghettoQueueHead - ghettoQueueTail
}

func lpad(s string,pad string, plength uint)string{
    for i:=len(s);i<int(plength);i++{
        s=pad+s
    }
    return s
}

func main(){
    // Scan in input
    var n int
    var k uint
    fmt.Scanf("%d %d ", &n, &k)

    // Set up FastIO BufferedReader
    reader := bufio.NewReader(os.Stdin)

    // Scan in each other character
    // Represent them as integers
    for i := 0; i < n; i++ {
        var number = 0
        other, _ := reader.ReadString('\n')

        for j := uint(0); j < k; j++ {
            number *= 2
            if other[j] == '1' {
                number += 1
            }
        }

        // Push them into the ghetto queue
        if visited[number] == 0 {
            push(number)
            visited[number] = 1;
        }
    }

    // Do BFS
    for size() > 0 {
        var curr int = pop()
        for i := uint(0); i < k; i++ {
            var next int = curr ^ (1<<i)
            if visited[next] > 0 {continue}
            visited[next] = visited[curr] + 1
            push(next);
        }
    }

    // Find the best
    var best = -1;
    var out = -1;
    for i := 0; i < (1<<uint(k)); i++{
        if visited[i] > best {
            best = visited[i]
            out = i
        }
    }

    fmt.Printf("%s\n", lpad(strconv.FormatInt(int64(out), 2), "0", k))
}