// package main 

// import "fmt"

// func main(){

// 	var option int 

// 	for {
// 		fmt.Println("To perform integer ops 1 ")
// 		fmt.Println("To perform floating ops 2 ")
// 		fmt.Println("To exit press 3 ")
// 		fmt.Print("Enter you desired option : ")
// 		fmt.Scan(&option)
// 		if(option == 1){
// 			var num1 int
// 			fmt.Print("Enter 1st num : ")
// 			fmt.Scan(&num1)
// 			var num2 int
// 			fmt.Print("Enter 2nd num : ")
// 			fmt.Scan(&num2)
// 			fmt.Printf("Addition : %d\n",num1+num2)
// 			fmt.Printf("Subtraction : %d\n",num1-num2)
// 			fmt.Printf("Multiplication : %d\n",num1*num2)
// 		}else if(option == 2){
// 			var fnum1 float32
// 			fmt.Print("Enter 1st fnum : ")
// 			fmt.Scan(&fnum1)
// 			var fnum2 float32
// 			fmt.Print("Enter 2nd fnum : ")
// 			fmt.Scan(&fnum2)
// 			fmt.Printf("Addition : %f\n",fnum1+fnum2)
// 			fmt.Printf("Subtraction : %f\n",fnum1-fnum2)
// 			fmt.Printf("Multiplication : %f\n",fnum1*fnum2)
// 		}else if(option == 3){
// 			fmt.Print("Exit..")
// 			break
// 		}else{
// 			fmt.Println("Invalid Input!")
// 		}
// 	}
// }