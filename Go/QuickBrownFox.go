package main

import (
    "fmt"
    "strings"
    "bufio"
    "os"
)

func main(){
    // Create a variable to hold the number of testcases
    var testcases int

    // Create my bufferedReader
    in := bufio.NewReader(os.Stdin)

    // Scan in the line containing the number of testcases
    // This format is similar to input() of python
    fmt.Scanln(&testcases)

    // While loops are written in for syntax.
    for testcases > 0 {
        // Read in the input
        var alphabet string = "abcdefghijklmnopqrstuvwxyz"
        input, _ := in.ReadString('\n')

        // For each character in the input
        for i := range input {
            var lowercase string = string(input[i])
            alphabet = strings.Replace(alphabet, strings.ToLower(lowercase), "", 1);
        }

        // Check if the length of alphabet is 0
        // Note that go requires else statements to start on the same line as the
        // closing brackets of the previous if statement
        if (len(alphabet) == 0){
            fmt.Println("pangram")
        } else {
            fmt.Printf("missing + %s\n", alphabet)
        }
        testcases--
    }
}
