#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
using namespace std;

// Student Record ADT
class Student {
public:
    int studentID;
    string studentName;
    float grade;
    string courseDetails;
    
    // Constructor
    Student() {
        studentID = 0;
        studentName = "";
        grade = 0.0;
        courseDetails = "";
    }
    
    Student(int id, string name, float g, string course) {
        studentID = id;
        studentName = name;
        grade = g;
        courseDetails = course;
    }
    
    // Display student details
    void display() {
        cout << "ID: " << studentID 
             << " | Name: " << studentName 
             << " | Grade: " << grade 
             << " | Course: " << courseDetails << endl;
    }
};

// Node for hash table collision resolution (chaining)
class HashNode {
public:
    Student data;
    HashNode* next;
    
    HashNode(Student s) {
        data = s;
        next = nullptr;
    }
};

// Hash Table Implementation
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
                temp = temp->next;
            }
            temp->next = newNode;
        }
        cout << "Student inserted successfully!" << endl;
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
                cout << "[ID: " << temp->data.studentID << ", " 
                     << temp->data.studentName << "] ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

// Student Performance Tracker System
class StudentPerformanceTracker {
private:
    vector<Student> students;
    HashTable hashTable;
    
public:
    // Add a new student record
    void addStudentRecord() {
        int id;
        string name, course;
        float grade;
        
        cout << "\n--- Add New Student ---" << endl;
        cout << "Enter Student ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);
        cout << "Enter Grade: ";
        cin >> grade;
        cin.ignore();
        cout << "Enter Course Details: ";
        getline(cin, course);
        
        Student newStudent(id, name, grade, course);
        students.push_back(newStudent);
        hashTable.insertStudent(newStudent);
    }
    
    // Sequential Search by Name
    void sequentialSearchByName(string name) {
        cout << "\n--- Sequential Search Results ---" << endl;
        bool found = false;
        
        for (int i = 0; i < students.size(); i++) {
            if (students[i].studentName == name) {
                students[i].display();
                found = true;
            }
        }
        
        if (!found) {
            cout << "Student not found!" << endl;
        }
    }
    
    // Binary Search by ID (requires sorted array)
    void binarySearchByID(int id) {
        cout << "\n--- Binary Search Results ---" << endl;
        
        // First, sort by ID
        vector<Student> sortedStudents = students;
        sort(sortedStudents.begin(), sortedStudents.end(), 
             [](Student a, Student b) { return a.studentID < b.studentID; });
        
        int left = 0;
        int right = sortedStudents.size() - 1;
        bool found = false;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (sortedStudents[mid].studentID == id) {
                sortedStudents[mid].display();
                found = true;
                break;
            }
            
            if (sortedStudents[mid].studentID < id) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        if (!found) {
            cout << "Student not found!" << endl;
        }
    }
    
    // Bubble Sort by Grades
    vector<Student> bubbleSort(vector<Student> arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j].grade > arr[j + 1].grade) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
        return arr;
    }
    
    // Insertion Sort by Grades
    vector<Student> insertionSort(vector<Student> arr) {
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            Student key = arr[i];
            int j = i - 1;
            
            while (j >= 0 && arr[j].grade > key.grade) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return arr;
    }
    
    // Merge Sort Helper Functions
    void merge(vector<Student>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        vector<Student> leftArr(n1), rightArr(n2);
        
        for (int i = 0; i < n1; i++)
            leftArr[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            rightArr[j] = arr[mid + 1 + j];
        
        int i = 0, j = 0, k = left;
        
        while (i < n1 && j < n2) {
            if (leftArr[i].grade <= rightArr[j].grade) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
    }
    
    void mergeSortHelper(vector<Student>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortHelper(arr, left, mid);
            mergeSortHelper(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    
    vector<Student> mergeSort(vector<Student> arr) {
        mergeSortHelper(arr, 0, arr.size() - 1);
        return arr;
    }
    
    // Quick Sort Helper Functions
    int partition(vector<Student>& arr, int low, int high) {
        float pivot = arr[high].grade;
        int i = (low - 1);
        
        for (int j = low; j <= high - 1; j++) {
            if (arr[j].grade < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }
    
    void quickSortHelper(vector<Student>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSortHelper(arr, low, pi - 1);
            quickSortHelper(arr, pi + 1, high);
        }
    }
    
    vector<Student> quickSort(vector<Student> arr) {
        quickSortHelper(arr, 0, arr.size() - 1);
        return arr;
    }
    
    // Heap Sort Helper Functions
    void heapify(vector<Student>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[left].grade > arr[largest].grade)
            largest = left;
        
        if (right < n && arr[right].grade > arr[largest].grade)
            largest = right;
        
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
    
    vector<Student> heapSort(vector<Student> arr) {
        int n = arr.size();
        
        // Build heap
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);
        
        // Extract elements from heap
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
        return arr;
    }
    
    // Sort by grades using selected algorithm
    void sortByGrades(int choice) {
        if (students.empty()) {
            cout << "No students to sort!" << endl;
            return;
        }
        
        vector<Student> sorted;
        
        switch (choice) {
            case 1:
                sorted = bubbleSort(students);
                cout << "\n--- Sorted by Bubble Sort ---" << endl;
                break;
            case 2:
                sorted = insertionSort(students);
                cout << "\n--- Sorted by Insertion Sort ---" << endl;
                break;
            case 3:
                sorted = mergeSort(students);
                cout << "\n--- Sorted by Merge Sort ---" << endl;
                break;
            case 4:
                sorted = quickSort(students);
                cout << "\n--- Sorted by Quick Sort ---" << endl;
                break;
            case 5:
                sorted = heapSort(students);
                cout << "\n--- Sorted by Heap Sort ---" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
                return;
        }
        
        for (int i = 0; i < sorted.size(); i++) {
            cout << "Rank " << i + 1 << ": ";
            sorted[i].display();
        }
    }
    
    // Compare sorting algorithms time complexity
    void compareSortingComplexity() {
        if (students.size() < 2) {
            cout << "Need at least 2 students to compare sorting algorithms!" << endl;
            return;
        }
        
        cout << "\n--- Sorting Algorithm Performance Comparison ---" << endl;
        cout << "Number of students: " << students.size() << endl;
        cout << setw(20) << "Algorithm" << setw(20) << "Time (microseconds)" << endl;
        cout << string(40, '-') << endl;
        
        vector<Student> testArray = students;
        
        // Bubble Sort
        auto start = chrono::high_resolution_clock::now();
        bubbleSort(testArray);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << setw(20) << "Bubble Sort" << setw(20) << duration.count() << endl;
        
        // Insertion Sort
        start = chrono::high_resolution_clock::now();
        insertionSort(testArray);
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << setw(20) << "Insertion Sort" << setw(20) << duration.count() << endl;
        
        // Merge Sort
        start = chrono::high_resolution_clock::now();
        mergeSort(testArray);
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << setw(20) << "Merge Sort" << setw(20) << duration.count() << endl;
        
        // Quick Sort
        start = chrono::high_resolution_clock::now();
        quickSort(testArray);
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << setw(20) << "Quick Sort" << setw(20) << duration.count() << endl;
        
        // Heap Sort
        start = chrono::high_resolution_clock::now();
        heapSort(testArray);
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << setw(20) << "Heap Sort" << setw(20) << duration.count() << endl;
        
        cout << "\nTime Complexity Analysis:" << endl;
        cout << "Bubble Sort:    O(n²)" << endl;
        cout << "Insertion Sort: O(n²)" << endl;
        cout << "Merge Sort:     O(n log n)" << endl;
        cout << "Quick Sort:     O(n log n) average, O(n²) worst" << endl;
        cout << "Heap Sort:      O(n log n)" << endl;
    }
    
    // Display all students
    void displayAllStudents() {
        if (students.empty()) {
            cout << "No students in the system!" << endl;
            return;
        }
        
        cout << "\n--- All Students ---" << endl;
        for (int i = 0; i < students.size(); i++) {
            students[i].display();
        }
    }
    
    // Search menu
    void searchMenu() {
        int choice;
        cout << "\n--- Search Menu ---" << endl;
        cout << "1. Sequential Search by Name" << endl;
        cout << "2. Binary Search by ID" << endl;
        cout << "3. Hash Table Search by ID" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                string name;
                cout << "Enter student name: ";
                getline(cin, name);
                sequentialSearchByName(name);
                break;
            }
            case 2: {
                int id;
                cout << "Enter student ID: ";
                cin >> id;
                binarySearchByID(id);
                break;
            }
            case 3: {
                int id;
                cout << "Enter student ID: ";
                cin >> id;
                Student* found = hashTable.searchByID(id);
                if (found != nullptr) {
                    cout << "\n--- Hash Table Search Results ---" << endl;
                    found->display();
                } else {
                    cout << "Student not found in hash table!" << endl;
                }
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    
    // Add sample data for testing
    void addSampleData() {
        students.push_back(Student(101, "Alice Johnson", 85.5, "Computer Science"));
        students.push_back(Student(102, "Bob Smith", 92.3, "Mathematics"));
        students.push_back(Student(103, "Charlie Brown", 78.9, "Physics"));
        students.push_back(Student(104, "Diana Prince", 88.7, "Chemistry"));
        students.push_back(Student(105, "Eve Adams", 95.2, "Biology"));
        students.push_back(Student(106, "Frank Miller", 82.4, "Computer Science"));
        students.push_back(Student(107, "Grace Lee", 91.6, "Mathematics"));
        students.push_back(Student(108, "Henry Wilson", 76.8, "Physics"));
        
        // Add all to hash table
        for (int i = 0; i < students.size(); i++) {
            hashTable.insertStudent(students[i]);
        }
        
        cout << "Sample data added successfully!" << endl;
    }
};

// Main function
int main() {
    StudentPerformanceTracker tracker;
    int choice;
    
    cout << "========================================" << endl;
    cout << "    STUDENT PERFORMANCE TRACKER SYSTEM  " << endl;
    cout << "========================================" << endl;
    
    while (true) {
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Add Student Record" << endl;
        cout << "2. Search Student" << endl;
        cout << "3. Sort Students by Grades" << endl;
        cout << "4. Rank Students by Performance (Heap Sort)" << endl;
        cout << "5. Compare Sorting Algorithms" << endl;
        cout << "6. Display All Students" << endl;
        cout << "7. Display Hash Table" << endl;
        cout << "8. Add Sample Data" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                tracker.addStudentRecord();
                break;
                
            case 2:
                tracker.searchMenu();
                break;
                
            case 3: {
                int sortChoice;
                cout << "\n--- Sorting Options ---" << endl;
                cout << "1. Bubble Sort" << endl;
                cout << "2. Insertion Sort" << endl;
                cout << "3. Merge Sort" << endl;
                cout << "4. Quick Sort" << endl;
                cout << "5. Heap Sort" << endl;
                cout << "Enter choice: ";
                cin >> sortChoice;
                tracker.sortByGrades(sortChoice);
                break;
            }
            
            case 4:
                cout << "\n--- Ranking Students by Performance (Heap Sort) ---" << endl;
                tracker.sortByGrades(5);
                break;
                
            case 5:
                tracker.compareSortingComplexity();
                break;
                
            case 6:
                tracker.displayAllStudents();
                break;
                
            case 7: {
                HashTable temp;
                temp.display();
                break;
            }
            
            case 8:
                tracker.addSampleData();
                break;
                
            case 9:
                cout << "\nThank you for using Student Performance Tracker!" << endl;
                return 0;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}