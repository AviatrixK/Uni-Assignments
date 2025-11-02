# Lab Assignment 2 – Customer Support Ticket System

## Problem Statement
The goal of this lab assignment was to **design and implement a Customer Support Ticket System** using the concepts of **Linked Lists, Stacks, Queues, and Polynomial Linked Lists**.  
The system should allow dynamic addition of customer tickets, support undo operations, handle urgent tickets using priority, and process tickets in a round-robin fashion.

---

## Implementation Strategy

### 1. Ticket ADT
Each ticket stores the following information:
- `TicketID` – unique identifier for the ticket  
- `CustomerName` – name of the customer  
- `IssueDescription` – details about the issue  
- `Priority` – urgency level (1 = high priority)

These were implemented using a **structure** with a constructor to simplify object creation.

---

### 2. Singly Linked List (TicketList)
Used to **store tickets dynamically**.  
- New tickets are added at the end.  
- Deletion and retrieval are performed by ticket ID.  
- The list grows and shrinks dynamically without needing predefined size.

---

### 3. Stack (UndoStack)
Implemented using a vector to simulate stack operations.  
- Used for **Undo** functionality.  
- Every time a ticket is added or deleted, the action is stored in the stack.  
- When `undoTicketOperation()` is called, the last action is reverted.

---

### 4. Priority Queue
A **min-heap priority queue** processes urgent tickets first.  
- Tickets with smaller priority values (1 = most urgent) are served first.  
- Implemented using STL `priority_queue` with a custom comparator.

---

### 5. Circular Queue
Used for **round-robin ticket processing**.  
- Tickets are stored in a circular buffer.  
- Each cycle, the next ticket is dequeued and processed.  
- Demonstrates fair ticket handling among agents.

---

### 6. Polynomial Linked List (Billing History)
Represents billing records as polynomials (e.g., `100x^2 + 50x^1`).  
- Each node stores coefficient and power.  
- Comparison checks whether two billing records are identical or not.

---

## Learning Outcome
- Gained practical experience in applying **Linked Lists**, **Stacks**, and **Queues**.  
- Understood how these structures can work together to solve **real-world problems** like ticket management systems.  
- Learned dynamic memory handling using pointers in C++.  
- Explored the real use of **priority queues** and **circular queues** in scheduling problems.

---

## ⏱️ Sample Output (Shortened)
```
Ticket added with ID 1
Ticket added with ID 2
Ticket added with ID 3

All tickets:
Current Tickets:
ID:1 | Alice | Priority:2
Issue: Cannot login
ID:2 | Bob | Priority:1
Issue: Payment failed
ID:3 | Charlie | Priority:3
Issue: Bug in UI

Undo last op:
Undo: removed ticket ID 3

After undo:
Current Tickets:
ID:1 | Alice | Priority:2
Issue: Cannot login
ID:2 | Bob | Priority:1
Issue: Payment failed

Process priority tickets:
Processing priority tickets:
Processing ID 2 (Priority 1) - Bob
Processing ID 1 (Priority 2) - Alice
Processing ID 3 (Priority 3) - Charlie

Remaining tickets:
No tickets in the system.

Round-robin demo:
Round-robin queue IDs: 1 2 3
Round-robin processing (2 cycles):
Cycle 1: Ticket ID 1 already processed or removed.
Cycle 2: Ticket ID 2 already processed or removed.

Compare billing histories:
Billing A: 100x^2 + 50x^1
Billing B: 100x^2 + 50x^1
Billing histories are identical.
```

---

## Conclusion
This lab strengthened my understanding of **linear data structures** and their integration in practical applications.  
I learned to build an end-to-end system using multiple data structures, demonstrating the relationship between **stack undo features**, **queue scheduling**, and **linked list storage**.


