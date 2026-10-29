
package main

import "testing"

func TestDivideValid(t *testing.T) {
	result, err := divide(10, 2)

	if err != nil {
		t.Fatalf("unexpected error: %v", err)
	}
	if result != 5 {
		t.Errorf("expected 5, got %v", result)
	}
}

func TestDivideByZero(t *testing.T) {
	_, err := divide(10, 0)

	if err == nil {
		t.Fatal("expected division by zero error")
	}
}

func TestSquareRootValid(t *testing.T) {
	result, err := squareRoot(25)

	if err != nil {
		t.Fatalf("unexpected error: %v", err)
	}
	if result != 5 {
		t.Errorf("expected 5, got %v", result)
	}
}

func TestSquareRootNegative(t *testing.T) {
	_, err := squareRoot(-9)

	if err == nil {
		t.Fatal("expected negative square root error")
	}
}

func TestInputValid(t *testing.T) {
	result, err := checkInput("Hello")

	if err != nil {
		t.Fatalf("unexpected error: %v", err)
	}
	if result != "Hello" {
		t.Errorf("expected Hello, got %v", result)
	}
}

func TestInputEmpty(t *testing.T) {
	_, err := checkInput("")

	if err == nil {
		t.Fatal("expected empty input error")
	}
}
