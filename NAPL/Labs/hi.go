package main
import "fmt"

func main(){
	//Arithmetic operation for float
	var fnum1 float32 = 4.2
	var fnum2 float32 = 5.6
	//Printing O/P using formatted Printf
	fmt.Printf("Addition : %f\n",fnum1+fnum2)
	fmt.Printf("Subtraction : %f\n",fnum1-fnum2)
	fmt.Printf("Multiplication : %f\n",fnum1*fnum2)

	//Arithmetic operation for int
	var num1 int = 4
	var num2 int = 5
	//Printing O/P using formatted Printf
	fmt.Printf("Addition : %d\n",num1+num2)
	fmt.Printf("Subtraction : %d\n",num1-num2)
	fmt.Printf("Multiplication : %d\n",num1*num2)
} 
