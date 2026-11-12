package main

import "fmt"

func main() {
    // Slice 
    students := []string{"Keerthu", "Hema", "Luna"}
    fmt.Println("Original Slice:", students)

    // Add 
    students = append(students, "Cho")
    fmt.Println("After Adding:", students)

    // Remove 
    index := 1
    students = append(students[:index], students[index+1:]...)
    fmt.Println("After Removing:", students)

    // Update 
    students[1] = "David"
    fmt.Println("After Updating:", students)

    // Map 
    marks := map[string]int{
        "Go": 85,
        "Java": 90,
        "Python": 80,
    }
    fmt.Println("\nOriginal Map:", marks)

    // Insert 
    marks["C"] = 75
    fmt.Println("After Inserting:", marks)

    // Delete 
    delete(marks, "Java")
    fmt.Println("After Deleting:", marks)

    // Lookup 
    subject := "Go"
    value, exists := marks[subject]

    if exists {
        fmt.Println("Marks in", subject, ":", value)
    } else {
        fmt.Println(subject, "not found")
    }
}
