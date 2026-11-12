package main

import (
    "fmt"
    "exp2/Exp2"
)

func main() {
    str := "Hello World"

    fmt.Println("Original String:", str)
    fmt.Println("Reversed String:", Exp2.Reverse(str))
    fmt.Println("Number of Vowels:", Exp2.CountVowels(str))

    fmt.Println("Factorial of 5:", Exp2.Factorial(5))
    fmt.Println("Power of 2^3:", Exp2.Power(2, 3))
}