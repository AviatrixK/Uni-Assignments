package model;

import util.InvalidMarksException;
import java.util.Scanner;

/**
 * Student class extending Person
 * Represents a student with academic information
 */
public class Student extends Person {
    private int rollNo;
    private String course;
    private double marks;
    private String grade;

    // Default constructor
    public Student() {
        super();
    }

    // Parameterized constructor
    public Student(int rollNo, String name, String email, String course, double marks) {
        super(name, email);
        this.rollNo = rollNo;
        this.course = course;
        this.marks = marks;
        this.grade = calculateGrade();
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

    public void setMarks(double marks) throws InvalidMarksException {
        if (marks < 0 || marks > 100) {
            throw new InvalidMarksException("Marks must be between 0 and 100. Provided: " + marks);
        }
        this.marks = marks;
        this.grade = calculateGrade();
    }

    public String getGrade() {
        return grade;
    }

    /**
     * Calculate grade based on marks
     * @return Grade as String
     */
    public String calculateGrade() {
        if (marks >= 90) {
            return "A+";
        } else if (marks >= 80) {
            return "A";
        } else if (marks >= 70) {
            return "B+";
        } else if (marks >= 60) {
            return "B";
        } else if (marks >= 50) {
            return "C";
        } else if (marks >= 40) {
            return "D";
        } else {
            return "F";
        }
    }

    /**
     * Input student details from user
     * @param scanner Scanner object for input
     * @throws InvalidMarksException if marks are invalid
     */
    public void inputDetails(Scanner scanner) throws InvalidMarksException {
        try {
            System.out.print("Enter Roll No: ");
            this.rollNo = Integer.parseInt(scanner.nextLine().trim());

            System.out.print("Enter Name: ");
            this.name = scanner.nextLine().trim();
            if (this.name.isEmpty()) {
                throw new IllegalArgumentException("Name cannot be empty");
            }

            System.out.print("Enter Email: ");
            this.email = scanner.nextLine().trim();
            if (this.email.isEmpty() || !this.email.contains("@")) {
                throw new IllegalArgumentException("Invalid email format");
            }

            System.out.print("Enter Course: ");
            this.course = scanner.nextLine().trim();
            if (this.course.isEmpty()) {
                throw new IllegalArgumentException("Course cannot be empty");
            }

            System.out.print("Enter Marks: ");
            double inputMarks = Double.parseDouble(scanner.nextLine().trim());
            setMarks(inputMarks); // This will call calculateGrade internally

        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("Invalid number format for Roll No or Marks");
        }
    }

    /**
     * Display student details
     */
    public void displayDetails() {
        System.out.println("Roll No: " + rollNo);
        System.out.println("Name: " + name);
        System.out.println("Email: " + email);
        System.out.println("Course: " + course);
        System.out.println("Marks: " + marks);
        System.out.println("Grade: " + grade);
    }

    @Override
    public void displayInfo() {
        displayDetails();
    }

    /**
     * Convert student object to CSV format for file storage
     * @return CSV string representation
     */
    public String toCSV() {
        return rollNo + "," + name + "," + email + "," + course + "," + marks + "," + grade;
    }

    /**
     * Create Student object from CSV string
     * @param csv CSV string
     * @return Student object
     */
    public static Student fromCSV(String csv) throws InvalidMarksException {
        String[] parts = csv.split(",");
        if (parts.length >= 5) {
            int rollNo = Integer.parseInt(parts[0].trim());
            String name = parts[1].trim();
            String email = parts[2].trim();
            String course = parts[3].trim();
            double marks = Double.parseDouble(parts[4].trim());
            return new Student(rollNo, name, email, course, marks);
        }
        return null;
    }

    @Override
    public String toString() {
        return "Student{" +
                "rollNo=" + rollNo +
                ", name='" + name + '\'' +
                ", email='" + email + '\'' +
                ", course='" + course + '\'' +
                ", marks=" + marks +
                ", grade='" + grade + '\'' +
                '}';
    }
}