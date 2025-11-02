# Assignment 2 – Hospital Patient Record Management System

---

## Problem Statement
Design and implement a Hospital Patient Record Management System using linear data structures.  
The system must support dynamic patient admissions, undo operations, emergency queue management (priority and round-robin), billing calculations using polynomial linked lists, and inventory calculations using postfix evaluation.

---

## Implementation Strategy

### 1. Patient Record ADT
Each patient record includes:
- `PatientID` – unique integer ID
- `PatientName` – string
- `AdmissionDate` – string in DD/MM/YYYY format
- `TreatmentDetails` – string describing services

This ADT is implemented as a `struct Patient` with a constructor for easy creation.

---

### 2. PatientList (Singly Linked List)
- Used to store admitted patient records dynamically.
- `insertPatient`: adds a new patient at the end.
- `deletePatient`: removes a patient by ID.
- `retrievePatient`: finds a patient node by ID.
- Advantages: dynamic size and easy insertion/deletion.
- Drawbacks: linear search for retrieval (O(n)).

---

### 3. UndoStack (Stack)
- Stack stores recent admission actions (add/delete) to support undo.
- Implemented using `vector<PatAction>` as an array-based stack.
- `undoAdmission` reverts the last operation by inspecting and applying the opposite action.

---

### 4. Emergency Queue
- Two approaches implemented:
  - **Priority Queue**: Processes most urgent patients first (smaller priority value).
  - **Circular Queue**: Supports round-robin attendance among waiting patients.
- Priority queue implemented using STL `priority_queue` with custom comparator.

---

### 5. Polynomial Linked List (Billing)
- Billing records are represented as polynomials where each term is a node with coefficient and power.
- Useful for representing costs that depend on different factors (e.g., duration^power).
- `equals` method compares two billing polynomials term-by-term.

---

### 6. Postfix Evaluation (Inventory)
- Postfix (Reverse Polish Notation) expressions are evaluated using a stack.
- Supports integer operands and operators `+ - * /`.
- Used here to model inventory computation expressions (e.g., combine supplies and multiply by units).

---

## Sample Output (Short)
```
Patient admitted with ID 1
Patient admitted with ID 2
Patient admitted with ID 3

All patients:
Current Admitted Patients:
ID:1 | Ravi Kumar | Date:01/09/2025
Treatment: Appendicitis - surgery
ID:2 | Meera Bose | Date:02/09/2025
Treatment: Fracture - cast
ID:3 | Ajay Das | Date:03/09/2025
Treatment: Fever & observation

Undo last admission:
Undo: removed patient ID 3

After undo:
Current Admitted Patients:
ID:1 | Ravi Kumar | Date:01/09/2025
Treatment: Appendicitis - surgery
ID:2 | Meera Bose | Date:02/09/2025
Treatment: Fracture - cast

Emergency priority processing:
Processing emergency patients by priority:
Handling ID 1 (Ravi Kumar) - Priority 1
Handling ID 2 (Meera Bose) - Priority 3
Handling ID 3 (Ajay Das) - Priority 4

Remaining patients:
No patients admitted.

Round-robin demo:
Round-robin patient IDs: 1 2 3 
Round-robin emergency processing (2 cycles):
Cycle 1: Patient ID 1 already processed or discharged.
Cycle 2: Patient ID 2 already processed or discharged.

Billing comparison:
Billing A: 200x^2 + 50x^1
Billing B: 200x^2 + 50x^1
Billing records match.

Inventory postfix expression: 10 5 + 2 *
Inventory calculation result: 30

```

---

## Learning Outcome
- Practiced implementing linked lists, stacks, and queues in C++.
- Understood how these structures can be combined to build practical systems.
- Learned polynomial linked lists for billing representation and postfix evaluation for simple computations.
- Improved skills with pointers, dynamic memory, and STL containers.

---

## Conclusion
The assignment demonstrates the use of linear data structures to manage hospital operations like patient admissions, emergency handling, billing, and inventory calculations. The system is a simplified model suitable for learning and can be extended for production requirements.

---


