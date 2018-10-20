package main

import "fmt"

var primes [32005]int

func generatePrimes(){
    primes[0] = 1
    primes[1] = 1
    for i := 2; i < 180; i++ {
        if primes[i] == 0 {
            for j := i * i; j <= 32000; j += i {
                primes[j] = 1
            }
        }
    }
}

func run() {
    var n int
    fmt.Scanf("%d", &n)

    // Count the number of representations
    numRep := 0
    for i := n/2; i >= 2 ; i-- {
        if primes[i] == 0 && primes[n-i] == 0{
            numRep++
            defer fmt.Printf("%d+%d\n", i, n-i)
        }
    }
    fmt.Printf("%d has %d representations\n", n, numRep)
}

func main() {
    generatePrimes()
    var testcases int
    fmt.Scanf("%d", &testcases)
    for testcases > 0 {
        run()
        fmt.Printf("\n")
        testcases--
    }
}
