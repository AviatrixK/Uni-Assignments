package java_assignments.LabAssignment2.StudentManagementSystem;
import java_assignments.LabAssignment2.StudentManagementSystem.model.Student;
import java_assignments.LabAssignment2.StudentManagementSystem.model.Person;
import java_assignments.LabAssignment2.StudentManagementSystem.service.*;

public class Main {
    public static void main(String[] args) {
        // Create StudentManager instance
        StudentManager manager = new StudentManager();
        
        System.out.println("=== Student Management System ===\n");
        
        // Demonstrate polymorphism - Person reference to Student object
        Person person1 = new Student("Ankit", "ankit@mail.com", 101, "B.Tech", 85.5);
        Person person2 = new Student("Riya", "riya@mail.com", 102, "M.Tech", 92.0);
        
        // Add students to the system
        manager.addStudent((Student) person1);
        manager.addStudent((Student) person2);
        
        // Display students using polymorphic method call
        System.out.println("\n--- Displaying Students Using Polymorphism ---");
        person1.displayInfo();
        System.out.println();
        
        // Display with research area for M.Tech student
        ((Student) person2).displayInfo("AI");
        System.out.println();
        
        // Demonstrate method overloading
        System.out.println("\n--- Method Overloading Demonstration ---");
        ((Student) person1).displayInfo(true);
        System.out.println();
        
        // Add more students
        Student student3 = new Student("Priya", "priya@mail.com", 103, "B.Tech", 78.0);
        Student student4 = new Student("Rahul", "rahul@mail.com", 104, "MCA", 88.5);
        
        manager.addStudent(student3);
        manager.addStudent(student4);
        
        // Try to add duplicate roll number
        System.out.println("\n--- Testing Duplicate Prevention ---");
        Student duplicate = new Student("Duplicate", "dup@mail.com", 101, "B.Tech", 75.0);
        manager.addStudent(duplicate);
        
        // Search for a student
        System.out.println("\n--- Search Student ---");
        Student found = manager.searchStudent(103);
        if (found != null) {
            found.displayInfo();
        }
        
        // View all students before sorting
        System.out.println("\n--- All Students Before Sorting ---");
        manager.viewAllStudents();
        
        // Sort by marks
        System.out.println("\n--- Sorting by Marks ---");
        manager.sortStudentsByMarks();
        manager.viewAllStudents();
        
        // Sort by name
        System.out.println("\n--- Sorting by Name ---");
        manager.sortStudentsByName();
        manager.viewAllStudents();
        
        // Update a student
        System.out.println("\n--- Update Student ---");
        Student updatedInfo = new Student("Priya Sharma", "priya.sharma@mail.com", 
                                         103, "B.Tech", 82.0);
        manager.updateStudent(103, updatedInfo);
        
        // Display updated student
        Student updated = manager.searchStudent(103);
        if (updated != null) {
            updated.displayInfo();
        }
        
        // Display statistics
        System.out.println("\n--- Statistics ---");
        System.out.println("Total Students: " + manager.getTotalStudents());
        System.out.println("Average Marks: " + 
                         String.format("%.2f", manager.calculateAverageMarks()));
        
        // Delete a student
        System.out.println("\n--- Delete Student ---");
        manager.deleteStudent(104);
        
        // Final display
        System.out.println("\n--- Final Student List ---");
        manager.viewAllStudents();
        
        // Demonstrate final method
        System.out.println("\n--- Final Method Demonstration ---");
        ((Student) person1).displayFinalInfo();
        
        // Force garbage collection to demonstrate finalize (educational purposes)
        System.out.println("\n--- Finalize Demonstration ---");
        Student tempStudent = new Student("Temp", "temp@mail.com", 999, "Temp", 50.0);
        tempStudent = null;
        System.gc();
        
        // Small delay to allow finalize to be called
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}