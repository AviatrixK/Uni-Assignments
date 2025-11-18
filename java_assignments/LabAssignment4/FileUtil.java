import java.io.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Utility class for File Handling operations.
 */
public class FileUtil {
    private static final String FILE_NAME = "students.txt";

    /**
     * Ensures the file exists before reading/writing.
     */
    public static void checkFileExists() {
        try {
            File file = new File(FILE_NAME);
            if (!file.exists()) {
                file.createNewFile();
            }
        } catch (IOException e) {
            System.err.println("Error initializing file: " + e.getMessage());
        }
    }

    /**
     * Reads student records from students.txt using BufferedReader.
     */
    public static ArrayList<Student> readStudents() {
        ArrayList<Student> students = new ArrayList<>();
        checkFileExists();

        try (BufferedReader br = new BufferedReader(new FileReader(FILE_NAME))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] data = line.split(",");
                if (data.length == 5) {
                    int roll = Integer.parseInt(data[0]);
                    String name = data[1];
                    String email = data[2];
                    String course = data[3];
                    double marks = Double.parseDouble(data[4]);
                    students.add(new Student(roll, name, email, course, marks));
                }
            }
        } catch (IOException | NumberFormatException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
        return students;
    }

    /**
     * Writes student records to students.txt using BufferedWriter.
     */
    public static void saveStudents(List<Student> students) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(FILE_NAME))) {
            for (Student s : students) {
                bw.write(s.toCSV());
                bw.newLine();
            }
            System.out.println("Records saved successfully.");
        } catch (IOException e) {
            System.err.println("Error saving to file: " + e.getMessage());
        }
    }

    /**
     * Demonstrates usage of File Class Attributes.
     */
    public static void displayFileAttributes() {
        File file = new File(FILE_NAME);
        if (file.exists()) {
            System.out.println("\n--- File Attributes (File Class) ---");
            System.out.println("Path: " + file.getAbsolutePath());
            System.out.println("Size: " + file.length() + " bytes");
            System.out.println("Can Read: " + file.canRead());
            System.out.println("Can Write: " + file.canWrite());
        }
    }

    /**
     * Demonstrates reading records randomly using RandomAccessFile.
     */
    public static void readUsingRandomAccess() {
        System.out.println("\n--- Reading using RandomAccessFile ---");
        try (RandomAccessFile raf = new RandomAccessFile(FILE_NAME, "r")) {
            if (raf.length() > 0) {
                raf.seek(0); // Move pointer to start
                String firstLine = raf.readLine();
                System.out.println("First Record (Raw): " + firstLine);
            } else {
                System.out.println("File is empty.");
            }
        } catch (IOException e) {
            System.err.println("Random Access Error: " + e.getMessage());
        }
    }
}