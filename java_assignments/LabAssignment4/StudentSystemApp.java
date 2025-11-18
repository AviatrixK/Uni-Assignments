import java.util.*;
import java.io.*;

/**
 * Student class to represent a student record.
 */
class Student implements Serializable {
    private int rollNo;
    private String name;
    private String email;
    private String course;
    private double marks;

    public Student(int rollNo, String name, String email, String course, double marks) {
        this.rollNo = rollNo;
        this.name = name;
        this.email = email;
        this.course = course;
        this.marks = marks;
    }

    public int getRollNo() {
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

    public double getMarks() {
        return marks;
    }

    @Override
    public String toString() {
        return String.format("Roll: %d | Name: %s | Email: %s | Course: %s | Marks: %.2f",
                rollNo, name, email, course, marks);
    }

    public char[] toCSV() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'toCSV'");
    }
}

/**
 * StudentManager class to manage student operations.
 */
class StudentManager {
    private List<Student> students;
    private static final String FILE_NAME = "students.dat";

    public StudentManager() {
        students = new ArrayList<>();
        loadStudents();
    }

    public void addStudent(Student s) {
        students.add(s);
        System.out.println("Student added successfully!");
    }

    public void viewAllStudents() {
        if (students.isEmpty()) {
            System.out.println("No students found.");
            return;
        }
        System.out.println("\n===== All Students =====");
        for (Student s : students) {
            System.out.println(s);
        }
        System.out.println();
    }

    public void searchByName(String name) {
        boolean found = false;
        System.out.println("\n===== Search Results =====");
        for (Student s : students) {
            if (s.getName().equalsIgnoreCase(name)) {
                System.out.println(s);
                found = true;
            }
        }
        if (!found) {
            System.out.println("No student found with name: " + name);
        }
        System.out.println();
    }

    public void deleteByName(String name) {
        boolean removed = students.removeIf(s -> s.getName().equalsIgnoreCase(name));
        if (removed) {
            System.out.println("Student(s) with name '" + name + "' deleted successfully!");
        } else {
            System.out.println("No student found with name: " + name);
        }
    }

    public void sortByMarks() {
        students.sort((s1, s2) -> Double.compare(s2.getMarks(), s1.getMarks()));
        System.out.println("Students sorted by marks (descending).");
        viewAllStudents();
    }

    public void sortByName() {
        students.sort((s1, s2) -> s1.getName().compareToIgnoreCase(s2.getName()));
        System.out.println("Students sorted by name (alphabetically).");
        viewAllStudents();
    }

    public void showFileUtilities() {
        File file = new File(FILE_NAME);
        System.out.println("\n===== File Utilities =====");
        System.out.println("File Name: " + file.getName());
        System.out.println("File Path: " + file.getAbsolutePath());
        System.out.println("File Exists: " + file.exists());
        System.out.println("File Size: " + file.length() + " bytes");
        System.out.println("Readable: " + file.canRead());
        System.out.println("Writable: " + file.canWrite());
        
        // Random Access File Demo
        try (RandomAccessFile raf = new RandomAccessFile(FILE_NAME, "r")) {
            System.out.println("\n--- Random Access Demo ---");
            System.out.println("File length: " + raf.length() + " bytes");
            if (raf.length() > 0) {
                System.out.println("File pointer at: " + raf.getFilePointer());
            }
        } catch (IOException e) {
            System.out.println("Error accessing file: " + e.getMessage());
        }
        System.out.println();
    }

    public void saveAndExit() {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(FILE_NAME))) {
            oos.writeObject(students);
            System.out.println("Student data saved successfully!");
        } catch (IOException e) {
            System.out.println("Error saving data: " + e.getMessage());
        }
    }

    @SuppressWarnings("unchecked")
    private void loadStudents() {
        File file = new File(FILE_NAME);
        if (!file.exists()) {
            return;
        }
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(FILE_NAME))) {
            students = (List<Student>) ois.readObject();
            System.out.println("Student data loaded successfully!");
        } catch (FileNotFoundException e) {
            System.out.println("No previous data found. Starting fresh.");
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("Error loading data: " + e.getMessage());
        }
    }
}

/**
 * Main entry point for the Student Record Management System.
 */
public class StudentSystemApp {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        StudentManager manager = new StudentManager();

        while (true) {
            System.out.println("===== Capstone Student Menu =====");
            System.out.println("1. Add Student");
            System.out.println("2. View All Students");
            System.out.println("3. Search by Name");
            System.out.println("4. Delete by Name");
            System.out.println("5. Sort by Marks");
            System.out.println("6. Sort by Name (Extra)");
            System.out.println("7. File Attributes & Random Access");
            System.out.println("8. Save and Exit");
            System.out.print("Enter choice: ");

            try {
                String input = sc.nextLine();
                int choice = Integer.parseInt(input);

                switch (choice) {
                    case 1:
                        System.out.print("Enter Roll No: ");
                        int roll = Integer.parseInt(sc.nextLine());
                        System.out.print("Enter Name: ");
                        String name = sc.nextLine();
                        System.out.print("Enter Email: ");
                        String email = sc.nextLine();
                        System.out.print("Enter Course: ");
                        String course = sc.nextLine();
                        System.out.print("Enter Marks: ");
                        double marks = Double.parseDouble(sc.nextLine());

                        Student s = new Student(roll, name, email, course, marks);
                        manager.addStudent(s);
                        break;

                    case 2:
                        manager.viewAllStudents();
                        break;

                    case 3:
                        System.out.print("Enter Name to Search: ");
                        String searchName = sc.nextLine();
                        manager.searchByName(searchName);
                        break;

                    case 4:
                        System.out.print("Enter Name to Delete: ");
                        String delName = sc.nextLine();
                        manager.deleteByName(delName);
                        break;

                    case 5:
                        manager.sortByMarks();
                        break;

                    case 6:
                        manager.sortByName();
                        break;

                    case 7:
                        manager.showFileUtilities();
                        break;

                    case 8:
                        manager.saveAndExit();
                        System.out.println("Exiting system. Goodbye!");
                        sc.close();
                        System.exit(0);
                        break;

                    default:
                        System.out.println("Invalid choice! Please try again.");
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter numbers for Roll/Marks/Choice.");
            } catch (Exception e) {
                System.out.println("An error occurred: " + e.getMessage());
            }
        }
    }
}