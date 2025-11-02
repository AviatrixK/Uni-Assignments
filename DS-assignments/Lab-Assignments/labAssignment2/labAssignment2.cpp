#include <bits/stdc++.h>
using namespace std;

// Student-style implementation of Customer Support Ticket System
// Covers: singly linked list (TicketList), stack (UndoStack), priority queue (PriorityQueue),
// circular queue (CircularQueue), and polynomial linked list (BillingHistory).

// --- Ticket ADT ---
struct Ticket {
    int ticketID;
    string customerName;
    string issueDescription;
    int priority; // 1 = highest urgency
    Ticket* next;
    Ticket(int id, const string &name, const string &issue, int pr)
        : ticketID(id), customerName(name), issueDescription(issue), priority(pr), next(nullptr) {}
};

// --- Singly Linked List for Tickets ---
class TicketList {
public:
    Ticket* head;
    TicketList() : head(nullptr) {}

    // Insert at end
    void insertTicket(int id, const string &name, const string &issue, int pr) {
        Ticket* node = new Ticket(id, name, issue, pr);
        if (!head) {
            head = node;
            return;
        }
        Ticket* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = node;
    }

    // Delete by TicketID
    bool deleteTicket(int id) {
        if (!head) return false;
        if (head->ticketID == id) {
            Ticket* toDel = head;
            head = head->next;
            delete toDel;
            return true;
        }
        Ticket* prev = head;
        Ticket* cur = head->next;
        while (cur) {
            if (cur->ticketID == id) {
                prev->next = cur->next;
                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    // Retrieve by TicketID
    Ticket* retrieveTicket(int id) {
        Ticket* temp = head;
        while (temp) {
            if (temp->ticketID == id) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void displayAll() {
        Ticket* temp = head;
        if (!temp) {
            cout << "No tickets in the system.\n";
            return;
        }
        cout << "Current Tickets:\n";
        while (temp) {
            cout << "ID:" << temp->ticketID << " | " << temp->customerName << " | Priority:" << temp->priority << "\n";
            cout << "Issue: " << temp->issueDescription << "\n";
            temp = temp->next;
        }
    }
};

// --- Undo Stack ---
enum ActionType {ADD, DELETE};
struct Action {
    ActionType type;
    // For simplicity store full ticket snapshot for undo
    int id;
    string name;
    string issue;
    int priority;
};

class UndoStack {
    vector<Action> st;
public:
    void push(const Action &a) { st.push_back(a); }
    bool empty() const { return st.empty(); }
    Action top() const { return st.back(); }
    void pop() { st.pop_back(); }
};

// --- Priority Queue for urgent tickets ---
struct PQItem {
    int id;
    int priority;
    string name;
    string issue;
};

struct PQCompare {
    bool operator()(const PQItem &a, const PQItem &b) const {
        // smaller priority value = higher urgency
        return a.priority > b.priority;
    }
};

// --- Circular Queue for round-robin processing ---
class CircularQueue {
    int capacity;
    vector<int> arr; // store ticket IDs for processing
    int frontIdx, rearIdx, size;
public:
    CircularQueue(int cap = 10) : capacity(cap), arr(cap), frontIdx(0), rearIdx(-1), size(0) {}
    bool isFull() const { return size == capacity; }
    bool isEmpty() const { return size == 0; }
    bool enqueue(int ticketID) {
        if (isFull()) return false;
        rearIdx = (rearIdx + 1) % capacity;
        arr[rearIdx] = ticketID;
        size++;
        return true;
    }
    bool dequeue(int &ticketID) {
        if (isEmpty()) return false;
        ticketID = arr[frontIdx];
        frontIdx = (frontIdx + 1) % capacity;
        size--;
        return true;
    }
    void display() const {
        if (isEmpty()) { cout << "Round-robin queue empty.\n"; return; }
        cout << "Round-robin queue IDs: ";
        for (int i = 0, idx = frontIdx; i < size; ++i, idx = (idx + 1) % capacity) cout << arr[idx] << " ";
        cout << "\n";
    }
};

// --- Polynomial Linked List for Billing History ---
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
        if (!head || head->pow < pow) { // keep terms in descending pow
            node->next = head;
            head = node;
            return;
        }
        Term* temp = head;
        while (temp->next && temp->next->pow >= pow) temp = temp->next;
        node->next = temp->next;
        temp->next = node;
    }

    // Compare two polynomials (simple equality check)
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

// --- Customer Support System combining everything ---
class SupportSystem {
public:
    TicketList tickets;
    UndoStack undo;
    priority_queue<PQItem, vector<PQItem>, PQCompare> pq;
    CircularQueue rrQueue;
    Polynomial billingA, billingB;
    int nextTicketID;

    SupportSystem(): rrQueue(20), nextTicketID(1) {}

    void addTicketRecord(const string &name, const string &issue, int priority) {
        int id = nextTicketID++;
        tickets.insertTicket(id, name, issue, priority);
        Action act{ADD, id, name, issue, priority};
        undo.push(act);
        // also push into priority queue for urgent handling
        pq.push(PQItem{id, priority, name, issue});
        // enqueue to round-robin as well
        rrQueue.enqueue(id);
        cout << "Ticket added with ID " << id << "\n";
    }

    void undoTicketOperation() {
        if (undo.empty()) { cout << "Nothing to undo.\n"; return; }
        Action a = undo.top();
        undo.pop();
        if (a.type == ADD) {
            bool ok = tickets.deleteTicket(a.id);
            if (ok) cout << "Undo: removed ticket ID " << a.id << "\n";
            else cout << "Undo failed: ticket not found.\n";
        } else if (a.type == DELETE) {
            tickets.insertTicket(a.id, a.name, a.issue, a.priority);
            cout << "Undo: restored ticket ID " << a.id << "\n";
        }
    }

    void processPriorityTickets() {
        if (pq.empty()) { cout << "No priority tickets.\n"; return; }
        cout << "Processing priority tickets:\n";
        while (!pq.empty()) {
            PQItem it = pq.top(); pq.pop();
            cout << "Processing ID " << it.id << " (Priority " << it.priority << ") - " << it.name << "\n";
            // simulate processing by removing from ticket list if present
            tickets.deleteTicket(it.id);
        }
    }

    void processRoundRobinTickets(int cycles = 1) {
        cout << "Round-robin processing (" << cycles << " cycles):\n";
        for (int c = 0; c < cycles; ++c) {
            int id;
            if (!rrQueue.dequeue(id)) { cout << "No tickets left in round-robin.\n"; return; }
            Ticket* t = tickets.retrieveTicket(id);
            if (t) {
                cout << "Cycle " << (c+1) << ": Processing ID " << id << " - " << t->customerName << "\n";
                // after processing, we can re-enqueue if not resolved (simple simulation: do not re-enqueue)
            } else {
                cout << "Cycle " << (c+1) << ": Ticket ID " << id << " already processed or removed.\n";
            }
        }
    }

    void compareBillingHistory() {
        cout << "Billing A: "; billingA.display();
        cout << "Billing B: "; billingB.display();
        if (billingA.equals(billingB)) cout << "Billing histories are identical.\n";
        else cout << "Billing histories differ.\n";
    }
};

// --- Simple demo main with student-style input/output ---
int main() {
    SupportSystem sys;
    // Sample data to show functionality
    sys.addTicketRecord("Alice", "Cannot login", 2);
    sys.addTicketRecord("Bob", "Payment failed", 1);
    sys.addTicketRecord("Charlie", "Bug in UI", 3);

    cout << "\nAll tickets:\n";
    sys.tickets.displayAll();

    cout << "\nUndo last op:\n";
    sys.undoTicketOperation();
    cout << "\nAfter undo:\n";
    sys.tickets.displayAll();

    cout << "\nProcess priority tickets:\n";
    sys.processPriorityTickets();
    cout << "\nRemaining tickets:\n";
    sys.tickets.displayAll();

    cout << "\nRound-robin demo:\n";
    sys.rrQueue.display();
    sys.processRoundRobinTickets(2);

    // Polynomial billing demo
    sys.billingA.insertTerm(100, 2); // 100x^2
    sys.billingA.insertTerm(50, 1);
    sys.billingB.insertTerm(100, 2);
    sys.billingB.insertTerm(50, 1);
    cout << "\nCompare billing histories:\n";
    sys.compareBillingHistory();

    return 0;
}
