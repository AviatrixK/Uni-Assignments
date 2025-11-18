# Project Report: Student Record Management System

## 1. Project Overview
The **Student Record Management System** is a Java-based console application designed to manage student data efficiently. The system ensures data persistence by saving records to a text file (`students.txt`). It utilizes the **Java Collections Framework** for in-memory data manipulation and **File Handling** APIs for storage.

## 2. Objectives
*   To implement persistent storage using `java.io` classes.
*   To utilize `ArrayList` and `HashMap` for efficient data management.
*   To demonstrate sorting using `Comparator` and traversal using `Iterator`.
*   To implement random file access using `RandomAccessFile`.

## 3. Technical Implementation

### A. Data Storage (File Handling)
The application uses a CSV (Comma Separated Values) format to store data in `students.txt`.
*   **Reading:** `BufferedReader` is used for efficient line-by-line reading.
*   **Writing:** `BufferedWriter` is used to save the updated list back to the file.
*   **Random Access:** `RandomAccessFile` is implemented to demonstrate byte-level reading from specific file pointers.
*   **Metadata:** The `File` class is used to retrieve file attributes like size and path.

### B. Data Structures (Collections)
*   **`ArrayList<Student>`**: Used to maintain the list of students. This allows for easy sorting and sequential iteration.
*   **`HashMap<Integer, Student>`**: Used to map Roll Numbers to Student objects. This ensures efficient **O(1)** lookup time and prevents duplicate Roll Numbers (Uniqueness check).

### C. Sorting and Traversal
*   **Sorting:** Implemented using the `Comparator` interface.
    *   *Sort by Marks:* Descending order.
    *   *Sort by Name:* Alphabetical order.
*   **Traversal:** `Iterator` is used to safely traverse collections and remove elements during iteration.

## 4. Class Hierarchy

| Class Name | Responsibility |
| :--- | :--- |
| **`Student`** | Defines the data model (Roll No, Name, Email, Course, Marks). Includes CSV formatting logic. |
| **`FileUtil`** | Handles all low-level file operations (`BufferedReader`, `RandomAccessFile`). |
| **`StudentManager`** | Contains business logic (Add, Delete, Search, Sort). Manages the Collections (`List` & `Map`). |
| **`StudentSystemApp`** | The entry point containing the `main` method and the menu-driven user interface. |

## 5. Key Features
1.  **Add Student:** Validates unique Roll No before adding.
2.  **View All:** Displays formatted records.
3.  **Search:** Finds students by Name.
4.  **Delete:** Removes students safely using Iterators.
5.  **Sort:** Ranks students based on Marks or Name.
6.  **Persistence:** Automatically loads data on start and saves on exit.

## 6. Learning Outcomes
Through the development of this project, the following concepts were mastered:
*   **Persistence:** Bridging the gap between volatile memory (RAM) and permanent storage.
*   **Data Integrity:** Ensuring data is formatted correctly for file storage.
*   **Algorithm Efficiency:** Using HashMaps for faster lookups compared to iterating through lists.
*   **Exception Handling:** Managing `IOException` and `NumberFormatException` to prevent crashes.

## 7. Conclusion
The project successfully meets all assignment requirements, providing a robust solution for managing student records with persistent storage and advanced collection manipulation.