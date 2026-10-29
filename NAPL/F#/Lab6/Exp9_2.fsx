let rec isPrime n i =
    if n < 2 then false
    elif i * i > n then true
    elif n % i = 0 then false
    else isPrime n (i + 1)

printf "Enter a number: "
let n = int (System.Console.ReadLine())

if isPrime n 2 then
    printfn "Prime Number"
else
    printfn "Not a Prime Number"