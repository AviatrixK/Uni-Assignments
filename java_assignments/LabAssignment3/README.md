# **Student Management System (Java)**

A simple console-based Student Management System built using **Core Java**, demonstrating:

- OOP (classes, objects, interfaces)
- Custom exceptions  
- Multithreading (loading animation & search simulation)
- HashMap-based in-memory database  
- Input validation  
- Modular design  

---

## **Features**
- **Add New Student**
  - Auto grade calculation  
  - Input validation (name, email, marks, course)
  - Loading animation via threads

- **Display Student Information**
  - Search with simulated loading
  - Shows roll number, name, email, marks, and grade

- **Custom Exceptions**
  - `InvalidInputException`
  - `StudentNotFoundException`

- **Threading**
  - Loading animation using `Runnable` and `Thread`

---

## **Project Structure**
```
java_assignments/
└── LabAssignment3/
    └── StudentManagementSystem.java
```

---

## **How to Run**
1. Navigate to the project directory:
   ```bash
   cd java_assignments/LabAssignment3
   ```
2. Compile:
   ```bash
   javac StudentManagementSystem.java
   ```
3. Run:
   ```bash
   java StudentManagementSystem
   ```

---

## **Usage**
Menu options:
```
1. Add New Student
2. Display Student Information
3. Exit
```

---

## **Technologies Used**
- **Java** (Core Java, OOP)
- **Collections Framework (HashMap)**
- **Exception Handling**
- **Multithreading**

---

## **Notes**
- Data is stored in a HashMap — no external database required.
- All fields are validated before insertion.
- Marks must be between **0 and 100**.
