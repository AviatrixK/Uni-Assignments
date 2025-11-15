# Student Performance Tracker System – Implementation Report  
**Course:**  Bsc. (H) Cybersecurity
**Subject:** Data Structures and Algorithms 
**Student Name:** [Kiruthika]  
**Student ID:** [2401830004]  

## Executive Summary
This report presents the implementation of a **Student Performance Tracker System** in C++. The system efficiently manages academic records using advanced data structures and algorithms including searching, sorting, and hashing techniques. The implementation demonstrates practical applications of theoretical concepts in real-world academic performance tracking scenarios.

## 1. Description of the Student Record ADT

### 1.1 Structure Design
```cpp
class Student {
    int studentID;
    string studentName;
    float grade;
    string courseDetails;
};
```

### 1.2 Key Methods
- Constructor
- display()
- Getter/Setter methods

### 1.3 Design Rationale
- Data Integrity  
- Reusability  
- Maintainability  

## 2. Strategy for Searching, Sorting, and Hashing

### 2.1 Searching Algorithms
#### Sequential Search
- O(n)

#### Binary Search
- O(log n)

### 2.2 Sorting Algorithms
- Bubble Sort  
- Insertion Sort  
- Merge Sort  
- Quick Sort  
- Heap Sort  

### 2.3 Hashing
- 10 buckets  
- Hash: `key % TABLE_SIZE`  
- Chaining for collisions  

## 3. Time Complexity Comparison

### 3.1 Using chrono library
```cpp
auto start = chrono::high_resolution_clock::now();
auto end = chrono::high_resolution_clock::now();
```

### 3.2 Table
| Algorithm | Best | Avg | Worst | Space |
|----------|------|------|--------|-------|
| Bubble | O(n) | O(n²) | O(n²) | O(1) |
| Insertion | O(n) | O(n²) | O(n²) | O(1) |
| Merge | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Quick | O(n log n) | O(n log n) | O(n²) | O(log n) |
| Heap | O(n log n) | O(n log n) | O(n log n) | O(1) |

## 4. System Efficiency

### Search Performance
- Hash: O(1)  
- Binary: O(log n)  
- Sequential: O(n)

### Sorting Performance
Sample:
```
Bubble: 12–15 μs  
Insertion: 10–12 μs  
Merge: 18–22 μs  
Quick: 15–18 μs  
Heap: 20–25 μs
```

## 5. Testing Results

### Adding a Student
```
Input: ID 109  
Output: Inserted, Hash index 9
```

### Sorting Output
```
Rank 1: Raman – 95.2  
Rank 2: Jagjeet – 92.3  
...
```

## 6. Challenges and Solutions
| Challenge | Solution |
|----------|----------|
| Collisions | Chaining |
| Sorting order | Auto-sort |
| Timing accuracy | High-res clock |
| Input validation | Error checks |

## 7. Conclusion
- Efficient data management  
- Flexible searching  
- Comprehensive sorting  
- Scalable architecture  

### Future Enhancements
- File I/O  
- Advanced hashing  
- GUI  
- More attributes  
- Statistical analysis  
                            

