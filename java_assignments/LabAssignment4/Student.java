import java.io.Serializable;

/**
 * Represents a Student entity.
 * contains details: Roll No, Name, Email, Course, Marks.
 */
public class Student {
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

    // Getters
    public int getRollNo() { return rollNo; }
    public String getName() { return name; }
    public String getEmail() { return email; }
    public String getCourse() { return course; }
    public double getMarks() { return marks; }

    /**
     * Formats student data for CSV file storage.
     * Format: rollNo,name,email,course,marks
     */
    public String toCSV() {
        return rollNo + "," + name + "," + email + "," + course + "," + marks;
    }

    /**
     * Formats student data for display as per assignment requirement.
     */
    @Override
    public String toString() {
        return "Roll No: " + rollNo + "\n" +
               "Name: " + name + "\n" +
               "Email: " + email + "\n" +
               "Course: " + course + "\n" +
               "Marks: " + marks + "\n";
    }

    // ==========================================
    // Main Method for Testing this Class
    // ==========================================
    public static void main(String[] args) {
        // Create a dummy student object to test the class
        Student testStudent = new Student(101, "Ankit", "ankit@mail.com", "B.Tech", 85.5);

        System.out.println("--- Testing Display Format (toString) ---");
        System.out.println(testStudent.toString());

        System.out.println("--- Testing File Storage Format (toCSV) ---");
        System.out.println(testStudent.toCSV());
        
        // Verification
        if(testStudent.toCSV().equals("101,Ankit,ankit@mail.com,B.Tech,85.5")) {
            System.out.println("\nResult: CSV Generation Successful.");
        }
    }
}