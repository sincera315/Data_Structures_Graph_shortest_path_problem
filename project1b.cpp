#include <iostream>

using namespace std;

class ListNode {
public:
    int id;
    ListNode* next;

    ListNode(int nodeId) : id(nodeId), next(nullptr) {}
};

class GraphNode {
public:
    int id;
    ListNode* head;

    GraphNode(int nodeId) : id(nodeId), head(nullptr) {}

    void addEdge(int to) {
        ListNode* newNode = new ListNode(to);
        newNode->next = head;
        head = newNode;
    }

    ~GraphNode() {
        ListNode* current = head;
        while (current != nullptr) {
            ListNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

class Grid {
public:
    int size;
    GraphNode** nodes;

    Grid(int n) : size(n) {
        nodes = new GraphNode*[n * n];
        for (int i = 0; i < n * n; i++) {
            nodes[i] = new GraphNode(i);
        }
    }

    ~Grid() {
        for (int i = 0; i < size * size; i++) {
            delete nodes[i];
        }
        delete[] nodes;
    }

    void addEdge(int from, int to) {
        if (from >= 0 && from < size * size && to >= 0 && to < size * size) {
            nodes[from]->addEdge(to);
            nodes[to]->addEdge(from);
        }
    }

    void printConnections() {
        for (int i = 0; i < size * size; i++) {
            cout << "Node " << nodes[i]->id << " connects to: ";
            ListNode* current = nodes[i]->head;
            while (current != nullptr) {
                cout << current->id << " ";
                current = current->next;
            }
            cout << endl;
        }
    }

    void printVisualGrid() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << (i * size + j) << "\t";
            }
            cout << endl;
        }
    }
};

int main() {
    int n;
    cout << "Enter the grid size (N x N): ";
    cin >> n;

    if (cin.fail() || n <= 0) {
        cerr << "Invalid input: Grid size must be a positive integer." << endl;
        return 1;
    }

    Grid cityGrid(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int current = i * n + j;
            if (j < n - 1) cityGrid.addEdge(current, current + 1);
            if (i < n - 1) cityGrid.addEdge(current, current + n);
        }
    }

    cout << "Visual Grid Layout (Node Indices):" << endl;
    cityGrid.printVisualGrid();

    cout << "\nNode Connections:" << endl;
    cityGrid.printConnections();

    return 0;
}
