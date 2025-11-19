package model;

/**
 * Abstract class representing a Person with basic information
 * Demonstrates abstraction and inheritance concepts
 */
public abstract class Person {
    protected String name;
    protected String email;

    // Default constructor
    public Person() {
    }

    // Parameterized constructor
    public Person(String name, String email) {
        this.name = name;
        this.email = email;
    }

    // Getters and Setters
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    // Abstract method to be implemented by subclasses
    public abstract void displayInfo();
}