open System

let task taskid waitTime = async {
    printfn "Task %d Started" taskid
    do! Async.Sleep(3000 * waitTime)
    printfn "Task %d Completed" taskid
    return taskid * 2
}

// Parallel execution
let tasks = [| task 1 1; task 2 2; task 3 3 |]
             |> Async.Parallel

let results = Async.RunSynchronously tasks

printfn "Results:"
results |> Array.iter (fun x -> printfn "%d" x)