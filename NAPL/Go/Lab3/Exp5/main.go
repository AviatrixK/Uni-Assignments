package main
import "fmt"

func updateValue(ptr *int) {
    *ptr = 100
}

type Student struct {
    Name string
    Age  int
}

func main() {
    // Pointer declaration
    num := 10
    ptr := &num
    fmt.Println("Original Value:", num)
    fmt.Println("Address of num:", ptr)
    fmt.Println("Value using pointer:", *ptr)

    // Pass by reference
    fmt.Println("\nBefore Modification:", num)

    updateValue(ptr)
    fmt.Println("After Modification:", num)

    student := new(Student)

    student.Name = "Kiru"
    student.Age = 22

    fmt.Println("\nStudent Details:")
    fmt.Println("Name:", student.Name)
    fmt.Println("Age:", student.Age)

    // Modify struct fields through pointer
    student.Name = "Kiruthika"
    student.Age = 21

    fmt.Println("\nAfter Modification:")
    fmt.Println("Name:", student.Name)
    fmt.Println("Age:", student.Age)
}