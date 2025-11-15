#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>
#include <iomanip>
#include <map>
using namespace std;

// ==================== ROAD NETWORK NODE ====================
class RoadNode {
public:
    int nodeID;
    string nodeName;
    string zoneDetails;
    
    RoadNode() {
        nodeID = 0;
        nodeName = "";
        zoneDetails = "";
    }
    
    RoadNode(int id, string name, string zone) {
        nodeID = id;
        nodeName = name;
        zoneDetails = zone;
    }
    
    void display() {
        cout << "ID: " << nodeID 
             << " | Name: " << nodeName 
             << " | Zone: " << zoneDetails << endl;
    }
};

// ==================== BINARY SEARCH TREE FOR ZONES ====================
class BSTNode {
public:
    RoadNode data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(RoadNode node) {
        data = node;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    BSTNode* root;
    
    BSTNode* insertHelper(BSTNode* node, RoadNode data) {
        if (node == nullptr) {
            return new BSTNode(data);
        }
        
        if (data.nodeID < node->data.nodeID) {
            node->left = insertHelper(node->left, data);
        } else if (data.nodeID > node->data.nodeID) {
            node->right = insertHelper(node->right, data);
        }
        
        return node;
    }
    
    void inorderHelper(BSTNode* node) {
        if (node != nullptr) {
            inorderHelper(node->left);
            node->data.display();
            inorderHelper(node->right);
        }
    }
    
    BSTNode* searchHelper(BSTNode* node, int id) {
        if (node == nullptr || node->data.nodeID == id) {
            return node;
        }
        
        if (id < node->data.nodeID) {
            return searchHelper(node->left, id);
        }
        
        return searchHelper(node->right, id);
    }
    
public:
    BinarySearchTree() {
        root = nullptr;
    }
    
    void insert(RoadNode data) {
        root = insertHelper(root, data);
    }
    
    void displayInorder() {
        cout << "\n--- City Zones (BST Inorder) ---" << endl;
        inorderHelper(root);
    }
    
    RoadNode* search(int id) {
        BSTNode* result = searchHelper(root, id);
        if (result != nullptr) {
            return &(result->data);
        }
        return nullptr;
    }
};

// ==================== AVL TREE FOR ZONES ====================
class AVLNode {
public:
    RoadNode data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(RoadNode node) {
        data = node;
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
    
    AVLNode* insertHelper(AVLNode* node, RoadNode data) {
        // Standard BST insertion
        if (node == nullptr) {
            return new AVLNode(data);
        }
        
        if (data.nodeID < node->data.nodeID) {
            node->left = insertHelper(node->left, data);
        } else if (data.nodeID > node->data.nodeID) {
            node->right = insertHelper(node->right, data);
        } else {
            return node;
        }
        
        // Update height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        
        // Get balance factor
        int balance = getBalance(node);
        
        // Left Left Case
        if (balance > 1 && data.nodeID < node->left->data.nodeID) {
            return rotateRight(node);
        }
        
        // Right Right Case
        if (balance < -1 && data.nodeID > node->right->data.nodeID) {
            return rotateLeft(node);
        }
        
        // Left Right Case
        if (balance > 1 && data.nodeID > node->left->data.nodeID) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Right Left Case
        if (balance < -1 && data.nodeID < node->right->data.nodeID) {
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
    
    void insert(RoadNode data) {
        root = insertHelper(root, data);
    }
    
    void display() {
        cout << "\n--- City Zones (AVL Tree - Balanced) ---" << endl;
        inorderHelper(root);
    }
};

// ==================== GRAPH IMPLEMENTATION ====================
class RoadGraph {
private:
    int numNodes;
    vector<vector<int>> adjacencyMatrix;
    vector<vector<pair<int, int>>> adjacencyList; // pair<destination, weight>
    vector<RoadNode> nodes;
    map<int, int> nodeIDToIndex;
    
public:
    RoadGraph(int n) {
        numNodes = n;
        adjacencyMatrix.resize(n, vector<int>(n, INT_MAX));
        adjacencyList.resize(n);
        nodes.resize(n);
        
        // Initialize diagonal to 0
        for (int i = 0; i < n; i++) {
            adjacencyMatrix[i][i] = 0;
        }
    }
    
    void addNode(int index, RoadNode node) {
        if (index < numNodes) {
            nodes[index] = node;
            nodeIDToIndex[node.nodeID] = index;
        }
    }
    
    void addRoad(int src, int dest, int weight, bool isOneWay = false) {
        // For adjacency matrix
        adjacencyMatrix[src][dest] = weight;
        if (!isOneWay) {
            adjacencyMatrix[dest][src] = weight;
        }
        
        // For adjacency list
        adjacencyList[src].push_back({dest, weight});
        if (!isOneWay) {
            adjacencyList[dest].push_back({src, weight});
        }
    }
    
    void displayMatrix() {
        cout << "\n--- Adjacency Matrix ---" << endl;
        cout << "     ";
        for (int i = 0; i < numNodes; i++) {
            cout << setw(12) << nodes[i].nodeName.substr(0, 10);
        }
        cout << endl;
        
        for (int i = 0; i < numNodes; i++) {
            cout << setw(5) << nodes[i].nodeName.substr(0, 4) << " ";
            for (int j = 0; j < numNodes; j++) {
                if (adjacencyMatrix[i][j] == INT_MAX) {
                    cout << setw(12) << "INF";
                } else {
                    cout << setw(12) << adjacencyMatrix[i][j];
                }
            }
            cout << endl;
        }
    }
    
    void displayList() {
        cout << "\n--- Adjacency List ---" << endl;
        for (int i = 0; i < numNodes; i++) {
            cout << nodes[i].nodeName << " -> ";
            for (auto edge : adjacencyList[i]) {
                cout << "[" << nodes[edge.first].nodeName << ", " << edge.second << "km] ";
            }
            cout << endl;
        }
    }
    
    // ==================== DIJKSTRA'S ALGORITHM ====================
    void dijkstraShortestPath(int src, int dest) {
        vector<int> dist(numNodes, INT_MAX);
        vector<int> parent(numNodes, -1);
        vector<bool> visited(numNodes, false);
        
        dist[src] = 0;
        
        for (int count = 0; count < numNodes - 1; count++) {
            int u = -1;
            
            // Find minimum distance vertex
            for (int v = 0; v < numNodes; v++) {
                if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                    u = v;
                }
            }
            
            if (u == -1 || dist[u] == INT_MAX) break;
            
            visited[u] = true;
            
            // Update distances using adjacency list (more efficient)
            for (auto& edge : adjacencyList[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }
        
        // Display result
        cout << "\n--- Shortest Path (Dijkstra's Algorithm) ---" << endl;
        cout << "From: " << nodes[src].nodeName << " (ID: " << nodes[src].nodeID << ")" << endl;
        cout << "To: " << nodes[dest].nodeName << " (ID: " << nodes[dest].nodeID << ")" << endl;
        
        if (dist[dest] == INT_MAX) {
            cout << "No path exists!" << endl;
        } else {
            cout << "Shortest Distance: " << dist[dest] << " km" << endl;
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
                cout << nodes[path[i]].nodeName;
                if (i < path.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }
    
    // ==================== FLOYD-WARSHALL ALGORITHM ====================
    void floydWarshall() {
        cout << "\n--- All Pairs Shortest Path (Floyd-Warshall) ---" << endl;
        
        // Create a copy of adjacency matrix
        vector<vector<int>> dist = adjacencyMatrix;
        
        // Floyd-Warshall algorithm
        for (int k = 0; k < numNodes; k++) {
            for (int i = 0; i < numNodes; i++) {
                for (int j = 0; j < numNodes; j++) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }
        }
        
        // Display shortest paths matrix
        cout << "\nShortest Distance Matrix:" << endl;
        cout << "     ";
        for (int i = 0; i < numNodes; i++) {
            cout << setw(12) << nodes[i].nodeName.substr(0, 10);
        }
        cout << endl;
        
        for (int i = 0; i < numNodes; i++) {
            cout << setw(5) << nodes[i].nodeName.substr(0, 4) << " ";
            for (int j = 0; j < numNodes; j++) {
                if (dist[i][j] == INT_MAX) {
                    cout << setw(12) << "INF";
                } else {
                    cout << setw(12) << dist[i][j];
                }
            }
            cout << endl;
        }
    }
    
    // ==================== TOPOLOGICAL SORT ====================
    void topologicalSort() {
        cout << "\n--- Topological Sort (Construction Priority) ---" << endl;
        
        vector<int> indegree(numNodes, 0);
        
        // Calculate indegree for each node
        for (int u = 0; u < numNodes; u++) {
            for (auto& edge : adjacencyList[u]) {
                indegree[edge.first]++;
            }
        }
        
        queue<int> q;
        for (int i = 0; i < numNodes; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> result;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            result.push_back(u);
            
            for (auto& edge : adjacencyList[u]) {
                indegree[edge.first]--;
                if (indegree[edge.first] == 0) {
                    q.push(edge.first);
                }
            }
        }
        
        if (result.size() != numNodes) {
            cout << "Graph contains a cycle! Cannot perform topological sort." << endl;
        } else {
            cout << "Construction Priority Order:" << endl;
            for (int i = 0; i < result.size(); i++) {
                cout << i + 1 << ". " << nodes[result[i]].nodeName 
                     << " (Zone: " << nodes[result[i]].zoneDetails << ")" << endl;
            }
        }
    }
    
    // ==================== PRIM'S ALGORITHM (MST) ====================
    void primMST() {
        cout << "\n--- Minimum Spanning Tree (Prim's Algorithm) ---" << endl;
        
        vector<bool> inMST(numNodes, false);
        vector<int> key(numNodes, INT_MAX);
        vector<int> parent(numNodes, -1);
        
        key[0] = 0;
        
        for (int count = 0; count < numNodes - 1; count++) {
            int u = -1;
            
            // Find minimum key vertex
            for (int v = 0; v < numNodes; v++) {
                if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                    u = v;
                }
            }
            
            if (u == -1 || key[u] == INT_MAX) break;
            
            inMST[u] = true;
            
            // Update key values
            for (auto& edge : adjacencyList[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (!inMST[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                }
            }
        }
        
        // Display MST
        cout << "Cost-Effective Road Network Plan:" << endl;
        int totalCost = 0;
        for (int i = 1; i < numNodes; i++) {
            if (parent[i] != -1 && key[i] != INT_MAX) {
                cout << nodes[parent[i]].nodeName << " - " 
                     << nodes[i].nodeName 
                     << " (Cost: " << key[i] << " km)" << endl;
                totalCost += key[i];
            }
        }
        cout << "Total Road Construction Cost: " << totalCost << " km" << endl;
    }
    
    // ==================== KRUSKAL'S ALGORITHM (MST) ====================
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
        cout << "\n--- Minimum Spanning Tree (Kruskal's Algorithm) ---" << endl;
        
        vector<Edge> edges;
        
        // Collect all edges
        for (int i = 0; i < numNodes; i++) {
            for (auto& edge : adjacencyList[i]) {
                if (i < edge.first) { // Avoid duplicate edges
                    edges.push_back(Edge(i, edge.first, edge.second));
                }
            }
        }
        
        // Sort edges by weight
        sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
            return a.weight < b.weight;
        });
        
        vector<int> parent(numNodes);
        vector<int> rank(numNodes, 0);
        for (int i = 0; i < numNodes; i++) {
            parent[i] = i;
        }
        
        cout << "Cost-Effective Road Network Plan:" << endl;
        
        int totalCost = 0;
        int edgeCount = 0;
        
        for (Edge& e : edges) {
            int x = findParent(parent, e.src);
            int y = findParent(parent, e.dest);
            
            if (x != y) {
                cout << nodes[e.src].nodeName << " - " 
                     << nodes[e.dest].nodeName 
                     << " (Cost: " << e.weight << " km)" << endl;
                totalCost += e.weight;
                unionSet(parent, rank, x, y);
                edgeCount++;
                
                if (edgeCount == numNodes - 1) break;
            }
        }
        
        cout << "Total Road Construction Cost: " << totalCost << " km" << endl;
    }
    
    // Get number of nodes
    int getNumNodes() {
        return numNodes;
    }
    
    // Get nodes
    vector<RoadNode> getNodes() {
        return nodes;
    }
};

class SmartCityNavigationSystem {
private:
    RoadGraph* roadNetwork;
    BinarySearchTree bst;
    AVLTree avl;
    vector<RoadNode> cityZones;
    
public:
    SmartCityNavigationSystem() {
        roadNetwork = nullptr;
    }
    
    // Add road network
    void addRoadNetwork() {
        int n, edges;
        
        cout << "\n--- Construct Road Network ---" << endl;
        cout << "Enter number of intersections/zones: ";
        cin >> n;
        
        roadNetwork = new RoadGraph(n);
        
        // Add nodes
        for (int i = 0; i < n; i++) {
            int id;
            string name, zone;
            cout << "\n--- Node " << i + 1 << " ---" << endl;
            cout << "Enter Node ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Node Name: ";
            getline(cin, name);
            cout << "Enter Zone Type (Residential/Commercial/Industrial): ";
            getline(cin, zone);
            
            RoadNode node(id, name, zone);
            roadNetwork->addNode(i, node);
            cityZones.push_back(node);
            
            // Add to trees
            bst.insert(node);
            avl.insert(node);
        }
        
        cout << "\nEnter number of roads: ";
        cin >> edges;
        
        for (int i = 0; i < edges; i++) {
            int src, dest, weight;
            char oneWay;
            cout << "\n--- Road " << i + 1 << " ---" << endl;
            cout << "Enter source node index (0-" << n-1 << "): ";
            cin >> src;
            cout << "Enter destination node index (0-" << n-1 << "): ";
            cin >> dest;
            cout << "Enter distance (km): ";
            cin >> weight;
            cout << "Is it one-way? (y/n): ";
            cin >> oneWay;
            
            roadNetwork->addRoad(src, dest, weight, (oneWay == 'y' || oneWay == 'Y'));
        }
        
        cout << "\nRoad network constructed successfully!" << endl;
    }
    
    // Compute shortest path
    void computeShortestPath() {
        if (roadNetwork == nullptr) {
            cout << "Please construct the road network first!" << endl;
            return;
        }
        
        int choice;
        cout << "\n--- Shortest Path Algorithms ---" << endl;
        cout << "1. Dijkstra's Algorithm (Single Source)" << endl;
        cout << "2. Floyd-Warshall Algorithm (All Pairs)" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if (choice == 1) {
            int src, dest;
            cout << "Enter source node index: ";
            cin >> src;
            cout << "Enter destination node index: ";
            cin >> dest;
            roadNetwork->dijkstraShortestPath(src, dest);
        } else if (choice == 2) {
            roadNetwork->floydWarshall();
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    // Index city zones
    void indexCityZones() {
        if (cityZones.empty()) {
            cout << "No zones to display! Please add road network first." << endl;
            return;
        }
        
        int choice;
        cout << "\n--- City Zone Indexing ---" << endl;
        cout << "1. Display zones using BST" << endl;
        cout << "2. Display zones using AVL Tree" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if (choice == 1) {
            bst.displayInorder();
        } else if (choice == 2) {
            avl.display();
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    // Search zone
    void searchZone() {
        int id;
        cout << "\n--- Search City Zone ---" << endl;
        cout << "Enter Zone ID to search: ";
        cin >> id;
        
        RoadNode* result = bst.search(id);
        if (result != nullptr) {
            cout << "\nZone Found:" << endl;
            result->display();
        } else {
            cout << "Zone not found!" << endl;
        }
    }
    
    // Prioritize construction
    void prioritizeConstruction() {
        if (roadNetwork == nullptr) {
            cout << "Please construct the road network first!" << endl;
            return;
        }
        
        roadNetwork->topologicalSort();
    }
    
    // Plan road network
    void planRoadNetwork() {
        if (roadNetwork == nullptr) {
            cout << "Please construct the road network first!" << endl;
            return;
        }
        
        int choice;
        cout << "\n--- Minimum Spanning Tree ---" << endl;
        cout << "1. Prim's Algorithm" << endl;
        cout << "2. Kruskal's Algorithm" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if (choice == 1) {
            roadNetwork->primMST();
        } else if (choice == 2) {
            roadNetwork->kruskalMST();
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    // Display graph representations
    void displayGraphs() {
        if (roadNetwork == nullptr) {
            cout << "Please construct the road network first!" << endl;
            return;
        }
        
        int choice;
        cout << "\n--- Graph Representation ---" << endl;
        cout << "1. Adjacency Matrix" << endl;
        cout << "2. Adjacency List" << endl;
        cout << "3. Both" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if (choice == 1) {
            roadNetwork->displayMatrix();
        } else if (choice == 2) {
            roadNetwork->displayList();
        } else if (choice == 3) {
            roadNetwork->displayMatrix();
            roadNetwork->displayList();
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    // Load sample data
    void loadSampleData() {
        cout << "\n--- Loading Sample City Data ---" << endl;
        
        // Create a sample road network with 6 nodes
        roadNetwork = new RoadGraph(6);
        
        // Add zones
        RoadNode zone1(1, "City Center", "Commercial");
        RoadNode zone2(2, "North District", "Residential");
        RoadNode zone3(3, "Industrial Park", "Industrial");
        RoadNode zone4(4, "University Area", "Educational");
        RoadNode zone5(5, "Shopping Mall", "Commercial");
        RoadNode zone6(6, "Airport", "Transportation");
        
        roadNetwork->addNode(0, zone1);
        roadNetwork->addNode(1, zone2);
        roadNetwork->addNode(2, zone3);
        roadNetwork->addNode(3, zone4);
        roadNetwork->addNode(4, zone5);
        roadNetwork->addNode(5, zone6);
        
        cityZones = {zone1, zone2, zone3, zone4, zone5, zone6};
        
        // Add to trees
        for (auto& zone : cityZones) {
            bst.insert(zone);
            avl.insert(zone);
        }
        
        // Add roads (bidirectional)
        roadNetwork->addRoad(0, 1, 5);   // City Center - North District
        roadNetwork->addRoad(0, 2, 8);   // City Center - Industrial Park
        roadNetwork->addRoad(0, 4, 3);   // City Center - Shopping Mall
        roadNetwork->addRoad(1, 3, 4);   // North District - University
        roadNetwork->addRoad(1, 4, 6);   // North District - Shopping Mall
        roadNetwork->addRoad(2, 3, 7);   // Industrial Park - University
        roadNetwork->addRoad(2, 5, 10);  // Industrial Park - Airport
        roadNetwork->addRoad(3, 5, 12);  // University - Airport
        roadNetwork->addRoad(4, 5, 15);  // Shopping Mall - Airport
        
        // Add one-way roads
        roadNetwork->addRoad(0, 3, 9, true);  // City Center -> University (one-way)
        
        cout << "Sample data loaded successfully!" << endl;
        cout << "6 zones and 10 roads added to the system." << endl;
    }
};

int main() {
    SmartCityNavigationSystem system;
    int choice;
    
    cout << "================================================" << endl;
    cout << "      SMART CITY ROAD NAVIGATION SYSTEM        " << endl;
    cout << "================================================" << endl;
    
    while (true) {
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Add Road Network" << endl;
        cout << "2. Compute Shortest Path" << endl;
        cout << "3. Index City Zones" << endl;
        cout << "4. Search Zone by ID" << endl;
        cout << "5. Prioritize Construction (Topological Sort)" << endl;
        cout << "6. Plan Cost-Effective Roads (MST)" << endl;
        cout << "7. Display Graph Representations" << endl;
        cout << "8. Load Sample Data" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                system.addRoadNetwork();
                break;
                
            case 2:
                system.computeShortestPath();
                break;
                
            case 3:
                system.indexCityZones();
                break;
                
            case 4:
                system.searchZone();
                break;
                
            case 5:
                system.prioritizeConstruction();
                break;
                
            case 6:
                system.planRoadNetwork();
                break;
                
            case 7:
                system.displayGraphs();
                break;
                
            case 8:
                system.loadSampleData();
                break;
                
            case 9:
                cout << "\nThank you for using Smart City Navigation System!" << endl;
                return 0;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}