# Smart City Road Navigation System - Project Report

**Course:** BSc. (H) Computer Science / Cybersecurity  
**Subject:** Data Structures and Algorithms  
**Student Name:** [Kiruthika] 
**Student ID:*** [2401830004]  


---

## 1. Project Overview

A comprehensive C++ system for managing smart city road networks, computing optimal routes, and planning cost-effective infrastructure using advanced graph algorithms and tree structures.

### Core Features
- Dual graph representations (Adjacency Matrix & Adjacency List).
- Multiple shortest path algorithms (Dijkstra's & Floyd-Warshall).
- Hierarchical zone indexing using BST & AVL Trees.
- Infrastructure planning with Prim's & Kruskal's MST algorithms.
- Construction project prioritization using Topological Sort.

---

## 2. Road Network ADT

The system is built around a RoadNode ADT and a graph structure.

cpp
class RoadNode {
    int nodeID;          // Unique intersection ID
    string nodeName;     // Intersection/zone name
    string zoneDetails;  // Zone type (Residential/Commercial/Industrial)
};


### Graph Structure
- *Nodes:* Represent intersections or zones in the city.
- *Edges:* Represent roads connecting the nodes, with associated distances (weights).
- Supports both one-way (directed) and two-way (undirected) roads.

---

## 3. Implementation Strategy

### Graph Representations
The system supports two graph representations to suit different needs:

| Representation     | Space Complexity | Edge Lookup | Use Case                            |
|--------------------|------------------|-------------|-------------------------------------|
| *Adjacency Matrix* | O(V²)            | O(1)        | Dense graphs, Floyd-Warshall algorithm |
| *Adjacency List*   | O(V+E)           | O(degree)   | Sparse graphs, Dijkstra's algorithm   |

### Tree Structures for Zone Indexing
Hierarchical indexing of city zones is managed by tree structures for efficient lookups.

| Tree Type | Height     | Insert/Search | Advantage                 |
|-----------|------------|---------------|---------------------------|
| *BST*     | O(n) worst | O(h)          | Simple implementation     |
| *AVL*     | O(log n)   | O(log n)      | Guaranteed balance & performance |

---

## 4. Algorithm Implementation

### Shortest Path Algorithms

| Algorithm        | Type          | Time Complexity | Space  | Use Case                         |
|------------------|---------------|-----------------|--------|----------------------------------|
| *Dijkstra*       | Single-source | O(V²)           | O(V)   | Point-to-point navigation        |
| *Floyd-Warshall* | All-pairs     | O(V³)           | O(V²)  | Complete city distance matrix    |

### Minimum Spanning Tree (MST) Algorithms

| Algorithm    | Approach      | Time Complexity | Strategy                            |
|--------------|---------------|-----------------|-------------------------------------|
| *Prim's*     | Vertex-based  | O(V²)           | Grow a tree from a starting vertex  |
| *Kruskal's*  | Edge-based    | O(E log E)      | Sort edges, use Union-Find to avoid cycles |

### Additional Algorithms
- *Topological Sort:* O(V+E) - Used for construction scheduling and dependency resolution.
- *Tree Traversals (In-order, Pre-order, Post-order):* O(V) - For listing zones in various orders.

---

## 5. System Architecture

text
SmartCityNavigationSystem
├── RoadGraph
│   ├── Adjacency Matrix
│   ├── Adjacency List
│   ├── Dijkstra's Algorithm
│   ├── Floyd-Warshall Algorithm
│   ├── Prim's MST
│   ├── Kruskal's MST
│   └── Topological Sort
├── BinarySearchTree
│   └── Zone Indexing
└── AVLTree
    └── Balanced Zone Indexing


---

## 6. Performance Analysis

### Time Complexity Summary

| Operation         | Best Case    | Average Case | Worst Case   |
|-------------------|--------------|--------------|--------------|
| *Add Road*        | O(1)         | O(1)         | O(1)         |
| *Dijkstra's Path* | O(V²)        | O(V²)        | O(V²)        |
| *Floyd-Warshall*  | O(V³)        | O(V³)        | O(V³)        |
| *Zone Search (BST)* | O(1)         | O(log n)     | O(n)         |
| *Zone Search (AVL)* | O(log n)     | O(log n)     | O(log n)     |
| *MST Construction*  | O(E log E)   | O(E log E)   | O(E log E)   |

### Space Complexity

| Component          | Space Required | Description                              |
|--------------------|----------------|------------------------------------------|
| *Adjacency Matrix* | O(V²)          | Stores all possible edges (V × V matrix) |
| *Adjacency List*   | O(V+E)         | Stores only the actual edges present     |
| *BST/AVL Tree*     | O(V)           | One node per indexed zone                |
| *Algorithm Arrays* | O(V)           | Temporary arrays for distance, parent, etc. |

---

## 7. Sample Test Results

### Sample Network (6 Zones, 10 Roads)
- *Zones:* City Center, North District, Industrial Park, University Area, Shopping Mall, Airport.
- *Zone Types:* Commercial, Residential, Industrial, Educational, Transportation.

### Shortest Path Results
text
Dijkstra's Algorithm:
Source: City Center
Destination: Airport
Shortest Distance: 18 km
Path: City Center → Shopping Mall → Airport


### MST Results (for Infrastructure Planning)
text
Kruskal's Algorithm:
Selected Roads for minimum cost network:
- City Center ↔ Shopping Mall (3 km)
- North District ↔ University (4 km)
- City Center ↔ North District (5 km)
- City Center ↔ Industrial Park (8 km)
- Industrial Park ↔ Airport (10 km)
Total Cost to connect all zones: 30 km


### Topological Sort (for Construction Priority)
text
Construction Order (based on dependencies):
1. City Center
2. North District
3. Shopping Mall
4. University Area
5. Industrial Park
6. Airport


---

## 8. Key Features & Functionality

### Implemented Features
✅ Dual graph representations (Matrix & List)  
✅ Two shortest path algorithms (Dijkstra, Floyd-Warshall)  
✅ BST and AVL tree for hierarchical zone indexing  
✅ Two MST algorithms for infrastructure planning (Prim's, Kruskal's)  
✅ Topological sort for project scheduling  
✅ Support for both one-way and two-way roads  
✅ Zone categorization system  
✅ Sample data generator for testing  

### System Capabilities
- *Navigation:* Find optimal routes between any two points.
- *Planning:* Design cost-effective road networks.
- *Indexing:* Perform quick zone lookups with balanced trees.
- *Scheduling:* Prioritize construction projects based on dependencies.
- *Flexibility:* Handle both directed and undirected graph scenarios.

---

## 9. Testing Scenarios

| Test Case          | Input                         | Expected Output                 | Status |
|--------------------|-------------------------------|---------------------------------|--------|
| *Shortest Path*    | Nodes 0 → 5                 | Path with the minimum distance found | ✅ Pass |
| *All-Pairs Distance*| Graph with 6 nodes            | A 6×6 complete distance matrix  | ✅ Pass |
| *MST Generation*   | Graph with 10 edges           | A spanning tree with 5 edges and min cost | ✅ Pass |
| *Zone Search*      | Search for ID: 3              | "University Area" details returned | ✅ Pass |
| *Cycle Detection*  | Directed Acyclic Graph (DAG) input | A valid topological order generated | ✅ Pass |

---

## 10. Challenges & Solutions

| Challenge                      | Solution Implemented                               |
|--------------------------------|----------------------------------------------------|
| *Handling disconnected graphs* | Check for graph connectivity; handle infinite distances. |
| *One-way road representation*  | Use a boolean flag or separate directed edges.     |
| *Efficient path reconstruction*| Track a parent[] array in Dijkstra's algorithm.    |
| *AVL tree balancing*           | Implemented all four rotation cases (LL, RR, LR, RL). |
| *MST cycle detection*          | Used a Union-Find data structure with path compression. |

---

## 11. Real-World Applications

- *Traffic Management:* Suggesting optimal routes to drivers during peak hours.
- *Emergency Services:* Finding the fastest path for ambulances, fire trucks, and police.
- *Infrastructure Planning:* Designing cost-effective road, power, or water networks.
- *Delivery & Logistics:* Planning efficient multi-stop routes for delivery services.
- *Urban Development:* Managing hierarchical city zones and planning expansions.

---

## 12. Learning Outcomes

✅ Mastered graph representations (Matrix, List) and traversals (BFS, DFS).  
✅ Implemented and analyzed classical shortest path algorithms.  
✅ Applied MST algorithms to solve real-world optimization problems.  
✅ Understood the theory and implementation of self-balancing tree structures (AVL).  
✅ Analyzed time-space complexity trade-offs for different algorithms and data structures.  
✅ Developed practical problem-solving skills for complex systems.  

---

## 13. Conclusion

The Smart City Road Navigation System successfully demonstrates the practical application of advanced data structures and algorithms in urban planning and logistics. The system provides an efficient and scalable solution for:

- *Route Optimization:* Through Dijkstra's and Floyd-Warshall algorithms.
- *Infrastructure Planning:* Using MST algorithms for minimum cost.
- *Zone Management:* Via balanced tree structures for fast lookups.
- *Construction Scheduling:* Through topological sorting for dependency management.

### Key Achievements
- Complete implementation of 5 major graph and tree algorithms.
- Support for dual graph representations for flexibility.
- Robust hierarchical zone indexing system.
- Comprehensive testing framework to validate correctness.

### Future Enhancements
- Implement the A* algorithm for heuristic-based pathfinding.
- Integrate real-time traffic data to influence edge weights.
- Develop a GUI for visual representation of the graph and paths.
- Add database persistence to save and load city models.
- Extend to multi-modal transportation (e.g., include subways, buses).

---

## 14. Code Statistics

| Metric             | Value             |
|--------------------|-------------------|
| *Lines of Code*    | ~950              |
| *Classes*          | 8                 |
| *Major Algorithms* | 7 (Dijkstra, Floyd, Prim, Kruskal, TopoSort, BST, AVL) |
| *Time Complexities*| O(1) to O(V³)     |
| *Data Structures*  | 4 (Graph, BST, AVL, Lists) |