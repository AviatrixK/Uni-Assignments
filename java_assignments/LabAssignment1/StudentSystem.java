import java.util.Scanner;

class Student {
    int studentID;
    String studentName;
    String major;
    double score;
    char letterGrade;

    Student(int id, String name, String course, double marks) {
        this.studentID = id;
        this.studentName = name;
        this.major = course;
        this.score = marks;
        this.letterGrade = calculateGrade();
    }

    public char calculateGrade() {
        if (score >= 90) {
            return 'A';
        } else if (score >= 80) {
            return 'B';
        } else if (score >= 70) {
            return 'C';
        } else if (score >= 60) {
            return 'D';
        } else {
            return 'F';
        }
    }

    public void displayStudentDetails() {
        System.out.println("Student ID: " + this.studentID);
        System.out.println("Name: " + this.studentName);
        System.out.println("Course: " + this.major);
        System.out.println("Score: " + this.score);
        System.out.println("Grade: " + this.letterGrade);
        System.out.println("------------------------------");
    }

    public char[] toCSV() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'toCSV'");
    }
}

public class StudentSystem {
    static Scanner userInput = new Scanner(System.in);
    static Student[] studentDatabase = new Student[100];
    static int recordCount = 0;

    public static void main(String[] args) {
        int option;
        do {
            System.out.println("===== Student Menu =====");
            System.out.println("1. Add a New Student");
            System.out.println("2. Display All Students");
            System.out.println("3. Exit");
            System.out.println("========================");
            System.out.print("Enter your choice: ");
            option = userInput.nextInt();
            userInput.nextLine();
            switch (option) {
                case 1:
                    addStudentRecord();
                    break;
                case 2:
                    displayAllRecords();
                    break;
                case 3:
                    System.out.println("Exiting program. Goodbye!");
                    break;
                default:
                    System.out.println("Wrong choice! Please enter 1, 2, or 3.");
            }
            System.out.println();
        } while (option != 3);
    }

    public static void addStudentRecord() {
        if (recordCount >= studentDatabase.length) {
            System.out.println("Cannot add more students. The database is full.");
            return;
        }
        System.out.print("Enter Student Roll No. : ");
        int id = userInput.nextInt();
        userInput.nextLine();
        System.out.print("Enter Name: ");
        String name = userInput.nextLine();
        System.out.print("Enter Course: ");
        String course = userInput.nextLine();
        double marks = -1;
        while (marks < 0 || marks > 100) {
            System.out.print("Enter Score (between 0 and 100): ");
            marks = userInput.nextDouble();
            if (marks < 0 || marks > 100) {
                System.out.println("Invalid score. Please try again.");
            }
        }
        Student newStudent = new Student(id, name, course, marks);
        studentDatabase[recordCount] = newStudent;
        recordCount++;
        System.out.println("Student record added successfully!");
    }

    public static void displayAllRecords() {
        if (recordCount == 0) {
            System.out.println("No student records to display.");
            return;
        }
        System.out.println("\n--- All Student Details ---");
        for (int i = 0; i < recordCount; i++) {
            studentDatabase[i].displayStudentDetails();
        }
    }
}