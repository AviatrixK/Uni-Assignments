package service;

import model.Student;
import java.util.*;

/**
 * StudentManager class implementing RecordActions interface
 * Handles all CRUD operations on student records
 */
public class StudentManager implements RecordActions {
    // Using both List and Map for efficient management
    private List<Student> studentList;
    private Map<Integer, Student> studentMap;
    
    // Constructor
    public StudentManager() {
        this.studentList = new ArrayList<>();
        this.studentMap = new HashMap<>();
    }
    
    @Override
    public boolean addStudent(Student student) {
        // Check for duplicate roll number
        if (studentMap.containsKey(student.getRollNo())) {
            System.out.println("Error: Student with roll number " + 
                             student.getRollNo() + " already exists!");
            return false;
        }
        
        studentList.add(student);
        studentMap.put(student.getRollNo(), student);
        System.out.println("Student added successfully!");
        return true;
    }
    
    @Override
    public boolean deleteStudent(int rollNo) {
        Student student = studentMap.get(rollNo);
        if (student == null) {
            System.out.println("Error: Student with roll number " + 
                             rollNo + " not found!");
            return false;
        }
        
        studentList.remove(student);
        studentMap.remove(rollNo);
        System.out.println("Student deleted successfully!");
        return true;
    }
    
    @Override
    public boolean updateStudent(int rollNo, Student updatedStudent) {
        Student existingStudent = studentMap.get(rollNo);
        if (existingStudent == null) {
            System.out.println("Error: Student with roll number " + 
                             rollNo + " not found!");
            return false;
        }
        
        // Update student information
        existingStudent.setName(updatedStudent.getName());
        existingStudent.setEmail(updatedStudent.getEmail());
        existingStudent.setCourse(updatedStudent.getCourse());
        existingStudent.setMarks(updatedStudent.getMarks());
        
        System.out.println("Student updated successfully!");
        return true;
    }
    
    @Override
    public Student searchStudent(int rollNo) {
        Student student = studentMap.get(rollNo);
        if (student == null) {
            System.out.println("Student with roll number " + 
                             rollNo + " not found!");
        }
        return student;
    }
    
    @Override
    public void viewAllStudents() {
        if (studentList.isEmpty()) {
            System.out.println("No students in the system.");
            return;
        }
        
        System.out.println("\n=== All Students ===");
        for (Student student : studentList) {
            student.displayInfo();
            System.out.println("-------------------");
        }
    }
    
    @Override
    public void sortStudentsByMarks() {
        Collections.sort(studentList, new Comparator<Student>() {
            @Override
            public int compare(Student s1, Student s2) {
                return Double.compare(s2.getMarks(), s1.getMarks()); // Descending order
            }
        });
        System.out.println("Students sorted by marks (highest to lowest).");
    }
    
    @Override
    public void sortStudentsByName() {
        Collections.sort(studentList, new Comparator<Student>() {
            @Override
            public int compare(Student s1, Student s2) {
                return s1.getName().compareTo(s2.getName());
            }
        });
        System.out.println("Students sorted by name (alphabetically).");
    }
    
    // Method to get total number of students
    public int getTotalStudents() {
        return studentList.size();
    }
    
    // Method to calculate average marks
    public double calculateAverageMarks() {
        if (studentList.isEmpty()) return 0;
        
        double totalMarks = 0;
        for (Student student : studentList) {
            totalMarks += student.getMarks();
        }
        return totalMarks / studentList.size();
    }
}