package service;

import model.Student;

/**
 * Interface defining CRUD operations for student records
 */
public interface RecordActions {
    // Add a new student
    boolean addStudent(Student student);
    
    // Delete a student by roll number
    boolean deleteStudent(int rollNo);
    
    // Update student information
    boolean updateStudent(int rollNo, Student updatedStudent);
    
    // Search for a student by roll number
    Student searchStudent(int rollNo);
    
    // View all students
    void viewAllStudents();
    
    // Additional method for sorting students
    void sortStudentsByMarks();
    
    // Additional method for sorting by name
    void sortStudentsByName();
}