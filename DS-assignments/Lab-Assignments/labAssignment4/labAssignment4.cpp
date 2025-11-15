#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

class Building {
public:
    int buildingID;
    string buildingName;
    string locationDetails;
    
    Building() {
        buildingID = 0;
        buildingName = "";
        locationDetails = "";
    }
    
    Building(int id, string name, string location) {
        buildingID = id;
        buildingName = name;
        locationDetails = location;
    }
    
    void display() {
        cout << "ID: " << buildingID 
             << " | Name: " << buildingName 
             << " | Location: " << locationDetails << endl;
    }
};

// ==================== BINARY SEARCH TREE ====================
class BSTNode {
public:
    Building data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(Building b) {
        data = b;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    BSTNode* root;
    
    // Helper function for insertion
    BSTNode* insertHelper(BSTNode* node, Building b) {
        if (node == nullptr) {
            return new BSTNode(b);
        }
        
        if (b.buildingID < node->data.buildingID) {
            node->left = insertHelper(node->left, b);
        } else if (b.buildingID > node->data.buildingID) {
            node->right = insertHelper(node->right, b);
        }
        
        return node;
    }
    
    // Helper functions for traversals
    void inorderHelper(BSTNode* node) {
        if (node != nullptr) {
            inorderHelper(node->left);
            node->data.display();
            inorderHelper(node->right);
        }
    }
    
    void preorderHelper(BSTNode* node) {
        if (node != nullptr) {
            node->data.display();
            preorderHelper(node->left);
            preorderHelper(node->right);
        }
    }
    
    void postorderHelper(BSTNode* node) {
        if (node != nullptr) {
            postorderHelper(node->left);
            postorderHelper(node->right);
            node->data.display();
        }
    }
    
    // Helper for search
    BSTNode* searchHelper(BSTNode* node, int id) {
        if (node == nullptr || node->data.buildingID == id) {
            return node;
        }
        
        if (id < node->data.buildingID) {
            return searchHelper(node->left, id);
        }
        
        return searchHelper(node->right, id);
    }
    
public:
    BinarySearchTree() {
        root = nullptr;
    }
    
    void insert(Building b) {
        root = insertHelper(root, b);
        cout << "Building inserted in BST successfully!" << endl;
    }
    
    void inorderTraversal() {
        cout << "\n--- Inorder Traversal (Sorted by ID) ---" << endl;
        inorderHelper(root);
    }
    
    void preorderTraversal() {
        cout << "\n--- Preorder Traversal ---" << endl;
        preorderHelper(root);
    }
    
    void postorderTraversal() {
        cout << "\n--- Postorder Traversal ---" << endl;
        postorderHelper(root);
    }
    
    Building* search(int id) {
        BSTNode* result = searchHelper(root, id);
        if (result != nullptr) {
            return &(result->data);
        }
        return nullptr;
    }
};

// ==================== AVL TREE ====================
class AVLNode {
public:
    Building data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(Building b) {
        data = b;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    AVLNode* root;
    
    int getHeight(AVLNode* node) {
        if (node == nullptr) return 0;
        return node->height;
    }
    
    int getBalance(AVLNode* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        
        return x;
    }
    
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        
        return y;
    }
    
    AVLNode* insertHelper(AVLNode* node, Building b) {
        // Step 1: Perform normal BST insertion
        if (node == nullptr) {
            return new AVLNode(b);
        }
        
        if (b.buildingID < node->data.buildingID) {
            node->left = insertHelper(node->left, b);
        } else if (b.buildingID > node->data.buildingID) {
            node->right = insertHelper(node->right, b);
        } else {
            return node; // Duplicate IDs not allowed
        }
        
        // Step 2: Update height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        
        // Step 3: Get balance factor
        int balance = getBalance(node);
        
        // Step 4: Balance the tree
        // Left Left Case
        if (balance > 1 && b.buildingID < node->left->data.buildingID) {
            return rotateRight(node);
        }
        
        // Right Right Case
        if (balance < -1 && b.buildingID > node->right->data.buildingID) {
            return rotateLeft(node);
        }
        
        // Left Right Case
        if (balance > 1 && b.buildingID > node->left->data.buildingID) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right Left Case
        if (balance < -1 && b.buildingID < node->right->data.buildingID) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    void inorderHelper(AVLNode* node) {
        if (node != nullptr) {
            inorderHelper(node->left);
            node->data.display();
            inorderHelper(node->right);
        }
    }
    
public:
    AVLTree() {
        root = nullptr;
    }
    
    void insert(Building b) {
        root = insertHelper(root, b);
        cout << "Building inserted in AVL Tree successfully!" << endl;
    }
    
    void display() {
        cout << "\n--- AVL Tree Contents (Balanced) ---" << endl;
        inorderHelper(root);
    }
};

// ==================== GRAPH IMPLEMENTATION ====================
class Graph {
private:
    int numBuildings;
    vector<vector<int>> adjacencyMatrix;
    vector<vector<pair<int, int>>> adjacencyList; // pair<destination, weight>
    vector<string> buildingNames;
    
public:
    Graph(int n) {
        numBuildings = n;
        adjacencyMatrix.resize(n, vector<int>(n, 0));
        adjacencyList.resize(n);
        buildingNames.resize(n);
    }
    
    void addBuilding(int index, string name) {
        if (index < numBuildings) {
            buildingNames[index] = name;
        }
    }
    
    void addEdge(int src, int dest, int weight) {
        // For adjacency matrix
        adjacencyMatrix[src][dest] = weight;
        adjacencyMatrix[dest][src] = weight; // Undirected graph
        
        // For adjacency list
        adjacencyList[src].push_back({dest, weight});
        adjacencyList[dest].push_back({src, weight}); // Undirected graph
    }
    
    void displayMatrix() {
        cout << "\n--- Adjacency Matrix ---" << endl;
        cout << "    ";
        for (int i = 0; i < numBuildings; i++) {
            cout << setw(4) << i;
        }
        cout << endl;
        
        for (int i = 0; i < numBuildings; i++) {
            cout << setw(4) << i;
            for (int j = 0; j < numBuildings; j++) {
                cout << setw(4) << adjacencyMatrix[i][j];
            }
            cout << " (" << buildingNames[i] << ")" << endl;
        }
    }
    
    void displayList() {
        cout << "\n--- Adjacency List ---" << endl;
        for (int i = 0; i < numBuildings; i++) {
            cout << i << " (" << buildingNames[i] << "): ";
            for (auto edge : adjacencyList[i]) {
                cout << "[" << edge.first << ", " << edge.second << "] ";
            }
            cout << endl;
        }
    }
    
    // Dijkstra's Algorithm for shortest path
    void dijkstraShortestPath(int src, int dest) {
        vector<int> dist(numBuildings, INT_MAX);
        vector<int> parent(numBuildings, -1);
        vector<bool> visited(numBuildings, false);
        
        dist[src] = 0;
        
        for (int count = 0; count < numBuildings - 1; count++) {
            int u = -1;
            
            // Find minimum distance vertex
            for (int v = 0; v < numBuildings; v++) {
                if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                    u = v;
                }
            }
            
            visited[u] = true;
            
            // Update distances
            for (int v = 0; v < numBuildings; v++) {
                if (adjacencyMatrix[u][v] != 0 && !visited[v]) {
                    if (dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                        dist[v] = dist[u] + adjacencyMatrix[u][v];
                        parent[v] = u;
                    }
                }
            }
        }
        
        // Display result
        cout << "\n--- Shortest Path (Dijkstra's) ---" << endl;
        cout << "From: " << buildingNames[src] << " (ID: " << src << ")" << endl;
        cout << "To: " << buildingNames[dest] << " (ID: " << dest << ")" << endl;
        
        if (dist[dest] == INT_MAX) {
            cout << "No path exists!" << endl;
        } else {
            cout << "Distance: " << dist[dest] << " units" << endl;
            cout << "Path: ";
            
            // Reconstruct path
            vector<int> path;
            int current = dest;
            while (current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            
            reverse(path.begin(), path.end());
            
            for (int i = 0; i < path.size(); i++) {
                cout << buildingNames[path[i]];
                if (i < path.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }
    
    // Kruskal's Algorithm for Minimum Spanning Tree
    class Edge {
    public:
        int src, dest, weight;
        Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    };
    
    int findParent(vector<int>& parent, int i) {
        if (parent[i] == i) return i;
        return parent[i] = findParent(parent, parent[i]);
    }
    
    void unionSet(vector<int>& parent, vector<int>& rank, int x, int y) {
        int xroot = findParent(parent, x);
        int yroot = findParent(parent, y);
        
        if (rank[xroot] < rank[yroot]) {
            parent[xroot] = yroot;
        } else if (rank[xroot] > rank[yroot]) {
            parent[yroot] = xroot;
        } else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }
    
    void kruskalMST() {
        vector<Edge> edges;
        
        // Collect all edges
        for (int i = 0; i < numBuildings; i++) {
            for (int j = i + 1; j < numBuildings; j++) {
                if (adjacencyMatrix[i][j] != 0) {
                    edges.push_back(Edge(i, j, adjacencyMatrix[i][j]));
                }
            }
        }
        
        // Sort edges by weight
        sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
            return a.weight < b.weight;
        });
        
        vector<int> parent(numBuildings);
        vector<int> rank(numBuildings, 0);
        for (int i = 0; i < numBuildings; i++) {
            parent[i] = i;
        }
        
        cout << "\n--- Minimum Spanning Tree (Kruskal's) ---" << endl;
        cout << "Cable Layout Plan:" << endl;
        
        int totalCost = 0;
        int edgeCount = 0;
        
        for (Edge e : edges) {
            int x = findParent(parent, e.src);
            int y = findParent(parent, e.dest);
            
            if (x != y) {
                cout << buildingNames[e.src] << " - " 
                     << buildingNames[e.dest] 
                     << " (Cost: " << e.weight << " units)" << endl;
                totalCost += e.weight;
                unionSet(parent, rank, x, y);
                edgeCount++;
                
                if (edgeCount == numBuildings - 1) break;
            }
        }
        
        cout << "Total Cable Cost: " << totalCost << " units" << endl;
    }
};

// ==================== EXPRESSION TREE ====================
class ExprNode {
public:
    string value;
    ExprNode* left;
    ExprNode* right;
    
    ExprNode(string val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

class ExpressionTree {
private:
    ExprNode* root;
    
    bool isOperator(string s) {
        return (s == "+" || s == "-" || s == "*" || s == "/");
    }
    
    double evaluateHelper(ExprNode* node) {
        if (node == nullptr) return 0;
        
        // If leaf node (operand)
        if (node->left == nullptr && node->right == nullptr) {
            return stod(node->value);
        }
        
        // Evaluate left and right subtrees
        double left = evaluateHelper(node->left);
        double right = evaluateHelper(node->right);
        
        // Apply operator
        if (node->value == "+") return left + right;
        if (node->value == "-") return left - right;
        if (node->value == "*") return left * right;
        if (node->value == "/") return (right != 0) ? left / right : 0;
        
        return 0;
    }
    
    void inorderHelper(ExprNode* node) {
        if (node != nullptr) {
            if (isOperator(node->value)) cout << "(";
            inorderHelper(node->left);
            cout << node->value << " ";
            inorderHelper(node->right);
            if (isOperator(node->value)) cout << ")";
        }
    }
    
public:
    ExpressionTree() {
        root = nullptr;
    }
    
    // Build expression tree from postfix expression
    void buildFromPostfix(vector<string> postfix) {
        stack<ExprNode*> st;
        
        for (string token : postfix) {
            ExprNode* newNode = new ExprNode(token);
            
            if (isOperator(token)) {
                newNode->right = st.top(); st.pop();
                newNode->left = st.top(); st.pop();
            }
            
            st.push(newNode);
        }
        
        root = st.top();
    }
    
    double evaluate() {
        return evaluateHelper(root);
    }
    
    void displayInfix() {
        cout << "Infix Expression: ";
        inorderHelper(root);
        cout << endl;
    }
    
    // Energy bill calculator
    double calculateEnergyBill(double units, double rate, double fixedCharge) {
        // Build expression tree for: (units * rate) + fixedCharge
        root = new ExprNode("+");
        root->left = new ExprNode("*");
        root->right = new ExprNode(to_string(fixedCharge));
        root->left->left = new ExprNode(to_string(units));
        root->left->right = new ExprNode(to_string(rate));
        
        return evaluate();
    }
};

class CampusNavigationSystem {
private:
    BinarySearchTree bst;
    AVLTree avl;
    Graph* campusGraph;
    ExpressionTree exprTree;
    vector<Building> buildings;
    
public:
    CampusNavigationSystem() {
        campusGraph = nullptr;
    }
    
    void addBuildingRecord() {
        int id;
        string name, location;
        
        cout << "\n--- Add New Building ---" << endl;
        cout << "Enter Building ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Building Name: ";
        getline(cin, name);
        cout << "Enter Location Details: ";
        getline(cin, location);
        
        Building newBuilding(id, name, location);
        buildings.push_back(newBuilding);
        
        // Add to both BST and AVL tree
        bst.insert(newBuilding);
        avl.insert(newBuilding);
    }
    
    void listCampusLocations() {
        cout << "\n--- Campus Locations ---" << endl;
        cout << "Choose traversal type:" << endl;
        cout << "1. Inorder (Sorted by ID)" << endl;
        cout << "2. Preorder" << endl;
        cout << "3. Postorder" << endl;
        cout << "Enter choice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                bst.inorderTraversal();
                break;
            case 2:
                bst.preorderTraversal();
                break;
            case 3:
                bst.postorderTraversal();
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    
    void constructCampusGraph() {
        int n, edges;
        
        cout << "\n--- Construct Campus Graph ---" << endl;
        cout << "Enter number of buildings: ";
        cin >> n;
        
        campusGraph = new Graph(n);
        
        // Add building names
        for (int i = 0; i < n; i++) {
            string name;
            cout << "Enter name for building " << i << ": ";
            cin >> name;
            campusGraph->addBuilding(i, name);
        }
        
        cout << "Enter number of paths (edges): ";
        cin >> edges;
        
        for (int i = 0; i < edges; i++) {
            int src, dest, weight;
            cout << "Enter path " << i + 1 << " (source destination distance): ";
            cin >> src >> dest >> weight;
            campusGraph->addEdge(src, dest, weight);
        }
        
        cout << "Graph constructed successfully!" << endl;
    }
    
    void findOptimalPath() {
        if (campusGraph == nullptr) {
            cout << "Please construct the campus graph first!" << endl;
            return;
        }
        
        int src, dest;
        cout << "\n--- Find Optimal Path ---" << endl;
        cout << "Enter source building ID: ";
        cin >> src;
        cout << "Enter destination building ID: ";
        cin >> dest;
        
        campusGraph->dijkstraShortestPath(src, dest);
    }
    
    void planUtilityLayout() {
        if (campusGraph == nullptr) {
            cout << "Please construct the campus graph first!" << endl;
            return;
        }
        
        campusGraph->kruskalMST();
    }
    
    void calculateEnergyBill() {
        double units, rate, fixed;
        
        cout << "\n--- Energy Bill Calculator ---" << endl;
        cout << "Enter units consumed: ";
        cin >> units;
        cout << "Enter rate per unit: ";
        cin >> rate;
        cout << "Enter fixed charges: ";
        cin >> fixed;
        
        double bill = exprTree.calculateEnergyBill(units, rate, fixed);
        
        cout << "\nExpression: (units * rate) + fixed_charges" << endl;
        cout << "Calculation: (" << units << " * " << rate << ") + " << fixed << endl;
        cout << "Total Bill: $" << fixed << setprecision(2) << bill << endl;
    }
    
    void displayGraphs() {
        if (campusGraph == nullptr) {
            cout << "Please construct the campus graph first!" << endl;
            return;
        }
        
        campusGraph->displayMatrix();
        campusGraph->displayList();
    }
    
    void searchBuilding() {
        int id;
        cout << "\n--- Search Building ---" << endl;
        cout << "Enter Building ID to search: ";
        cin >> id;
        
        Building* result = bst.search(id);
        if (result != nullptr) {
            cout << "Building found:" << endl;
            result->display();
        } else {
            cout << "Building not found!" << endl;
        }
    }
    
    void displayAVLTree() {
        avl.display();
    }
    
    // Add sample data for testing
    void loadSampleData() {
        // Sample buildings
        buildings.push_back(Building(1, "Engineering Building", "North Campus"));
        buildings.push_back(Building(2, "Library", "Central Campus"));
        buildings.push_back(Building(3, "Science Lab", "East Campus"));
        buildings.push_back(Building(4, "Student Center", "Central Campus"));
        buildings.push_back(Building(5, "Admin Building", "West Campus"));
        
        // Add to trees
        for (Building b : buildings) {
            bst.insert(b);
            avl.insert(b);
        }
        
        // Create sample graph
        campusGraph = new Graph(5);
        campusGraph->addBuilding(0, "Engineering");
        campusGraph->addBuilding(1, "Library");
        campusGraph->addBuilding(2, "Science Lab");
        campusGraph->addBuilding(3, "Student Center");
        campusGraph->addBuilding(4, "Admin");
        
        // Add paths (edges)
        campusGraph->addEdge(0, 1, 10);  // Engineering to Library
        campusGraph->addEdge(0, 2, 15);  // Engineering to Science Lab
        campusGraph->addEdge(1, 3, 5);   // Library to Student Center
        campusGraph->addEdge(1, 4, 20);  // Library to Admin
        campusGraph->addEdge(2, 3, 8);   // Science Lab to Student Center
        campusGraph->addEdge(3, 4, 12);  // Student Center to Admin
        
        cout << "Sample data loaded successfully!" << endl;
    }
};

int main() {
    CampusNavigationSystem system;
    int choice;
    
    cout << "=============================================" << endl;
    cout << "   CAMPUS NAVIGATION AND UTILITY PLANNER    " << endl;
    cout << "=============================================" << endl;
    
    while (true) {
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Add Building Record" << endl;
        cout << "2. List Campus Locations (Tree Traversal)" << endl;
        cout << "3. Search Building" << endl;
        cout << "4. Display AVL Tree" << endl;
        cout << "5. Construct Campus Graph" << endl;
        cout << "6. Display Graph Representations" << endl;
        cout << "7. Find Optimal Path (Dijkstra's)" << endl;
        cout << "8. Plan Utility Layout (Kruskal's MST)" << endl;
        cout << "9. Calculate Energy Bill (Expression Tree)" << endl;
        cout << "10. Load Sample Data" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                system.addBuildingRecord();
                break;
                
            case 2:
                system.listCampusLocations();
                break;
                
            case 3:
                system.searchBuilding();
                break;
                
            case 4:
                system.displayAVLTree();
                break;
                
            case 5:
                system.constructCampusGraph();
                break;
                
            case 6:
                system.displayGraphs();
                break;
                
            case 7:
                system.findOptimalPath();
                break;
                
            case 8:
                system.planUtilityLayout();
                break;
                
            case 9:
                system.calculateEnergyBill();
                break;
                
            case 10:
                system.loadSampleData();
                break;
                
            case 11:
                cout << "\nThank you for using Campus Navigation System!" << endl;
                return 0;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}