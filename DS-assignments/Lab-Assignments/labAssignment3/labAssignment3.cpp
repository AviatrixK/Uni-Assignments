#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <limits>
using namespace std;

class Student {
public:
    int studentID;
    string studentName;
    float grade;
    string courseDetails;
    
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
    
    void display() {
        cout << "ID: " << studentID 
             << " | Name: " << studentName 
             << " | Grade: " << grade 
             << " | Course: " << courseDetails << endl;
    }
};

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
    
    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }
    
public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }
    
    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
    
    void insertStudent(Student student) {
        int index = hashFunction(student.studentID);
        HashNode* newNode = new HashNode(student);
        
        if (table[index] == nullptr) {
            table[index] = newNode;
        }
        else {
            HashNode* temp = table[index];
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    
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

class StudentPerformanceTracker {
private:
    vector<Student> students;
    HashTable hashTable;
    
public:
    void addStudentRecord() {
        int id;
        string name, course;
        float grade;
        
        cout << "\n--- Add New Student ---" << endl;
        
        while (true) {
            cout << "Enter Student ID: ";
            if (cin >> id) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            } else {
                cout << "Invalid input for Student ID. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        cout << "Enter Student Name: ";
        getline(cin, name);
        
        while (true) {
            cout << "Enter Grade: ";
            if (cin >> grade) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            } else {
                cout << "Invalid input for Grade. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        cout << "Enter Course Details: ";
        getline(cin, course);
        
        Student newStudent(id, name, grade, course);
        students.push_back(newStudent);
        hashTable.insertStudent(newStudent);
        cout << "Student inserted successfully!" << endl;
    }
    
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
    
    void binarySearchByID(int id) {
        cout << "\n--- Binary Search Results ---" << endl;
        
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
        
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);
        
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
        return arr;
    }
    
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
    
    void compareSortingComplexity() {
        if (students.empty()) {
            cout << "No students to compare sorting algorithms!" << endl;
            return;
        }
        
        cout << "\n--- Sorting Algorithm Performance Comparison ---" << endl;
        cout << "Number of students: " << students.size() << endl;
        cout << setw(20) << "Algorithm" << setw(20) << "Time (microseconds)" << endl;
        cout << string(40, '-') << endl;
        
        vector<Student> testArray = students;
        
        auto start = chrono::high_resolution_clock::now();
        bubbleSort(testArray);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << setw(20) << "Bubble Sort" << setw(20) << duration.count() << endl;
        
        start = chrono::high_resolution_clock::now();
        insertionSort(testArray);
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << setw(20) << "Insertion Sort" << setw(20) << duration.count() << endl;
        
        start = chrono::high_resolution_clock::now();
        mergeSort(testArray);
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << setw(20) << "Merge Sort" << setw(20) << duration.count() << endl;
        
        start = chrono::high_resolution_clock::now();
        quickSort(testArray);
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << setw(20) << "Quick Sort" << setw(20) << duration.count() << endl;
        
        start = chrono::high_resolution_clock::now();
        heapSort(testArray);
        end = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << setw(20) << "Heap Sort" << setw(20) << duration.count() << endl;
        
        cout << "\nTime Complexity Analysis:" << endl;
        cout << "Bubble Sort: O(n\u00b2)" << endl;
        cout << "Insertion Sort: O(n\u00b2)" << endl;
        cout << "Merge Sort: O(n log n)" << endl;
        cout << "Quick Sort: O(n log n) average, O(n\u00b2) worst" << endl;
        cout << "Heap Sort: O(n log n)" << endl;
    }
    
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
    
    void displayHashTable() {
        hashTable.display();
    }
    
    void searchMenu() {
        int choice;
        
        while (true) {
            cout << "\n--- Search Menu ---" << endl;
            cout << "1. Sequential Search by Name" << endl;
            cout << "2. Binary Search by ID" << endl;
            cout << "3. Hash Table Search by ID" << endl;
            cout << "Enter choice: ";
            
            if (cin >> choice) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            } else {
                cout << "Invalid choice. Please enter a number from the menu." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        
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
                while (true) {
                    cout << "Enter student ID: ";
                    if (cin >> id) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    } else {
                        cout << "Invalid input. Please enter a number." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                binarySearchByID(id);
                break;
            }
            case 3: {
                int id;
                while (true) {
                    cout << "Enter student ID: ";
                    if (cin >> id) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    } else {
                        cout << "Invalid input. Please enter a number." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
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
    
    void addSampleData() {
        students.push_back(Student(101, "Alice Johnson", 85.5, "Computer Science"));
        students.push_back(Student(102, "Bob Smith", 92.3, "Mathematics"));
        students.push_back(Student(103, "Charlie Brown", 78.9, "Physics"));
        students.push_back(Student(104, "Diana Prince", 88.7, "Chemistry"));
        students.push_back(Student(105, "Eve Adams", 95.2, "Biology"));
        students.push_back(Student(106, "Frank Miller", 82.4, "Computer Science"));
        students.push_back(Student(107, "Grace Lee", 91.6, "Mathematics"));
        students.push_back(Student(108, "Henry Wilson", 76.8, "Physics"));
        
        for (int i = 0; i < students.size(); i++) {
            hashTable.insertStudent(students[i]);
        }
        
        cout << "Sample data added successfully!" << endl;
    }
};

int main() {
    StudentPerformanceTracker tracker;
    int choice;
    
    cout << "========================================" << endl;
    cout << "     STUDENT PERFORMANCE TRACKER SYSTEM  " << endl;
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
        
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number from the menu." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
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
                
                if (!(cin >> sortChoice)) {
                    cout << "Invalid input for sort choice. Please enter a number." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                
            case 7:
                tracker.displayHashTable();
                break;
            
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