let sqrList nums = List.map (fun x -> x * x) nums
let evenList nums = List.filter (fun x -> x % 2 = 0) nums
let sumList nums = List.fold (fun sum x -> sum + x) 0 nums

//First list
let list = [1; 2; 3; 4; 5]
printfn "OG List: %A" list
printfn "Square List: %A" (sqrList list)
printfn "Even Nums: %A" (evenList list)
printfn "Sum of List: %d" (sumList list)

//Second list
let list1 = [10; 20; 30; 40]
printfn "OG List1: %A" list1
printfn "Square List1: %A" (sqrList list1)
printfn "Even Nums1: %A" (evenList list1)
printfn "Sum of List1: %d" (sumList list1)
