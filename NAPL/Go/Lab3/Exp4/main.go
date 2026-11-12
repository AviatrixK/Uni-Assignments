package main

import "fmt"

type Person struct {
    Name   string
    Age    int
    Job    string
    Salary float64
}

func (p *Person) ReadData() {
    fmt.Print("Enter Name: ")
    fmt.Scan(&p.Name)

    fmt.Print("Enter Age: ")
    fmt.Scan(&p.Age)

    fmt.Print("Enter Job: ")
    fmt.Scan(&p.Job)

    fmt.Print("Enter Salary: ")
    _, err := fmt.Scan(&p.Salary)

    if err != nil {
        fmt.Println("Invalid salary! Enter a number.")
        fmt.Scan(&p.Salary)
    }
}

func (p Person) Display() {
    fmt.Println("\nPerson Details:")
    fmt.Println("Name:", p.Name)
    fmt.Println("Age:", p.Age)
    fmt.Println("Job:", p.Job)
    fmt.Printf("Salary: %.2f\n", p.Salary)
}

func main() {
    var person1 Person
    var person2 Person

    fmt.Println("Enter details of Person 1:")
    person1.ReadData()

    fmt.Println("\nEnter details of Person 2:")
    person2.ReadData()

    person1.Display()
    person2.Display()
}