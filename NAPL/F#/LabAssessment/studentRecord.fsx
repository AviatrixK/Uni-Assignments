type Student = {
    Id: int
    Name: string
    Age: int
    Course: string
    Marks: int
}

let student1 = {
    Id = 1
    Name = "Eva"
    Age = 20
    Course = "Biology"
    Marks = 85
}

let student2 = {
    Id = 2
    Name = "Akansha"
    Age = 21
    Course = "Computer Science"
    Marks = 75
}

let student3 = {
    Id = 3
    Name = "Tiya"
    Age = 19
    Course = "Science"
    Marks = 45
}

let students = [student1; student2; student3]

students |> List.iter (fun s ->
    printfn "ID: %d, Name: %s, Age: %d, Course: %s, Marks: %d"
        s.Id s.Name s.Age s.Course s.Marks
)


let stuNames =
    students |> List.map (fun s -> s.Name)

printfn "\nStudent Names:"
printfn "%A" stuNames

let passStudents =
    students |> List.filter (fun s -> s.Marks >= 50)

printfn "\nPassed Students:"
passStudents |> List.iter (fun s -> printfn "%s" s.Name)


let checkRes marks =
    match marks with
    | m when m >= 80 -> "Excellent"
    | m when m >= 50 -> "Pass"
    | _ -> "Fail"

printfn "\nStudent Results:"
students |> List.iter (fun s ->
    printfn "%s: %s" s.Name (checkRes s.Marks)
)
