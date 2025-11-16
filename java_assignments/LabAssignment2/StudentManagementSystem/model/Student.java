package java_assignments.LabAssignment2.StudentManagementSystem.model;

/**
 * Student class extending Person with additional fields
 * Declared as final to demonstrate final class concept
 */
public final class Student extends Person {
    private int rollNo;
    private String course;
    private double marks;
    private char grade;
    
    // Constructor
    public Student(String name, String email, int rollNo, String course, double marks) {
        super(name, email);
        this.rollNo = rollNo;
        this.course = course;
        this.marks = marks;
        this.grade = calculateGrade(marks);
    }
    
    // Calculate grade based on marks
    private char calculateGrade(double marks) {
        if (marks >= 90) return 'A';
        else if (marks >= 80) return 'B';
        else if (marks >= 70) return 'C';
        else if (marks >= 60) return 'D';
        else return 'F';
    }
    
    // Override displayInfo from Person class
    @Override
    public void displayInfo() {
        System.out.println("Student Info:");
        System.out.println("Roll No: " + rollNo);
        System.out.println("Name: " + name);
        System.out.println("Email: " + email);
        System.out.println("Course: " + course);
        System.out.println("Marks: " + marks);
        System.out.println("Grade: " + grade);
    }
    
    // Method overloading - display with additional parameter
    public void displayInfo(boolean detailed) {
        System.out.println("[Note] Overloaded display method:");
        displayInfo();
        if (detailed) {
            System.out.println("This is a final method in a final class.");
        }
    }
    
    // Method overloading - display with research area for M.Tech students
    public void displayInfo(String researchArea) {
        System.out.println("Student Info:");
        System.out.println("Roll No: " + rollNo);
        System.out.println("Name: " + name);
        System.out.println("Email: " + email);
        System.out.println("Course: " + course);
        if (course.equalsIgnoreCase("M.Tech")) {
            System.out.println("Research Area: " + researchArea);
        }
    }
    
    // Final method that cannot be overridden
    public final void displayFinalInfo() {
        System.out.println("This is a final method in a final class.");
    }
    
    // Finalize method (deprecated but shown for educational purposes)
    @Override
    protected void finalize() throws Throwable {
        System.out.println("Finalize method called before object is garbage collected.");
        super.finalize();
    }
    
    // Getters and Setters
    public int getRollNo() {
        return rollNo;
    }
    
    public void setRollNo(int rollNo) {
        this.rollNo = rollNo;
    }
    
    public String getCourse() {
        return course;
    }
    
    public void setCourse(String course) {
        this.course = course;
    }
    
    public double getMarks() {
        return marks;
    }
    
    public void setMarks(double marks) {
        this.marks = marks;
        this.grade = calculateGrade(marks);
    }
    
    public char getGrade() {
        return grade;
    }
}