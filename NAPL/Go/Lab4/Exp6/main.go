package main

import "fmt"

func square(ch chan string) {
    fmt.Println("Square goroutine started")

    result := 5 * 5

    fmt.Println("Square goroutine completed")
    ch <- fmt.Sprintf("Square of 5 = %d", result)
}

func cube(ch chan string) {
    fmt.Println("Cube goroutine started")

    result := 3 * 3 * 3

    fmt.Println("Cube goroutine completed")
    ch <- fmt.Sprintf("Cube of 3 = %d", result)
}

func fibonacci(ch chan string) {
    fmt.Println("Fibonacci goroutine started")

    a, b := 0, 1
    result := a + b

    for i := 2; i < 7; i++ {
        a, b = b, a+b
        result = b
    }

    fmt.Println("Fibonacci goroutine completed")
    ch <- fmt.Sprintf("Fibonacci number = %d", result)
}

func main() {
    ch := make(chan string)

    go square(ch)
    go cube(ch)
    go fibonacci(ch)

    for i := 0; i < 3; i++ {
        fmt.Println("Result:", <-ch)
    }
}