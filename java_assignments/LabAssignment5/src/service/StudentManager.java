package service;

import model.Student;
import util.InvalidMarksException;
import util.StudentNotFoundException;

import java.io.*;
import java.util.*;

/**
 * StudentManager class implementing RecordActions interface
 * Manages all CRUD operations for student records
 */
public class StudentManager implements RecordActions {
    private List<Student> studentList;
    private Map<Integer, Student> studentMap;
    private static final String FILE_NAME = "students.txt";

    public StudentManager() {
        studentList = new ArrayList<>();
        studentMap = new HashMap<>();
    }

    /**
     * Add a new student to the system
     * @param student Student object to add
     */
    @Override
    public void addStudent(Student student) {
        // Check for duplicate roll number
        if (studentMap.containsKey(student.getRollNo())) {
            System.out.println("Error: Student with Roll No " + student.getRollNo() + " already exists!");
            return;
        }

        studentList.add(student);
        studentMap.put(student.getRollNo(), student);
        System.out.println("Student added successfully!");
    }

    /**
     * Delete a student by name
     * @param name Name of the student to delete
     * @throws StudentNotFoundException if student is not found
     */
    @Override
    public void deleteStudent(String name) throws StudentNotFoundException {
        Student studentToDelete = null;

        for (Student student : studentList) {
            if (student.getName().equalsIgnoreCase(name)) {
                studentToDelete = student;
                break;
            }
        }

        if (studentToDelete == null) {
            throw new StudentNotFoundException("Student with name '" + name + "' not found!");
        }

        studentList.remove(studentToDelete);
        studentMap.remove(studentToDelete.getRollNo());
        System.out.println("Student record deleted successfully.");
    }

    /**
     * Update student information
     * @param rollNo Roll number of the student to update
     * @param updatedStudent Updated student object
     * @throws StudentNotFoundException if student is not found
     */
    @Override
    public void updateStudent(int rollNo, Student updatedStudent) throws StudentNotFoundException {
        if (!studentMap.containsKey(rollNo)) {
            throw new StudentNotFoundException("Student with Roll No " + rollNo + " not found!");
        }

        Student existingStudent = studentMap.get(rollNo);
        int index = studentList.indexOf(existingStudent);

        studentList.set(index, updatedStudent);
        studentMap.put(rollNo, updatedStudent);
        System.out.println("Student record updated successfully.");
    }

    /**
     * Search for a student by name
     * @param name Name of the student to search
     * @return Student object if found
     * @throws StudentNotFoundException if student is not found
     */
    @Override
    public Student searchStudent(String name) throws StudentNotFoundException {
        for (Student student : studentList) {
            if (student.getName().equalsIgnoreCase(name)) {
                return student;
            }
        }
        throw new StudentNotFoundException("Student with name '" + name + "' not found!");
    }

    /**
     * View all students in the system
     */
    @Override
    public void viewAllStudents() {
        if (studentList.isEmpty()) {
            System.out.println("No student records available.");
            return;
        }

        System.out.println("\n========== All Students ==========");
        Iterator<Student> iterator = studentList.iterator();
        while (iterator.hasNext()) {
            Student student = iterator.next();
            student.displayDetails();
            System.out.println("----------------------------------");
        }
    }

    /**
     * Sort students by marks in descending order
     */
    public void sortStudentsByMarks() {
        if (studentList.isEmpty()) {
            System.out.println("No student records to sort.");
            return;
        }

        // Using Comparator to sort by marks in descending order
        Collections.sort(studentList, new Comparator<Student>() {
            @Override
            public int compare(Student s1, Student s2) {
                return Double.compare(s2.getMarks(), s1.getMarks());
            }
        });

        System.out.println("\n========== Sorted Student List by Marks ==========");
        Iterator<Student> iterator = studentList.iterator();
        while (iterator.hasNext()) {
            Student student = iterator.next();
            student.displayDetails();
            System.out.println("----------------------------------");
        }
    }

    /**
     * Load student records from file
     */
    public void loadFromFile() {
        File file = new File(FILE_NAME);
        if (!file.exists()) {
            System.out.println("No existing student records found. Starting fresh.");
            return;
        }

        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new FileReader(FILE_NAME));
            String line;
            int count = 0;

            while ((line = reader.readLine()) != null) {
                try {
                    Student student = Student.fromCSV(line);
                    if (student != null) {
                        studentList.add(student);
                        studentMap.put(student.getRollNo(), student);
                        count++;
                    }
                } catch (Exception e) {
                    System.out.println("Error parsing line: " + line);
                }
            }

            System.out.println("Loaded " + count + " student record(s) from file.");

        } catch (FileNotFoundException e) {
            System.out.println("Student data file not found.");
        } catch (IOException e) {
            System.out.println("Error reading student data: " + e.getMessage());
        } finally {
            try {
                if (reader != null) {
                    reader.close();
                }
            } catch (IOException e) {
                System.out.println("Error closing file: " + e.getMessage());
            }
        }
    }

    /**
     * Save student records to file
     */
    public void saveToFile() {
        BufferedWriter writer = null;
        try {
            writer = new BufferedWriter(new FileWriter(FILE_NAME));

            for (Student student : studentList) {
                writer.write(student.toCSV());
                writer.newLine();
            }

            System.out.println("Student records saved successfully.");

        } catch (IOException e) {
            System.out.println("Error saving student data: " + e.getMessage());
        } finally {
            try {
                if (writer != null) {
                    writer.close();
                }
            } catch (IOException e) {
                System.out.println("Error closing file: " + e.getMessage());
            }
        }
    }

    /**
     * Get the list of all students
     * @return List of students
     */
    public List<Student> getStudentList() {
        return studentList;
    }

    /**
     * Get the count of students
     * @return Number of students
     */
    public int getStudentCount() {
        return studentList.size();
    }
}