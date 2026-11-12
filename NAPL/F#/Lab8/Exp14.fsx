open System

// Base class
[<AbstractClass>]
type Shape() =
    abstract member Area : unit -> float

// Derived class - Circle
type Circle(radius: float) =
    inherit Shape()

    override this.Area() =
        Math.PI * radius * radius

// Derived class - Rectangle
type Rectangle(length: float, breadth: float) =
    inherit Shape()

    override this.Area() =
        length * breadth

// Creating objects
let circle = Circle(5.0)
let rectangle = Rectangle(10.0, 5.0)

// Calling methods
printfn "Area of Circle: %f" (circle.Area())
printfn "Area of Rectangle: %f" (rectangle.Area())

// Polymorphism
let shapes: Shape list = [circle; rectangle]

printfn "\nUsing Polymorphism:"

for shape in shapes do
    printfn "Area: %f" (shape.Area())