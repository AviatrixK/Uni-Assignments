
import java.util.*;

/**
 * Manages student records using Collections Framework.
 * NOTE: This class requires Student.java and FileUtil.java to be in the same folder.
 */
public class StudentManager {
    // List for sorting and sequential access
    private ArrayList<Student> studentList;
    // Map for fast lookup and preventing duplicate Roll Nos
    private Map<Integer, Student> studentMap;

    public StudentManager() {
        this.studentList = new ArrayList<>();
        this.studentMap = new HashMap<>();
        loadData();
    }

    // Load data from file at application start
    private void loadData() {
        // Calls FileUtil to get the list of students
        studentList = FileUtil.readStudents();
        
        // Populate Map for O(1) access
        for (Student s : studentList) {
            studentMap.put(s.getRollNo(), s);
        }
        
        // Display immediately as per "Expected Output" if data exists
        if (!studentList.isEmpty()) {
            System.out.println("Loaded students from file:");
            viewAllStudents(); 
        }
    }

    public void addStudent(Student s) {
        if (studentMap.containsKey(s.getRollNo())) {
            System.out.println("Error: Student with Roll No " + s.getRollNo() + " already exists.");
            return;
        }
        studentList.add(s);
        studentMap.put(s.getRollNo(), s);
        System.out.println("Student added successfully.");
    }

    /**
     * Display students using Iterator.
     */
    public void viewAllStudents() {
        if (studentList.isEmpty()) {
            System.out.println("No records found.");
            return;
        }
        Iterator<Student> it = studentList.iterator();
        while (it.hasNext()) {
            System.out.println(it.next());
        }
    }

    public void searchByName(String name) {
        boolean found = false;
        for (Student s : studentList) {
            if (s.getName().equalsIgnoreCase(name)) {
                System.out.println("Student Found:");
                System.out.println(s);
                found = true;
            }
        }
        if (!found) System.out.println("Student not found.");
    }

    public void deleteByName(String name) {
        Iterator<Student> it = studentList.iterator();
        boolean removed = false;
        while (it.hasNext()) {
            Student s = it.next();
            if (s.getName().equalsIgnoreCase(name)) {
                studentMap.remove(s.getRollNo()); // Remove from Map
                it.remove(); // Remove from List safely using Iterator
                System.out.println("Deleted student: " + name);
                removed = true;
            }
        }
        if (!removed) System.out.println("Student not found.");
    }

    /**
     * Sorts students by marks using Comparator (Descending).
     */
    public void sortByMarks() {
        Collections.sort(studentList, new Comparator<Student>() {
            @Override
            public int compare(Student s1, Student s2) {
                // Compare marks in descending order
                return Double.compare(s2.getMarks(), s1.getMarks());
            }
        });
        System.out.println("Sorted Student List by Marks:");
        viewAllStudents();
    }

    /**
     * Sorts students by name using Comparator.
     */
    public void sortByName() {
        Collections.sort(studentList, new Comparator<Student>() {
            @Override
            public int compare(Student s1, Student s2) {
                return s1.getName().compareToIgnoreCase(s2.getName());
            }
        });
        System.out.println("Sorted Student List by Name:");
        viewAllStudents();
    }

    public void saveAndExit() {
        FileUtil.saveStudents(studentList);
    }

    // Wrapper to show file utilities
    public void showFileUtilities() {
        FileUtil.displayFileAttributes();
        FileUtil.readUsingRandomAccess();
    }

    // ==========================================
    // ADDED MAIN METHOD FOR TESTING
    // ==========================================
    public static void main(String[] args) {
        System.out.println("--- Starting StudentManager Test ---");
        
        // 1. Initialize Manager
        StudentManager manager = new StudentManager();

        // 2. Test Adding Students
        // (Using dummy data to test logic)
        manager.addStudent(new Student(901, "TestUser1", "test1@mail.com", "CS", 88.0));
        manager.addStudent(new Student(902, "TestUser2", "test2@mail.com", "IT", 92.5));

        // 3. Test Viewing
        System.out.println("\n--- View All ---");
        manager.viewAllStudents();

        // 4. Test Sorting
        System.out.println("\n--- Sort by Marks ---");
        manager.sortByMarks();

        // 5. Test Deletion
        System.out.println("\n--- Delete TestUser1 ---");
        manager.deleteByName("TestUser1");
        
        System.out.println("\n--- Final View ---");
        manager.viewAllStudents();
        
    }
}
