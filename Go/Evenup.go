package main

import "fmt"

var ghettoStack [100000]int
var ghettoStackHead int = 0

func main() {
    // Scan in input
    var num, ph int
    fmt.Scanf("%d", &num)

    for i := 0; i < num ; i++ {
        fmt.Scanf("%d", &ph)
        // If the head of the stack is the same parity, then we can remove it
        if ghettoStackHead != 0 && ghettoStack[ghettoStackHead - 1] % 2 == ph % 2 {
            ghettoStackHead--
        } else {
            // Else we have no choice, but to put the element on the stack
            ghettoStack[ghettoStackHead] = ph
            ghettoStackHead++
        }
    }

    // In the end, we just have to print out the size of the remaining elements on the stack
    fmt.Printf("%d\n", ghettoStackHead)
}
