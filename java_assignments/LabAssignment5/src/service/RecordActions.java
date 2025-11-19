package service;

import model.Student;
import util.StudentNotFoundException;

/**
 * Interface defining the contract for student record management operations
 * Demonstrates interface implementation
 */
public interface RecordActions {
    void addStudent(Student student);
    void deleteStudent(String name) throws StudentNotFoundException;
    void updateStudent(int rollNo, Student updatedStudent) throws StudentNotFoundException;
    Student searchStudent(String name) throws StudentNotFoundException;
    void viewAllStudents();
}