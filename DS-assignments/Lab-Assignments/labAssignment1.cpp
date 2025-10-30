// groceryInventory.cpp

#include <bits/stdc++.h>
using namespace std;

struct Item {
    int id;
    string name;
    int quantity;
    double price;
    Item(int i=0, string n="", int q=0, double p=0.0)
      : id(i), name(move(n)), quantity(q), price(p) {}
};

class Inventory {
private:
    // Main "array-like" storage
    vector<Item> items;

    // Map from ItemID -> index in `items` vector for O(1) ID lookup
    unordered_map<int,int> idIndexMap;

    // Sparse storage for rarely-restocked items (ItemID -> quantity)
    unordered_map<int,int> sparseQty;

public:
    Inventory() = default;

    // Add a new item
    // Complexity: O(1) amortized (vector push_back), O(1) average for map insert
    bool addItem(const Item& it) {
        if (idIndexMap.find(it.id) != idIndexMap.end()) {
            // ID must be unique
            return false;
        }
        items.push_back(it);
        idIndexMap[it.id] = (int)items.size() - 1;
        return true;
    }

    // Search by ID using the map (fast)
    // Complexity: O(1) average
    Item* searchByID(int id) {
        auto it = idIndexMap.find(id);
        if (it == idIndexMap.end()) return nullptr;
        return &items[it->second];
    }

    // Search by Name (linear scan)
    // Complexity: O(n)
    Item* searchByName(const string& name) {
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].name == name) return &items[i];
        }
        return nullptr;
    }

    // Delete by ID (swap-with-back, fast but changes order)
    // Complexity: O(1) average
    bool deleteByID_fast(int id) {
        auto it = idIndexMap.find(id);
        if (it == idIndexMap.end()) return false;
        int idx = it->second;
        int lastIdx = (int)items.size() - 1;
        if (idx != lastIdx) {
            // move last into idx
            items[idx] = items[lastIdx];
            idIndexMap[items[idx].id] = idx; // update moved item's index
        }
        items.pop_back();
        idIndexMap.erase(it);

        // Also remove from sparse if present
        sparseQty.erase(id);
        return true;
    }

    // Delete by ID preserving order (slower because shift)
    // Complexity: O(n)
    bool deleteByID_preserveOrder(int id) {
        auto it = idIndexMap.find(id);
        if (it == idIndexMap.end()) return false;
        int idx = it->second;
        // erase element at idx by shifting left
        items.erase(items.begin() + idx);
        // rebuild idIndexMap (costly)
        idIndexMap.clear();
        for (size_t i = 0; i < items.size(); ++i) idIndexMap[items[i].id] = (int)i;
        sparseQty.erase(id); // remove from sparse if present
        return true;
    }

    // Display all items
    // Complexity: O(n)
    void displayAll() const {
        cout << left << setw(8) << "ItemID"
             << setw(20) << "Name"
             << setw(10) << "Quantity"
             << setw(10) << "Price" << '\n';
        cout << string(48, '-') << '\n';
        for (const auto &it : items) {
            cout << left << setw(8) << it.id
                 << setw(20) << it.name
                 << setw(10) << it.quantity
                 << setw(10) << fixed << setprecision(2) << it.price << '\n';
        }
        cout << '\n';
    }

    // Build a price-quantity table in row-major form (rows = items, cols = 2: price, quantity)
    // Complexity: O(n)
    vector<vector<double>> buildRowMajorTable() const {
        vector<vector<double>> table(items.size(), vector<double>(2));
        for (size_t r = 0; r < items.size(); ++r) {
            table[r][0] = items[r].price;      // column 0 = price
            table[r][1] = (double)items[r].quantity; // column 1 = quantity
        }
        return table;
    }

    // Build a column-major flat representation: flat[col * rows + row]
    // Complexity: O(n)
    vector<double> buildColumnMajorFlat() const {
        size_t rows = items.size();
        size_t cols = 2;
        vector<double> flat(rows * cols, 0.0);
        for (size_t r = 0; r < rows; ++r) {
            // price at (r,0)
            flat[0 * rows + r] = items[r].price;
            // quantity at (r,1)
            flat[1 * rows + r] = (double)items[r].quantity;
        }
        return flat;
    }

    // Print the row-major table neatly
    void printRowMajorTable() const {
        auto table = buildRowMajorTable();
        cout << "Row-major table (Row = item, Col0 = price, Col1 = quantity)\n";
        for (size_t r = 0; r < table.size(); ++r) {
            cout << "ItemID " << items[r].id << " -> price: " << table[r][0]
                 << ", quantity: " << (int)table[r][1] << '\n';
        }
        cout << '\n';
    }

    // Print column-major flat as rows/cols
    void printColumnMajorFlat() const {
        auto flat = buildColumnMajorFlat();
        size_t rows = items.size();
        size_t cols = 2;
        cout << "Column-major flat vector content (index = col*rows + row):\n";
        for (size_t c = 0; c < cols; ++c) {
            for (size_t r = 0; r < rows; ++r) {
                size_t idx = c * rows + r;
                if (c == 0) cout << "ItemID " << items[r].id << " price = " << flat[idx] << '\n';
                else cout << "ItemID " << items[r].id << " quantity = " << (int)flat[idx] << '\n';
            }
        }
        cout << '\n';
    }

    // Build sparse representation for a given list of rarely-restocked ItemIDs
    // We store only non-zero quantities for those items.
    // Complexity: O(k) where k = number of IDs passed
    void buildSparseForRareItems(const vector<int>& rareIDs) {
        sparseQty.clear();
        for (int id : rareIDs) {
            Item* p = searchByID(id);
            if (p && p->quantity != 0) {
                sparseQty[id] = p->quantity;
            }
        }
    }

    // Show sparse contents
    void showSparse() const {
        if (sparseQty.empty()) {
            cout << "Sparse storage is empty.\n\n";
            return;
        }
        cout << "Sparse storage (ItemID -> quantity) for rarely-restocked products:\n";
        for (auto &kv : sparseQty) {
            cout << "ItemID " << kv.first << " -> quantity " << kv.second << '\n';
        }
        cout << '\n';
    }

    // Get quantity by checking sparse first (if exists), else dense item
    // Complexity: O(1) average
    int getQuantityPreferSparse(int id) const {
        auto it = sparseQty.find(id);
        if (it != sparseQty.end()) return it->second;
        // else check dense items (linear search: O(n) here) - but typically we use idIndexMap in non-const methods
        for (const auto &it2 : items) if (it2.id == id) return it2.quantity;
        return 0; // not found
    }

    // Update quantity of an item (keeps idIndexMap correct)
    // Complexity: O(1) average
    bool updateQuantity(int id, int newQty) {
        auto it = idIndexMap.find(id);
        if (it == idIndexMap.end()) return false;
        items[it->second].quantity = newQty;
        // if sparse contains this id, update or remove if zero
        if (sparseQty.find(id) != sparseQty.end()) {
            if (newQty != 0) sparseQty[id] = newQty;
            else sparseQty.erase(id);
        }
        return true;
    }
};

void printMenu() {
    cout << "========== Inventory Menu ==========\n";
    cout << "1  - Add item\n";
    cout << "2  - Delete item (fast, order not preserved)\n";
    cout << "3  - Delete item (preserve order)\n";
    cout << "4  - Search by ID\n";
    cout << "5  - Search by Name\n";
    cout << "6  - Display all items\n";
    cout << "7  - Show row-major price/quantity table\n";
    cout << "8  - Show column-major flat table\n";
    cout << "9  - Build sparse storage for rarely-restocked items\n";
    cout << "10 - Show sparse storage\n";
    cout << "11 - Update quantity\n";
    cout << "0  - Exit\n";
    cout << "Enter choice: ";
}

int main() {
    Inventory inv;
    bool running = true;
    while (running) {
        printMenu();
        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting.\n";
            break;
        }
        if (choice == 0) { running = false; break; }
        if (choice == 1) {
            int id; string name; int q; double p;
            cout << "Enter ID (int): "; cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Name: "; getline(cin, name);
            cout << "Enter Quantity (int): "; cin >> q;
            cout << "Enter Price (double): "; cin >> p;
            bool ok = inv.addItem(Item(id, name, q, p));
            cout << (ok ? "Item added.\n\n" : "Add failed: ID already exists.\n\n");
        } else if (choice == 2) {
            int id; cout << "Enter ID to delete (fast): "; cin >> id;
            bool ok = inv.deleteByID_fast(id);
            cout << (ok ? "Deleted (fast).\n\n" : "Delete failed: ID not found.\n\n");
        } else if (choice == 3) {
            int id; cout << "Enter ID to delete (preserve order): "; cin >> id;
            bool ok = inv.deleteByID_preserveOrder(id);
            cout << (ok ? "Deleted (preserve order).\n\n" : "Delete failed: ID not found.\n\n");
        } else if (choice == 4) {
            int id; cout << "Enter ID to search: "; cin >> id;
            Item* p = inv.searchByID(id);
            if (p) {
                cout << "Found: ID " << p->id << ", Name: " << p->name
                     << ", Qty: " << p->quantity << ", Price: " << p->price << "\n\n";
            } else cout << "Not found.\n\n";
        } else if (choice == 5) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string name; cout << "Enter Name to search: "; getline(cin, name);
            Item* p = inv.searchByName(name);
            if (p) {
                cout << "Found: ID " << p->id << ", Name: " << p->name
                     << ", Qty: " << p->quantity << ", Price: " << p->price << "\n\n";
            } else cout << "Not found.\n\n";
        } else if (choice == 6) {
            inv.displayAll();
        } else if (choice == 7) {
            inv.printRowMajorTable();
        } else if (choice == 8) {
            inv.printColumnMajorFlat();
        } else if (choice == 9) {
            cout << "Enter count of rare item IDs: ";
            int k; cin >> k;
            vector<int> rareIds;
            cout << "Enter " << k << " IDs (space-separated or newline):\n";
            for (int i = 0; i < k; ++i) {
                int id; cin >> id; rareIds.push_back(id);
            }
            inv.buildSparseForRareItems(rareIds);
            cout << "Sparse built.\n\n";
        } else if (choice == 10) {
            inv.showSparse();
        } else if (choice == 11) {
            int id, qty;
            cout << "Enter ID and new quantity: "; cin >> id >> qty;
            bool ok = inv.updateQuantity(id, qty);
            cout << (ok ? "Updated quantity.\n\n" : "Update failed: ID not found.\n\n");
        } else {
            cout << "Unknown choice.\n\n";
        }
    }
    cout << "Exiting inventory program.\n";
    return 0;
}
