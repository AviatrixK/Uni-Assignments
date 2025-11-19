import model.Student;
import service.StudentManager;
import util.InvalidMarksException;
import util.Loader;
import util.StudentNotFoundException;

import java.util.Scanner;

/**
 * Main class - Entry point for Student Record Management System
 * Provides interactive menu-driven interface
 */
public class Main {
    private static StudentManager studentManager;
    private static Scanner scanner;

    public static void main(String[] args) {
        scanner = new Scanner(System.in);
        studentManager = new StudentManager();

        // Display welcome message
        System.out.println("╔═══════════════════════════════════════════════════════╗");
        System.out.println("║   STUDENT RECORD MANAGEMENT SYSTEM                    ║");
        System.out.println("║   Capstone Project - Java Programming                 ║");
        System.out.println("╚═══════════════════════════════════════════════════════╝");
        System.out.println();

        // Load existing records with multithreading
        loadRecordsWithThread();

        // Main menu loop
        boolean running = true;
        while (running) {
            try {
                displayMenu();
                int choice = getChoice();

                switch (choice) {
                    case 1:
                        addStudentOption();
                        break;
                    case 2:
                        viewAllStudentsOption();
                        break;
                    case 3:
                        searchStudentOption();
                        break;
                    case 4:
                        deleteStudentOption();
                        break;
                    case 5:
                        sortByMarksOption();
                        break;
                    case 6:
                        saveAndExitOption();
                        running = false;
                        break;
                    default:
                        System.out.println("Invalid choice! Please enter 1-6.");
                }
            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
            }
            System.out.println();
        }

        scanner.close();
    }

    /**
     * Display main menu
     */
    private static void displayMenu() {
        System.out.println("===== Capstone Student Menu =====");
        System.out.println("1. Add Student");
        System.out.println("2. View All Students");
        System.out.println("3. Search by Name");
        System.out.println("4. Delete by Name");
        System.out.println("5. Sort by Marks");
        System.out.println("6. Save and Exit");
        System.out.print("Enter choice: ");
    }

    /**
     * Get user's menu choice
     * @return User's choice as integer
     */
    private static int getChoice() {
        try {
            return Integer.parseInt(scanner.nextLine().trim());
        } catch (NumberFormatException e) {
            return -1;
        }
    }

    /**
     * Load records from file with multithreading simulation
     */
    private static void loadRecordsWithThread() {
        Loader loader = new Loader("Loading student records", 1000);
        Thread loadThread = new Thread(loader);
        loadThread.start();

        try {
            loadThread.join(); // Wait for loading animation to complete
            studentManager.loadFromFile();
        } catch (InterruptedException e) {
            System.out.println("Loading interrupted");
            Thread.currentThread().interrupt();
        }
        System.out.println();
    }

    /**
     * Option 1: Add a new student
     */
    private static void addStudentOption() {
        System.out.println("\n--- Add New Student ---");
        try {
            Student student = new Student();
            student.inputDetails(scanner);

            // Simulate processing with thread
            Loader.simulateLoading("Adding student");
            studentManager.addStudent(student);

        } catch (InvalidMarksException e) {
            System.out.println("Error: " + e.getMessage());
        } catch (IllegalArgumentException e) {
            System.out.println("Error: " + e.getMessage());
        } catch (Exception e) {
            System.out.println("Error adding student: " + e.getMessage());
        }
    }

    /**
     * Option 2: View all students
     */
    private static void viewAllStudentsOption() {
        Loader.simulateLoading("Loading student records");
        studentManager.viewAllStudents();
    }

    /**
     * Option 3: Search for a student by name
     */
    private static void searchStudentOption() {
        System.out.print("Enter name to search: ");
        String name = scanner.nextLine().trim();

        try {
            Loader.simulateLoading("Searching");
            Student student = studentManager.searchStudent(name);
            System.out.println("\nStudent Info:");
            student.displayDetails();
        } catch (StudentNotFoundException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    /**
     * Option 4: Delete a student by name
     */
    private static void deleteStudentOption() {
        System.out.print("Enter name to delete: ");
        String name = scanner.nextLine().trim();

        try {
            // Confirm deletion
            System.out.print("Are you sure you want to delete this student? (yes/no): ");
            String confirmation = scanner.nextLine().trim();

            if (confirmation.equalsIgnoreCase("yes")) {
                Loader.simulateLoading("Deleting student record");
                studentManager.deleteStudent(name);
            } else {
                System.out.println("Deletion cancelled.");
            }
        } catch (StudentNotFoundException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    /**
     * Option 5: Sort students by marks
     */
    private static void sortByMarksOption() {
        Loader.simulateLoading("Sorting students by marks");
        studentManager.sortStudentsByMarks();
    }

    /**
     * Option 6: Save and exit
     */
    private static void saveAndExitOption() {
        System.out.println("\n--- Saving and Exiting ---");
        Loader.simulateLoading("Saving student records");
        studentManager.saveToFile();
        System.out.println("\nThank you for using Student Record Management System!");
        System.out.println("Goodbye!");
    }
}