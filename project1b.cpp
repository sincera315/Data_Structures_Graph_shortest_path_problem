#include <iostream>
#include <fstream>
using namespace std;

// Logic: Grid(double pointer calling) --> GraphNode(single pointer calling) --> ListNode(Node is formed here)
// Now left work is :
//Implement Dijkstra's Algorithm: Write a function to implement Dijkstra's algorithm to find the shortest path from a given source node to all other nodes in the grid.
//Modify Grid Class : Add a method to get the shortest path from a source node to a destination node based on the output of Dijkstra's algorithm.
//Update Main Function : Call the Dijkstra function to find the shortest path, and then print or save the shortest path to the output file.

// it creates nodes to form linked list which will further be used to connect nodes to indexes of arrays to create an
// adjacency list. Here nodeid creates a unique id for each time to works.
class ListNode 
{
public:
    int id;
    ListNode* next;
    ListNode(int nodeId) : id(nodeId), next(NULL) {}// MIL(Member List Initialization.)
};

// it is the function which will help to create a graph using the node class and adding their nodes by connecting them to several other nodes.
class GraphNode 
{
public:
    int id;
    ListNode* head;

    GraphNode(int nodeId) : id(nodeId), head(NULL) {}

    // it will help to add edges to each node by using a linked list connection method(next ptr).
    void addEdge(int to) 
    {
        ListNode* newNode = new ListNode(to);
        newNode->next = head;
        head = newNode;
    }

    //Destructor so that all the allocated memory could be released after use and prevents errors or memory leakages.
    ~GraphNode() 
    {
        ListNode* current = head;
        while (current != NULL) 
        {
            ListNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

class Grid 
{
public:
    int size;
    GraphNode** nodes;

    Grid(int n) : size(n) 
    {
        nodes = new GraphNode * [n * n];
        for (int i = 0; i < n * n; i++) 
        {
            nodes[i] = new GraphNode(i);
        }
    }

    //Destructor so that all the allocated memory could be released after use and prevents errors or memory leakages.
    ~Grid() 
    {
        for (int i = 0; i < size * size; i++) 
        {
            delete nodes[i];
        }
        delete[] nodes;
    }

    void addEdge(int from, int to) 
    {
        if (from >= 0 && from < size * size && to >= 0 && to < size * size) 
        {
            nodes[from]->addEdge(to);
            nodes[to]->addEdge(from);
        }
    }

    void printConnections(ostream& out) 
    {
        for (int i = 0; i < size * size; i++) 
        {
            out << "Node " << nodes[i]->id << " connects to: ";
            ListNode* current = nodes[i]->head;
            while (current != NULL) 
            {
                out << current->id << " ";
                current = current->next;
            }
            out << endl;
        }
    }

    void printVisualGrid(ostream& out)
    {
        for (int i = 0; i < size; i++) 
        {
            for (int j = 0; j < size; j++) 
            {
                out << (i * size + j);
                //it is to display the link more visibly for horizontal
                if (j != size - 1) 
                {
                    out << "   --   ";
                }
            }
            out << endl;
            // for vertical connections.
            if (i != size - 1) 
            {
                out << "|" << "\t" << " |" << "\t" << "  |" << endl;
            }
        }
    }
};

void saveGridToFile(int n, Grid& cityGrid) 
{
    ofstream outFile("project1.txt");
    if (!outFile.is_open()) 
    {
        cerr << "Error: Unable to open output file." << endl;
        exit(1);
    }

    outFile << "Grid Size: " << n << " x " << n << endl << endl;
    outFile << "Visual Grid Layout (Node Indices):" << endl;
    cityGrid.printVisualGrid(outFile);
    outFile << endl;
    outFile << "Node Connections:" << endl;
    cityGrid.printConnections(outFile);

    outFile.close();
}

int main() 
{
    int n;
    cout << "Enter the grid size (N x N): ";
    cin >> n;

    if (cin.fail() || n <= 0) {
        cerr << "Invalid input: Grid size must be a positive integer." << endl;
        return 1;
    }

    Grid cityGrid(n);

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            int current = i * n + j;
            if (j < n - 1) cityGrid.addEdge(current, current + 1);
            if (i < n - 1) cityGrid.addEdge(current, current + n);
        }
    }

    cout << "Visual Grid Layout (Node Indices):" << endl;
    cityGrid.printVisualGrid(cout);

    cout << endl << "Node Connections:" << endl;
    cityGrid.printConnections(cout);

    saveGridToFile(n, cityGrid);

    return 0;
}
