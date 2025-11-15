# Campus Navigation and Utility Planner - Brief Project Report
**Course:** BSc. (H) Cybersecurity  
**Subject:** Data Structures and Algorithms  
**Student Name:** [Kiruthika]  
**Student ID:** [2401830004]  

---

## 1. Project Overview
A comprehensive C++ system for campus building management, optimal pathfinding, and utility planning using advanced data structures and algorithms.

### Core Components:
- Building storage via **BST & AVL Trees**
- Dual graph representations (**Adjacency Matrix & List**)
- Shortest path navigation (**Dijkstra's Algorithm**)
- Minimum spanning tree for cable layout (**Kruskal's Algorithm**)
- **Expression Tree** for energy bill calculations

---

## 2. Building Data ADT

```cpp
class Building {
    int buildingID;        // Unique identifier
    string buildingName;   // Building name
    string locationDetails;// Location info
};
```

Integrated across BST, AVL, and Graph implementations for unified data management.

---

## 3. Implementation Strategy

### Tree Structures
- **BST:** Standard binary search tree with O(h) operations  
- **AVL:** Self-balancing with rotation mechanisms; guarantees O(log n)  
- **Traversals:** Inorder (sorted), Preorder, Postorder  

### Graph Representations
- **Adjacency Matrix:**  
  - O(1) edge lookup  
  - O(V²) space complexity  

- **Adjacency List:**  
  - Space-efficient for sparse graphs  
  - O(V+E) space  

### Expression Tree
- Recursively evaluates arithmetic expressions  
- Used for energy bill calculation:  
  **(units * rate) + fixed_charge**

---

## 4. Key Algorithms

| Algorithm     | Purpose                         | Time Complexity |
|---------------|----------------------------------|----------------|
| Dijkstra's    | Shortest path between buildings  | O(V²)          |
| Kruskal's     | Minimum cable layout cost        | O(E log E)     |
| Union-Find    | Cycle detection in MST           | O(α(n))        |
| Tree Traversals | Display building listings      | O(n)           |

---

## 5. Performance Analysis

| Operation | BST       | AVL       | Graph (Matrix) | Graph (List) |
|----------|-----------|-----------|----------------|--------------|
| Insert   | O(h)      | O(log n)  | O(1)           | O(1)         |
| Search   | O(h)      | O(log n)  | O(V)           | O(V+E)       |
| Delete   | O(h)      | O(log n)  | O(1)           | O(1)         |
| Space    | O(n)      | O(n)      | O(V²)          | O(V+E)       |

Note:  
- h = height of tree  
- n = nodes  
- V = vertices  
- E = edges  

---

## 6. System Features

### Implemented Functionality:
- Building insertion in BST/AVL  
- Three tree traversal methods  
- Weighted undirected graph construction  
- Shortest pathfinding with reconstruction  
- MST generation with total cost computation  
- Expression tree evaluation for billing  
- Sample data loader for testing  

### Menu Options:
- Add/Search buildings  
- Display tree traversals  
- Construct campus graph  
- Find shortest paths  
- Plan utility layout  
- Calculate energy bills  

---

## 7. Testing Results

### Sample Graph (5 buildings, 6 paths):
- Engineering ↔ Library: 10 units  
- Library ↔ Student Center: 5 units  

**MST Total Cost:** 35 units  
**Shortest Path (Engineering → Admin):** 22 units via Library  

### Time Measurements:
- **BST Search:** O(log n) average  
- **AVL Balancing:** < 1ms for 100 nodes  
- **Dijkstra's:** < 1ms for 10 nodes  

---

## 8. Learning Outcomes
- Mastered AVL rotation mechanisms  
- Implemented matrix & list graph representations  
- Applied greedy algorithms (Kruskal’s)  
- Understood priority-based pathfinding (Dijkstra’s)  
- Practiced recursive tree operations  

---

## 9. Challenges & Solutions

| Challenge                | Solution                                      |
|--------------------------|-----------------------------------------------|
| AVL balancing logic      | Implemented LL, RR, LR, RL rotations         |
| Graph cycle detection    | Used Union-Find with path compression        |
| Path reconstruction      | Added parent array for Dijkstra’s            |
| Expression evaluation    | Used recursive postfix tree traversal        |

---

## 10. Conclusion

Developed a modular campus navigation system demonstrating proficiency in:

### **Data Structures:**
- Trees (BST, AVL)  
- Graphs  
- Stacks  

### **Algorithms:**
- Dijkstra’s shortest path  
- Kruskal’s MST  
- Tree traversals  

### **Complexity:**
Optimized primarily for **O(log n)** and **O(V²)** operations.

### **Future Enhancements:**
- A* search for heuristic pathfinding  
- Dynamic graph updates  
- Persistent storage (file I/O)  
- Web-based visualization interface  

### **Code Statistics:**
- **Lines of Code:** ~850  
- **Classes:** 10  
- **Algorithms:** 7  
- **Optimized for:** O(log n) & O(V²)

---
