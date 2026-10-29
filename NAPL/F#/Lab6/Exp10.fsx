open System
open System.Text.RegularExpressions

// 1. Reverse a string and check palindrome
let reverseString (s: string) =
    new string(Array.rev (s.ToCharArray()))

let isPalindrome (s: string) =
    s = reverseString s

// 2. Transform the string
let transformString (s: string) =
    if s |> Seq.forall Char.IsLetter then
        s.ToUpper()
    elif s |> Seq.forall Char.IsDigit then
        s + s
    else
        s

// 3. Validate email using Regex
let isValidEmail (email: string) =
    Regex.IsMatch(email, @"^[^@\s]+@[^@\s]+\.[^@\s]+$")

// Test cases
printfn "1. Palindrome Checking"
["madam"; "hello"; "level"]
|> List.iter (fun s ->
    printfn "%s -> Reverse: %s, Palindrome: %b"
        s (reverseString s) (isPalindrome s))

printfn "\n2. String Transformation"
["hello"; "123"; "abc123"]
|> List.iter (fun s ->
    printfn "%s -> %s" s (transformString s))

printfn "\n3. Email Validation"
["user@gmail.com"; "abc@"; "hello@yahoo.in"]
|> List.iter (fun email ->
    printfn "%s -> %b" email (isValidEmail email))