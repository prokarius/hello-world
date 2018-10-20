package main

import "fmt"

var numCoins int
var coins [105]int
var dp [2000005]int

func greedy(value, nCoins int) int {
    out := 0
    for nCoins > 0{
        nCoins -= 1
        curr := value/coins[nCoins]
        out += curr
        value -= curr * coins[nCoins]
    }
    return out
}

func main(){
    // Scan in the input
    var numCoins int
    fmt.Scanln(&numCoins)

    if (numCoins == 1){
        fmt.Println("canonical")
        return
    }

    i := 0

    // Scan in coin values
    for i < numCoins {
        fmt.Scanf("%d", &coins[i])
        i++
    }

    coinmax := coins[numCoins-1] + coins[numCoins-2]

    dp[0] = 0

    // Populate the dp table
    i = 1
    for i < coinmax {
        currmin := 1000000000
        j := 0
        for j < numCoins{
            if i - coins[j] < 0 {
                break
            }
            if currmin > dp[i - coins[j]]{
                currmin = dp[i - coins[j]]
            }
            j++
        }
        dp[i] = currmin + 1
        i++
    }

    // Then compare the dp table with each greedy
    i = 1
    for i < coinmax{
        if (greedy(i, numCoins) > dp[i]){
            fmt.Println("non-canonical")
            return
        }
        i++
    }
    fmt.Println("canonical")
}
