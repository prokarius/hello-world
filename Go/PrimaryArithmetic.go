package main

import "fmt"

func main() {
    var a, b int
    fmt.Scanf("%d %d", &a, &b)

    for (a != 0 || b != 0) {

        // Count the number of times the sum of
        // digits exceeds 10
        out := 0
        carry := 0
        for (a != 0 || b != 0) {
            curra := a % 10
            currb := b % 10
            if curra + currb + carry > 9 {
                carry = 1
                out++
            } else {
                carry = 0
            }
            a /= 10
            b /= 10
        }

        // Output formatting...
        if out == 0 {
            fmt.Printf("No")
        } else {
            fmt.Printf("%d", out)
        }
        fmt.Printf(" carry operation")
        if out > 1 {
            fmt.Printf("s")
        }
        fmt.Println(".")
        fmt.Scanf("%d %d", &a, &b)
    }
}
