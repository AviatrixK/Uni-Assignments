package model;

/**
 * Abstract class representing a Person with common fields
 */
public abstract class Person {
    protected String name;
    protected String email;
    
    // Constructor
    public Person(String name, String email) {
        this.name = name;
        this.email = email;
    }
    
    // Abstract method to be implemented by subclasses
    public abstract void displayInfo();
    
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
}