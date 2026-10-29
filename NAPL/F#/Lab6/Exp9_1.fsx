printf "Enter marks for Subject 1: "
let a = int (System.Console.ReadLine())

printf "Enter marks for Subject 2: "
let b = int (System.Console.ReadLine())

printf "Enter marks for Subject 3: "
let c = int (System.Console.ReadLine())

printf "Enter marks for Subject 4: "
let d = int (System.Console.ReadLine())

let total = a + b + c + d
let percentage = float total / 4.0

printfn "Percentage = %.2f%%" percentage

let division =
    match percentage with
    | p when p >= 60.0 -> "First Division"
    | p when p >= 50.0 -> "Second Division"
    | p when p >= 40.0 -> "Third Division"
    | _ -> "Fail"

printfn "Division = %s" division