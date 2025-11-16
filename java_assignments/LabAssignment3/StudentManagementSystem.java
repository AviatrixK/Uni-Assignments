package java_assignments.LabAssignment3;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.InputMismatchException;

public class StudentManagementSystem {
    private static Scanner scanner = new Scanner(System.in);
    private static StudentManager studentManager = new StudentManager();
    
    // Main method
    public static void main(String[] args) {
        System.out.println("=== Student Management System ===");
        System.out.println("================================\n");
        
        boolean continueRunning = true;
        
        while (continueRunning) {
            try {
                displayMenu();
                int choice = scanner.nextInt();
                scanner.nextLine(); // Clear buffer
                
                switch (choice) {
                    case 1:
                        addNewStudent();
                        break;
                    case 2:
                        displayStudentInfo();
                        break;
                    case 3:
                        continueRunning = false;
                        System.out.println("Program execution completed.");
                        break;
                    default:
                        System.out.println("Invalid choice! Please try again.");
                }
                
            } catch (InputMismatchException e) {
                System.err.println("Invalid input! Please enter a number.");
                scanner.nextLine(); // Clear invalid input
            } catch (Exception e) {
                System.err.println("An error occurred: " + e.getMessage());
            } finally {
                System.out.println("\n--------------------------------\n");
            }
        }
        
        scanner.close();
    }
    
    private static void displayMenu() {
        System.out.println("Select an option:");
        System.out.println("1. Add New Student");
        System.out.println("2. Display Student Information");
        System.out.println("3. Exit");
        System.out.print("Enter your choice: ");
    }
    
    private static void addNewStudent() {
        try {
            // Using wrapper classes for autoboxing
            System.out.print("Enter Roll No (Integer): ");
            Integer rollNo = Integer.valueOf(scanner.nextLine());
            
            System.out.print("Enter Name: ");
            String name = scanner.nextLine();
            
            System.out.print("Enter Email: ");
            String email = scanner.nextLine();
            
            System.out.print("Enter Course: ");
            String course = scanner.nextLine();
            
            System.out.print("Enter Marks: ");
            Double marks = Double.valueOf(scanner.nextLine());
            
            // Validate input
            studentManager.validateInput(name, email, course, marks);
            
            // Create student object
            Student student = new Student(rollNo, name, email, course, marks);
            
            // Add student (includes loading simulation)
            studentManager.addStudent(student);
            
            // Display added student information
            System.out.println("\nStudent added successfully!");
            studentManager.displayStudent(rollNo);
            
        } catch (NumberFormatException e) {
            System.err.println("Error: Invalid number format! " + e.getMessage());
        } catch (InvalidInputException e) {
            System.err.println("Input Error: " + e.getMessage());
        } catch (StudentNotFoundException e) {
            System.err.println("Student Error: " + e.getMessage());
        } catch (InterruptedException e) {
            System.err.println("Threading Error: " + e.getMessage());
            Thread.currentThread().interrupt();
        } catch (Exception e) {
            System.err.println("Unexpected error: " + e.getMessage());
        }
    }
    
    private static void displayStudentInfo() {
        try {
            System.out.print("Enter Roll No to search: ");
            Integer rollNo = Integer.valueOf(scanner.nextLine());
            
            // Simulate loading for search operation
            System.out.print("Searching");
            Thread searchThread = new Thread(() -> {
                try {
                    for (int i = 0; i < 3; i++) {
                        Thread.sleep(300);
                        System.out.print(".");
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            });
            searchThread.start();
            searchThread.join();
            System.out.println("\n");
            
            studentManager.displayStudent(rollNo);
            
        } catch (NumberFormatException e) {
            System.err.println("Error: Please enter a valid integer for Roll No!");
        } catch (StudentNotFoundException e) {
            System.err.println("Error: " + e.getMessage());
        } catch (InterruptedException e) {
            System.err.println("Search interrupted: " + e.getMessage());
            Thread.currentThread().interrupt();
        } catch (Exception e) {
            System.err.println("Unexpected error: " + e.getMessage());
        }
    }
    
    // RecordActions Interface
    interface RecordActions {
        void addStudent(Student student) throws InterruptedException;
        void displayStudent(Integer rollNo) throws StudentNotFoundException;
        void validateInput(String name, String email, String course, Double marks) throws InvalidInputException;
        String calculateGrade(Double marks);
    }
    
    // Student Class
    static class Student {
        private Integer rollNo;
        private String name;
        private String email;
        private String course;
        private Double marks;
        private String grade;
        
        // Constructor
        public Student(Integer rollNo, String name, String email, String course, Double marks) {
            this.rollNo = rollNo;
            this.name = name;
            this.email = email;
            this.course = course;
            this.marks = marks;
        }
        
        // Getters
        public Integer getRollNo() {
            return rollNo;
        }
        
        public String getName() {
            return name;
        }
        
        public String getEmail() {
            return email;
        }
        
        public String getCourse() {
            return course;
        }
        
        public Double getMarks() {
            return marks;
        }
        
        public String getGrade() {
            return grade;
        }
        
        // Setters
        public void setRollNo(Integer rollNo) {
            this.rollNo = rollNo;
        }
        
        public void setName(String name) {
            this.name = name;
        }
        
        public void setEmail(String email) {
            this.email = email;
        }
        
        public void setCourse(String course) {
            this.course = course;
        }
        
        public void setMarks(Double marks) {
            this.marks = marks;
        }
        
        public void setGrade(String grade) {
            this.grade = grade;
        }
        
        @Override
        public String toString() {
            return "Roll No: " + rollNo + "\n" +
                   "Name: " + name + "\n" +
                   "Email: " + email + "\n" +
                   "Course: " + course + "\n" +
                   "Marks: " + marks + "\n" +
                   "Grade: " + grade;
        }
    }
    
    // StudentManager Class
    static class StudentManager implements RecordActions {
        private Map<Integer, Student> studentDatabase;
        
        public StudentManager() {
            this.studentDatabase = new HashMap<>();
        }
        
        @Override
        public void addStudent(Student student) throws InterruptedException {
            // Calculate grade before adding
            String grade = calculateGrade(student.getMarks());
            student.setGrade(grade);
            
            // Simulate loading process using thread
            Loader loader = new Loader();
            Thread loadingThread = new Thread(loader);
            loadingThread.start();
            loadingThread.join(); // Wait for loading to complete
            
            // Add student to database
            studentDatabase.put(student.getRollNo(), student);
            
            System.out.println();
        }
        
        @Override
        public void displayStudent(Integer rollNo) throws StudentNotFoundException {
            if (!studentDatabase.containsKey(rollNo)) {
                throw new StudentNotFoundException("Student with Roll No " + rollNo + " not found!");
            }
            
            Student student = studentDatabase.get(rollNo);
            System.out.println(student);
            System.out.println("Display operation completed.");
        }
        
        @Override
        public void validateInput(String name, String email, String course, Double marks) 
                throws InvalidInputException {
            // Validate name
            if (name == null || name.trim().isEmpty()) {
                throw new InvalidInputException("Name cannot be empty!");
            }
            
            // Validate email
            if (email == null || email.trim().isEmpty()) {
                throw new InvalidInputException("Email cannot be empty!");
            }
            if (!email.contains("@") || !email.contains(".")) {
                throw new InvalidInputException("Invalid email format!");
            }
            
            // Validate course
            if (course == null || course.trim().isEmpty()) {
                throw new InvalidInputException("Course cannot be empty!");
            }
            
            // Validate marks
            if (marks == null) {
                throw new InvalidInputException("Marks cannot be null!");
            }
            if (marks < 0 || marks > 100) {
                throw new InvalidInputException("Marks must be between 0 and 100!");
            }
        }
        
        @Override
        public String calculateGrade(Double marks) {
            if (marks >= 90) return "A+";
            else if (marks >= 80) return "A";
            else if (marks >= 70) return "B";
            else if (marks >= 60) return "C";
            else if (marks >= 50) return "D";
            else if (marks >= 40) return "E";
            else return "F";
        }
        
        public Student getStudent(Integer rollNo) throws StudentNotFoundException {
            if (!studentDatabase.containsKey(rollNo)) {
                throw new StudentNotFoundException("Student with Roll No " + rollNo + " not found!");
            }
            return studentDatabase.get(rollNo);
        }
    }
    
    // Loader Class (for multithreading)
    static class Loader implements Runnable {
        private static final int LOADING_TIME = 3000; // 3 seconds
        private static final int DOT_INTERVAL = 500; // 0.5 seconds
        
        @Override
        public void run() {
            try {
                System.out.print("Loading");
                
                int totalTime = 0;
                while (totalTime < LOADING_TIME) {
                    Thread.sleep(DOT_INTERVAL);
                    System.out.print(".");
                    totalTime += DOT_INTERVAL;
                }
                
                System.out.println(" Complete!");
                
            } catch (InterruptedException e) {
                System.err.println("Loading interrupted: " + e.getMessage());
                Thread.currentThread().interrupt();
            }
        }
        
        // Alternative method for custom loading message
        public void loadWithMessage(String message) {
            try {
                System.out.print(message);
                
                for (int i = 0; i < 5; i++) {
                    Thread.sleep(DOT_INTERVAL);
                    System.out.print(".");
                }
                
                System.out.println(" Done!");
                
            } catch (InterruptedException e) {
                System.err.println("Loading interrupted: " + e.getMessage());
                Thread.currentThread().interrupt();
            }
        }
    }
    
    // Custom Exception - StudentNotFoundException
    static class StudentNotFoundException extends Exception {
        
        public StudentNotFoundException() {
            super("Student not found in the database!");
        }
        
        public StudentNotFoundException(String message) {
            super(message);
        }
        
        public StudentNotFoundException(String message, Throwable cause) {
            super(message, cause);
        }
    }
    
    // Custom Exception - InvalidInputException
    static class InvalidInputException extends Exception {
        
        public InvalidInputException() {
            super("Invalid input provided!");
        }
        
        public InvalidInputException(String message) {
            super(message);
        }
        
        public InvalidInputException(String message, Throwable cause) {
            super(message, cause);
        }
    }
}