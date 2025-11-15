#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <list>
using namespace std;

class Student {
public:
    int studentID;      
    string studentName;
    float marks;
    string courseDetails;
    
    // Default constructor
    Student() {
        studentID = 0;
        studentName = "";
        marks = 0.0;
        courseDetails = "";
    }
    
    // Parameterized constructor
    Student(int id, string name, float m, string course) {
        studentID = id;
        studentName = name;
        marks = m;
        courseDetails = course;
    }
    
    // Display student details
    void display() {
        cout << "Roll No: " << studentID 
             << " | Name: " << studentName 
             << " | Marks: " << marks 
             << " | Course: " << courseDetails << endl;
    }
};

// ==================== HASH TABLE IMPLEMENTATION ====================
class HashNode {
public:
    Student data;
    HashNode* next;
    
    HashNode(Student s) {
        data = s;
        next = nullptr;
    }
};

class HashTable {
private:
    static const int TABLE_SIZE = 10;
    HashNode* table[TABLE_SIZE];
    
    // Hash function
    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }
    
public:
    // Constructor
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }
    
    // Insert student into hash table
    void insertStudent(Student student) {
        int index = hashFunction(student.studentID);
        HashNode* newNode = new HashNode(student);
        
        // If no collision
        if (table[index] == nullptr) {
            table[index] = newNode;
        }
        // Handle collision using chaining
        else {
            HashNode* temp = table[index];
            while (temp->next != nullptr) {
                // Check if student already exists
                if (temp->data.studentID == student.studentID) {
                    cout << "Student with this ID already exists!" << endl;
                    delete newNode;
                    return;
                }
                temp = temp->next;
            }
            // Check last node
            if (temp->data.studentID == student.studentID) {
                cout << "Student with this ID already exists!" << endl;
                delete newNode;
                return;
            }
            temp->next = newNode;
            cout << "Collision handled using chaining at index " << index << endl;
        }
        cout << "Student inserted successfully at hash index " << index << "!" << endl;
    }
    
    // Search student by ID in hash table
    Student* searchByID(int id) {
        int index = hashFunction(id);
        HashNode* temp = table[index];
        
        while (temp != nullptr) {
            if (temp->data.studentID == id) {
                return &(temp->data);
            }
            temp = temp->next;
        }
        return nullptr;
    }
    
    // Get all students from hash table
    vector<Student> getAllStudents() {
        vector<Student> students;
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* temp = table[i];
            while (temp != nullptr) {
                students.push_back(temp->data);
                temp = temp->next;
            }
        }
        return students;
    }
    
    // Display hash table
    void display() {
        cout << "\n--- Hash Table Contents ---" << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Bucket " << i << ": ";
            HashNode* temp = table[i];
            if (temp == nullptr) {
                cout << "Empty";
            }
            while (temp != nullptr) {
                cout << "[" << temp->data.studentID << ", " 
                     << temp->data.studentName << "] ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

class SearchAlgorithms {
public:
    // Sequential search for roll number
    static int sequentialSearch(vector<Student>& students, int rollNumber) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].studentID == rollNumber) {
                return i;
            }
        }
        return -1;
    }
    
    // Binary search for roll number (requires sorted array)
    static int binarySearch(vector<Student>& students, int rollNumber) {
        int left = 0;
        int right = students.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (students[mid].studentID == rollNumber) {
                return mid;
            }
            
            if (students[mid].studentID < rollNumber) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }
};

class SortingAlgorithms {
public:
    // Heap Sort for marks
    static void heapify(vector<Student>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[left].marks > arr[largest].marks)
            largest = left;
        
        if (right < n && arr[right].marks > arr[largest].marks)
            largest = right;
        
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
    
    static void heapSort(vector<Student>& arr) {
        int n = arr.size();
        
        // Build heap
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);
        
        // Extract elements from heap
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
    
    // Quick Sort for marks
    static int partition(vector<Student>& arr, int low, int high) {
        float pivot = arr[high].marks;
        int i = (low - 1);
        
        for (int j = low; j <= high - 1; j++) {
            if (arr[j].marks <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }
    
    static void quickSortHelper(vector<Student>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSortHelper(arr, low, pi - 1);
            quickSortHelper(arr, pi + 1, high);
        }
    }
    
    static void quickSort(vector<Student>& arr) {
        if (!arr.empty()) {
            quickSortHelper(arr, 0, arr.size() - 1);
        }
    }
    
    // Radix Sort for roll numbers
    static int getMax(vector<Student>& arr) {
        int mx = arr[0].studentID;
        for (int i = 1; i < arr.size(); i++)
            if (arr[i].studentID > mx)
                mx = arr[i].studentID;
        return mx;
    }
    
    static void countSort(vector<Student>& arr, int exp) {
        int n = arr.size();
        vector<Student> output(n);
        int count[10] = {0};
        
        // Store count of occurrences
        for (int i = 0; i < n; i++)
            count[(arr[i].studentID / exp) % 10]++;
        
        // Change count[i] to actual position
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];
        
        // Build the output array
        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i].studentID / exp) % 10] - 1] = arr[i];
            count[(arr[i].studentID / exp) % 10]--;
        }
        
        // Copy output array to arr
        for (int i = 0; i < n; i++)
            arr[i] = output[i];
    }
    
    static void radixSort(vector<Student>& arr) {
        if (arr.empty()) return;
        
        int m = getMax(arr);
        
        // Do counting sort for every digit
        for (int exp = 1; m / exp > 0; exp *= 10)
            countSort(arr, exp);
    }
    
    // Bucket Sort for roll numbers
    static void bucketSort(vector<Student>& arr) {
        if (arr.empty()) return;
        
        int n = arr.size();
        
        // Find maximum roll number
        int maxRoll = arr[0].studentID;
        int minRoll = arr[0].studentID;
        for (int i = 1; i < n; i++) {
            maxRoll = max(maxRoll, arr[i].studentID);
            minRoll = min(minRoll, arr[i].studentID);
        }
        
        // Create n buckets
        vector<vector<Student>> buckets(n);
        
        // Put array elements in buckets
        for (int i = 0; i < n; i++) {
            int bucketIndex = (n - 1) * (arr[i].studentID - minRoll) / (maxRoll - minRoll + 1);
            buckets[bucketIndex].push_back(arr[i]);
        }
        
        // Sort individual buckets
        for (int i = 0; i < n; i++) {
            sort(buckets[i].begin(), buckets[i].end(), 
                 [](Student a, Student b) { return a.studentID < b.studentID; });
        }
        
        // Concatenate all buckets
        int index = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < buckets[i].size(); j++) {
                arr[index++] = buckets[i][j];
            }
        }
    }
};

class StudentResultManagementSystem {
private:
    HashTable hashTable;
    vector<Student> students;
    
    // Helper function to measure sorting time
    double measureSortingTime(void (*sortFunc)(vector<Student>&), vector<Student> data) {
        auto start = chrono::high_resolution_clock::now();
        sortFunc(data);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        return duration.count();
    }
    
public:
    // Add a new student record
    void addStudentRecord() {
        int id;
        string name, course;
        float marks;
        
        cout << "\n--- Add New Student Record ---" << endl;
        cout << "Enter Roll Number: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);
        cout << "Enter Marks: ";
        cin >> marks;
        cin.ignore();
        cout << "Enter Course Details: ";
        getline(cin, course);
        
        Student newStudent(id, name, marks, course);
        students.push_back(newStudent);
        hashTable.insertStudent(newStudent);
    }
    
    // Search by roll number
    void searchByRollNumber() {
        int rollNo;
        int choice;
        
        cout << "\n--- Search by Roll Number ---" << endl;
        cout << "1. Sequential Search" << endl;
        cout << "2. Binary Search (requires sorted list)" << endl;
        cout << "3. Hash Table Search" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        cout << "Enter Roll Number to search: ";
        cin >> rollNo;
        
        auto start = chrono::high_resolution_clock::now();
        
        switch (choice) {
            case 1: {
                // Sequential search
                int index = SearchAlgorithms::sequentialSearch(students, rollNo);
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                
                if (index != -1) {
                    cout << "\n--- Student Found (Sequential Search) ---" << endl;
                    students[index].display();
                    cout << "Search time: " << duration.count() << " microseconds" << endl;
                } else {
                    cout << "Student not found!" << endl;
                }
                break;
            }
            
            case 2: {
                // Binary search (sort first by roll number)
                vector<Student> sortedStudents = students;
                SortingAlgorithms::radixSort(sortedStudents);
                
                int index = SearchAlgorithms::binarySearch(sortedStudents, rollNo);
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                
                if (index != -1) {
                    cout << "\n--- Student Found (Binary Search) ---" << endl;
                    sortedStudents[index].display();
                    cout << "Search time: " << duration.count() << " microseconds" << endl;
                } else {
                    cout << "Student not found!" << endl;
                }
                break;
            }
            
            case 3: {
                // Hash table search
                Student* result = hashTable.searchByID(rollNo);
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                
                if (result != nullptr) {
                    cout << "\n--- Student Found (Hash Table) ---" << endl;
                    result->display();
                    cout << "Search time: " << duration.count() << " microseconds" << endl;
                } else {
                    cout << "Student not found!" << endl;
                }
                break;
            }
            
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    
    // Sort by marks
    void sortByMarks() {
        if (students.empty()) {
            cout << "No students to sort!" << endl;
            return;
        }
        
        int choice;
        cout << "\n--- Sort by Marks ---" << endl;
        cout << "1. Heap Sort" << endl;
        cout << "2. Quick Sort" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        vector<Student> sortedStudents = students;
        auto start = chrono::high_resolution_clock::now();
        
        switch (choice) {
            case 1:
                SortingAlgorithms::heapSort(sortedStudents);
                cout << "\n--- Students Sorted by Marks (Heap Sort) ---" << endl;
                break;
                
            case 2:
                SortingAlgorithms::quickSort(sortedStudents);
                cout << "\n--- Students Sorted by Marks (Quick Sort) ---" << endl;
                break;
                
            default:
                cout << "Invalid choice!" << endl;
                return;
        }
        
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        
        // Display sorted students
        for (int i = 0; i < sortedStudents.size(); i++) {
            cout << "Rank " << i + 1 << ": ";
            sortedStudents[i].display();
        }
        
        cout << "\nSorting time: " << duration.count() << " microseconds" << endl;
    }
    
    // Sort by roll number
    void sortByRollNumber() {
        if (students.empty()) {
            cout << "No students to sort!" << endl;
            return;
        }
        
        int choice;
        cout << "\n--- Sort by Roll Number ---" << endl;
        cout << "1. Radix Sort" << endl;
        cout << "2. Bucket Sort" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        vector<Student> sortedStudents = students;
        auto start = chrono::high_resolution_clock::now();
        
        switch (choice) {
            case 1:
                SortingAlgorithms::radixSort(sortedStudents);
                cout << "\n--- Students Sorted by Roll Number (Radix Sort) ---" << endl;
                break;
                
            case 2:
                SortingAlgorithms::bucketSort(sortedStudents);
                cout << "\n--- Students Sorted by Roll Number (Bucket Sort) ---" << endl;
                break;
                
            default:
                cout << "Invalid choice!" << endl;
                return;
        }
        
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        
        // Display sorted students
        for (int i = 0; i < sortedStudents.size(); i++) {
            sortedStudents[i].display();
        }
        
        cout << "\nSorting time: " << duration.count() << " microseconds" << endl;
    }
    
    // Compare sorting performance
    void compareSortingPerformance() {
        cout << "\n--- Sorting Algorithm Performance Comparison ---" << endl;
        
        // Create datasets of different sizes
        vector<int> sizes = {10, 50, 100, 500};
        
        cout << setw(15) << "Algorithm" 
             << setw(15) << "Data Type"
             << setw(15) << "10 items"
             << setw(15) << "50 items"
             << setw(15) << "100 items"
             << setw(15) << "500 items" << endl;
        cout << string(90, '-') << endl;
        
        for (int size : sizes) {
            // Generate random data
            vector<Student> testData;
            for (int i = 0; i < size; i++) {
                testData.push_back(Student(
                    1000 + rand() % 9000,  // Random roll number
                    "Student" + to_string(i),
                    rand() % 100,  // Random marks
                    "Course" + to_string(i % 5)
                ));
            }
            
            // Test each sorting algorithm
            if (size == 10) {  // Print header only once
                // Heap Sort
                cout << setw(15) << "Heap Sort" << setw(15) << "Marks";
                for (int s : sizes) {
                    vector<Student> tempData = testData;
                    if (s > testData.size()) {
                        // Generate more data if needed
                        tempData.clear();
                        for (int i = 0; i < s; i++) {
                            tempData.push_back(Student(
                                1000 + rand() % 9000,
                                "Student" + to_string(i),
                                rand() % 100,
                                "Course" + to_string(i % 5)
                            ));
                        }
                    }
                    double time = measureSortingTime(SortingAlgorithms::heapSort, tempData);
                    cout << setw(15) << time << "μs";
                }
                cout << endl;
                
                // Quick Sort
                cout << setw(15) << "Quick Sort" << setw(15) << "Marks";
                for (int s : sizes) {
                    vector<Student> tempData = testData;
                    if (s > testData.size()) {
                        tempData.clear();
                        for (int i = 0; i < s; i++) {
                            tempData.push_back(Student(
                                1000 + rand() % 9000,
                                "Student" + to_string(i),
                                rand() % 100,
                                "Course" + to_string(i % 5)
                            ));
                        }
                    }
                    double time = measureSortingTime(SortingAlgorithms::quickSort, tempData);
                    cout << setw(15) << time << "μs";
                }
                cout << endl;
                
                // Radix Sort
                cout << setw(15) << "Radix Sort" << setw(15) << "Roll No";
                for (int s : sizes) {
                    vector<Student> tempData = testData;
                    if (s > testData.size()) {
                        tempData.clear();
                        for (int i = 0; i < s; i++) {
                            tempData.push_back(Student(
                                1000 + rand() % 9000,
                                "Student" + to_string(i),
                                rand() % 100,
                                "Course" + to_string(i % 5)
                            ));
                        }
                    }
                    double time = measureSortingTime(SortingAlgorithms::radixSort, tempData);
                    cout << setw(15) << time << "μs";
                }
                cout << endl;
                
                // Bucket Sort
                cout << setw(15) << "Bucket Sort" << setw(15) << "Roll No";
                for (int s : sizes) {
                    vector<Student> tempData = testData;
                    if (s > testData.size()) {
                        tempData.clear();
                        for (int i = 0; i < s; i++) {
                            tempData.push_back(Student(
                                1000 + rand() % 9000,
                                "Student" + to_string(i),
                                rand() % 100,
                                "Course" + to_string(i % 5)
                            ));
                        }
                    }
                    double time = measureSortingTime(SortingAlgorithms::bucketSort, tempData);
                    cout << setw(15) << time << "μs";
                }
                cout << endl;
                break;  // Only print once
            }
        }
        
        cout << "\nTime Complexity Analysis:" << endl;
        cout << "Heap Sort:    O(n log n) - All cases" << endl;
        cout << "Quick Sort:   O(n log n) average, O(n²) worst case" << endl;
        cout << "Radix Sort:   O(d × n) where d = number of digits" << endl;
        cout << "Bucket Sort:  O(n + k) average case" << endl;
    }
    
    // Display all students
    void displayAllStudents() {
        if (students.empty()) {
            cout << "No students in the system!" << endl;
            return;
        }
        
        cout << "\n--- All Student Records ---" << endl;
        for (int i = 0; i < students.size(); i++) {
            students[i].display();
        }
    }
    
    // Display hash table
    void displayHashTable() {
        hashTable.display();
    }
    
    // Load sample data for testing
    void loadSampleData() {
        // Sample students
        students.push_back(Student(1001, "Alice Johnson", 85.5, "Computer Science"));
        students.push_back(Student(1015, "Bob Smith", 92.3, "Mathematics"));
        students.push_back(Student(1003, "Charlie Brown", 78.9, "Physics"));
        students.push_back(Student(1024, "Diana Prince", 88.7, "Chemistry"));
        students.push_back(Student(1005, "Eve Adams", 95.2, "Biology"));
        students.push_back(Student(1012, "Frank Miller", 82.4, "Computer Science"));
        students.push_back(Student(1007, "Grace Lee", 91.6, "Mathematics"));
        students.push_back(Student(1018, "Henry Wilson", 76.8, "Physics"));
        students.push_back(Student(1009, "Ivy Chen", 89.3, "Chemistry"));
        students.push_back(Student(1020, "Jack Davis", 84.1, "Biology"));
        
        // Add all to hash table
        for (int i = 0; i < students.size(); i++) {
            hashTable.insertStudent(students[i]);
        }
        
        cout << "Sample data loaded successfully!" << endl;
        cout << "10 students added to the system." << endl;
    }
    
    // Generate large dataset for performance testing
    void generateLargeDataset() {
        int n;
        cout << "\n--- Generate Large Dataset ---" << endl;
        cout << "Enter number of students to generate: ";
        cin >> n;
        
        for (int i = 0; i < n; i++) {
            Student s(
                1000 + rand() % 9000,  // Random roll number between 1000-9999
                "Student" + to_string(i),
                50 + rand() % 51,  // Random marks between 50-100
                "Course" + to_string(rand() % 10)
            );
            students.push_back(s);
            hashTable.insertStudent(s);
        }
        
        cout << n << " students generated successfully!" << endl;
    }
};

int main() {
    StudentResultManagementSystem system;
    int choice;
    
    cout << "================================================" << endl;
    cout << "       STUDENT RESULT MANAGEMENT SYSTEM        " << endl;
    cout << "================================================" << endl;
    
    while (true) {
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Add Student Record" << endl;
        cout << "2. Search by Roll Number" << endl;
        cout << "3. Sort by Marks" << endl;
        cout << "4. Sort by Roll Number" << endl;
        cout << "5. Compare Sorting Performance" << endl;
        cout << "6. Display All Students" << endl;
        cout << "7. Display Hash Table" << endl;
        cout << "8. Load Sample Data" << endl;
        cout << "9. Generate Large Dataset" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                system.addStudentRecord();
                break;
                
            case 2:
                system.searchByRollNumber();
                break;
                
            case 3:
                system.sortByMarks();
                break;
                
            case 4:
                system.sortByRollNumber();
                break;
                
            case 5:
                system.compareSortingPerformance();
                break;
                
            case 6:
                system.displayAllStudents();
                break;
                
            case 7:
                system.displayHashTable();
                break;
                
            case 8:
                system.loadSampleData();
                break;
                
            case 9:
                system.generateLargeDataset();
                break;
                
            case 10:
                cout << "\nThank you for using Student Result Management System!" << endl;
                return 0;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}