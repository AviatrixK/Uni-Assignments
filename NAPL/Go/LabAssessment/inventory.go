package main

import ( 
		"fmt"
		"errors"
)
type Item struct {
	Id int 
	Name string 
	Quantity int 
	Price float32	 
}

func addItem(inv *[]Item, item Item) error {
	if item.Id <= 0 || item.Name == "" || item.Quantity <= 0 || item.Price <= 0 {
		return errors.New("invalid item details")
	}

	for _, i := range *inv {
		if i.Id == item.Id {
			return errors.New("item already exists")
		}
	}

	*inv = append(*inv, item)
	return nil
}


func removeItem(inv *[]Item, id int) error {
	for i, item := range *inv {
		if item.Id == id {
			*inv = append((*inv)[:i], (*inv)[i+1:]...)
			return nil
		}
	}

	return errors.New("item not found")
}

func summary(inv []Item) {
	ch := make(chan float32)

	go func() {
		var total float32
		for _, item := range inv {
			total += float32(item.Quantity) * item.Price
		}
		ch <- total
	}()

	total := <-ch

	fmt.Println("Total Items:", len(inv))
	fmt.Println("Total Inventory Value:", total)
}

func main() {
	var inv []Item

	inv = append(inv, Item{Id: 1, Name: "Milk", Quantity: 5, Price: 36.5})
	inv = append(inv, Item{Id: 2, Name: "Honey", Quantity: 8, Price: 50})

	fmt.Println("Inventory:", inv)

	for i, item := range inv {
		if item.Id == 1 {
			inv = append(inv[:i], inv[i+1:]...)
			break
		}
	}

	fmt.Println("After Removing:", inv)
}
