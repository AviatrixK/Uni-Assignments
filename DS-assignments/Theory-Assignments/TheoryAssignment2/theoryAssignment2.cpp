#include <bits/stdc++.h>
using namespace std;

// Student-style implementation of Hospital Patient Record Management System
// Covers: linked list (PatientList), stack (UndoStack), priority queue (EmergencyQueue),
// circular queue (for round-robin), polynomial linked list (Billing), and postfix evaluation (Inventory)

// --- Patient ADT ---
struct Patient {
    int patientID;
    string patientName;
    string admissionDate; // simple string like "DD/MM/YYYY"
    string treatmentDetails;
    Patient* next;
    Patient(int id, const string &name, const string &date, const string &treat)
        : patientID(id), patientName(name), admissionDate(date), treatmentDetails(treat), next(nullptr) {}
};

// --- Singly Linked List for Patients ---
class PatientList {
public:
    Patient* head;
    PatientList() : head(nullptr) {}

    void insertPatient(int id, const string &name, const string &date, const string &treat) {
        Patient* node = new Patient(id, name, date, treat);
        if (!head) {
            head = node;
            return;
        }
        Patient* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = node;
    }

    bool deletePatient(int id) {
        if (!head) return false;
        if (head->patientID == id) {
            Patient* toDel = head;
            head = head->next;
            delete toDel;
            return true;
        }
        Patient* prev = head;
        Patient* cur = head->next;
        while (cur) {
            if (cur->patientID == id) {
                prev->next = cur->next;
                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    Patient* retrievePatient(int id) {
        Patient* temp = head;
        while (temp) {
            if (temp->patientID == id) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void displayAll() {
        Patient* temp = head;
        if (!temp) {
            cout << "No patients admitted.\n";
            return;
        }
        cout << "Current Admitted Patients:\n";
        while (temp) {
            cout << "ID:" << temp->patientID << " | " << temp->patientName
                 << " | Date:" << temp->admissionDate << "\n";
            cout << "Treatment: " << temp->treatmentDetails << "\n";
            temp = temp->next;
        }
    }
};

// --- Undo Stack ---
enum PatActionType {P_ADD, P_DELETE};
struct PatAction {
    PatActionType type;
    int id;
    string name;
    string date;
    string treatment;
};

class UndoStack {
    vector<PatAction> st;
public:
    void push(const PatAction &a) { st.push_back(a); }
    bool empty() const { return st.empty(); }
    PatAction top() const { return st.back(); }
    void pop() { st.pop_back(); }
};

// --- Emergency Priority Queue ---
struct EItem {
    int id;
    int priority; // 1 = most urgent
    string name;
    string details;
};

struct ECompare {
    bool operator()(const EItem &a, const EItem &b) const {
        return a.priority > b.priority; // smaller number = higher urgency
    }
};

// --- Circular Queue for round-robin emergency handling ---
class CircularQueue {
    int capacity;
    vector<int> arr;
    int frontIdx, rearIdx, sz;
public:
    CircularQueue(int cap = 10) : capacity(cap), arr(cap), frontIdx(0), rearIdx(-1), sz(0) {}
    bool isFull() const { return sz == capacity; }
    bool isEmpty() const { return sz == 0; }
    bool enqueue(int id) {
        if (isFull()) return false;
        rearIdx = (rearIdx + 1) % capacity;
        arr[rearIdx] = id;
        sz++;
        return true;
    }
    bool dequeue(int &id) {
        if (isEmpty()) return false;
        id = arr[frontIdx];
        frontIdx = (frontIdx + 1) % capacity;
        sz--;
        return true;
    }
    void display() const {
        if (isEmpty()) { cout << "Emergency round-robin queue empty.\n"; return; }
        cout << "Round-robin patient IDs: ";
        for (int i = 0, idx = frontIdx; i < sz; ++i, idx = (idx + 1) % capacity) cout << arr[idx] << " ";
        cout << "\n";
    }
};

// --- Polynomial Linked List for Billing ---
struct Term {
    int coeff;
    int pow;
    Term* next;
    Term(int c, int p): coeff(c), pow(p), next(nullptr) {}
};

class Polynomial {
public:
    Term* head;
    Polynomial(): head(nullptr) {}
    void insertTerm(int coeff, int pow) {
        Term* node = new Term(coeff, pow);
        if (!head || head->pow < pow) {
            node->next = head;
            head = node;
            return;
        }
        Term* temp = head;
        while (temp->next && temp->next->pow >= pow) temp = temp->next;
        node->next = temp->next;
        temp->next = node;
    }
    bool equals(const Polynomial &other) const {
        Term* a = head;
        Term* b = other.head;
        while (a && b) {
            if (a->pow != b->pow || a->coeff != b->coeff) return false;
            a = a->next; b = b->next;
        }
        return (a == nullptr && b == nullptr);
    }
    void display() const {
        if (!head) { cout << "0\n"; return; }
        Term* temp = head;
        while (temp) {
            cout << temp->coeff << "x^" << temp->pow;
            temp = temp->next;
            if (temp) cout << " + ";
        }
        cout << "\n";
    }
};

// --- Postfix Evaluation for Inventory (basic) ---
int evaluatePostfix(const string &expr) {
    stack<int> s;
    for (size_t i = 0; i < expr.length(); ++i) {
        char ch = expr[i];
        if (ch == ' ') continue;
        if (isdigit(ch)) {
            int num = 0;
            while (i < expr.length() && isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            i--;
            s.push(num);
        } else {
            if (s.size() < 2) return INT_MIN;
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            int res = 0;
            if (ch == '+') res = a + b;
            else if (ch == '-') res = a - b;
            else if (ch == '*') res = a * b;
            else if (ch == '/') {
                if (b == 0) return INT_MIN;
                res = a / b;
            } else return INT_MIN;
            s.push(res);
        }
    }
    if (s.size() != 1) return INT_MIN;
    return s.top();
}

// --- Hospital System Class ---
class HospitalSystem {
public:
    PatientList patients;
    UndoStack undo;
    priority_queue<EItem, vector<EItem>, ECompare> emergencyPQ;
    CircularQueue rrQueue;
    Polynomial billA, billB;
    int nextPatientID;

    HospitalSystem(): rrQueue(20), nextPatientID(1) {}

    void addPatientRecord(const string &name, const string &date, const string &treatment, int priorityForEmergency = 5) {
        int id = nextPatientID++;
        patients.insertPatient(id, name, date, treatment);
        PatAction act{P_ADD, id, name, date, treatment};
        undo.push(act);
        // add to emergency structures
        emergencyPQ.push(EItem{id, priorityForEmergency, name, treatment});
        rrQueue.enqueue(id);
        cout << "Patient admitted with ID " << id << "\n";
    }

    void undoAdmission() {
        if (undo.empty()) { cout << "Nothing to undo.\n"; return; }
        PatAction a = undo.top(); undo.pop();
        if (a.type == P_ADD) {
            bool ok = patients.deletePatient(a.id);
            if (ok) cout << "Undo: removed patient ID " << a.id << "\n";
            else cout << "Undo failed: patient not found.\n";
        } else if (a.type == P_DELETE) {
            patients.insertPatient(a.id, a.name, a.date, a.treatment);
            cout << "Undo: restored patient ID " << a.id << "\n";
        }
    }

    void manageEmergencyQueuePriority() {
        if (emergencyPQ.empty()) { cout << "No emergency patients.\n"; return; }
        cout << "Processing emergency patients by priority:\n";
        while (!emergencyPQ.empty()) {
            EItem it = emergencyPQ.top(); emergencyPQ.pop();
            cout << "Handling ID " << it.id << " (" << it.name << ") - Priority " << it.priority << "\n";
            patients.deletePatient(it.id);
        }
    }

    void manageEmergencyQueueRoundRobin(int cycles = 1) {
        cout << "Round-robin emergency processing (" << cycles << " cycles):\n";
        for (int c = 0; c < cycles; ++c) {
            int id;
            if (!rrQueue.dequeue(id)) { cout << "No more patients in round-robin.\n"; return; }
            Patient* p = patients.retrievePatient(id);
            if (p) {
                cout << "Cycle " << (c+1) << ": Attending ID " << id << " - " << p->patientName << "\n";
            } else {
                cout << "Cycle " << (c+1) << ": Patient ID " << id << " already processed or discharged.\n";
            }
        }
    }

    void calculateBilling() {
        cout << "Billing A: "; billA.display();
        cout << "Billing B: "; billB.display();
        if (billA.equals(billB)) cout << "Billing records match.\n";
        else cout << "Billing records differ.\n";
    }

    void evaluateInventoryExpression(const string &postfixExpr) {
        int result = evaluatePostfix(postfixExpr);
        if (result == INT_MIN) {
            cout << "Invalid postfix expression or error (like divide by zero).\n";
        } else {
            cout << "Inventory calculation result: " << result << "\n";
        }
    }
};

// --- Demo main ---
int main() {
    HospitalSystem hs;

    // Sample admissions
    hs.addPatientRecord("Ravi Kumar", "01/09/2025", "Appendicitis - surgery", 1);
    hs.addPatientRecord("Meera Bose", "02/09/2025", "Fracture - cast", 3);
    hs.addPatientRecord("Ajay Das", "03/09/2025", "Fever & observation", 4);

    cout << "\nAll patients:\n";
    hs.patients.displayAll();

    cout << "\nUndo last admission:\n";
    hs.undoAdmission();

    cout << "\nAfter undo:\n";
    hs.patients.displayAll();

    cout << "\nEmergency priority processing:\n";
    hs.manageEmergencyQueuePriority();

    cout << "\nRemaining patients:\n";
    hs.patients.displayAll();

    cout << "\nRound-robin demo:\n";
    hs.rrQueue.display();
    hs.manageEmergencyQueueRoundRobin(2);

    // Billing samples
    hs.billA.insertTerm(200, 2); // 200x^2 (e.g., surgery cost factor)
    hs.billA.insertTerm(50, 1);
    hs.billB.insertTerm(200, 2);
    hs.billB.insertTerm(50, 1);

    cout << "\nBilling comparison:\n";
    hs.calculateBilling();

    // Inventory postfix evaluation demo
    string expr = "10 5 + 2 *"; // (10 + 5) * 2 = 30
    cout << "\nInventory postfix expression: " << expr << "\n";
    hs.evaluateInventoryExpression(expr);

    return 0;
}
