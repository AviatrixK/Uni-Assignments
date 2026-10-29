
package main

import (
	"fmt"
	"math"
	"strings"
)

func divide(a, b float64) (float64, error) {
	if b == 0 {
		return 0, fmt.Errorf("division by zero is not allowed")
	}
	return a / b, nil
}

func squareRoot(n float64) (float64, error) {
	if n < 0 {
		return 0, fmt.Errorf("cannot calculate square root of a negative number")
	}
	return math.Sqrt(n), nil
}

func checkInput(s string) (string, error) {
	if strings.TrimSpace(s) == "" {
		return "", fmt.Errorf("input cannot be empty")
	}
	return s, nil
}

func main() {
	result, err := divide(10, 2)
	if err != nil {
		fmt.Println("Error:", err)
	} else {
		fmt.Println("Division result:", result)
	}

	root, err := squareRoot(-9)
	if err != nil {
		fmt.Println("Error:", err)
	} else {
		fmt.Println("Square root:", root)
	}

	input, err := checkInput("")
	if err != nil {
		fmt.Println("Error:", err)
	} else {
		fmt.Println("Input:", input)
	}
}
