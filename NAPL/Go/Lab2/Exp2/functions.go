package Exp2

func Reverse(s string) string {
    res := ""

    for i := len(s) - 1; i >= 0; i-- {
        res += string(s[i])
    }

    return res
}

func CountVowels(s string) int {
    count := 0

    for _, ch := range s {
        if ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
            ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' {
            count++
        }
    }

    return count
}

func Factorial(n int) int {
    res := 1

    for i := 1; i <= n; i++ {
        res *= i
    }

    return res
}

func Power(base, exp int) int {
    res := 1

    for i := 1; i <= exp; i++ {
        res *= base
    }

    return res
}