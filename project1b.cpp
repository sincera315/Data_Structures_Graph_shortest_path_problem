#include <iostream>
#include <fstream>
using namespace std;
//logic: Grid(double pointer calling) --> GraphNode(single pointer calling) --> ListNode(Node is formed here)

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

    GraphNode(int nodeId) : id(nodeId), head(NULL) {}// MIL(Member Initialization List.)

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
        //creating 2D array of nodes using Graph nodes double pointer method.
        nodes = new GraphNode * [n * n];
        for (int i = 0; i < n * n; i++) 
        {
            nodes[i] = new GraphNode(i);
        }
    }

    //destructor to deallocater memory more efficiently and correctly.
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

    void printConnections() 
    {
        for (int i = 0; i < size * size; i++) 
        {
            cout << "Node " << nodes[i]->id << " connects to: ";
            ListNode* current = nodes[i]->head;
            while (current != NULL) 
            {
                cout << current->id << " ";
                current = current->next;
            }
            cout << endl;
        }
    }

    // print in a more graph format.
    void printVisualGrid() 
    {
        for (int i = 0; i < size; i++) 
        {
            for (int j = 0; j < size; j++) 
            {
                cout << (i * size + j) ;
                //for printing connection lines in between nodes.
                if (j != size - 1)
                {
                    cout << "   --   ";
                }
            }
            cout << endl;
            //for printing connection lines vertically between nodes.
            if (i != size - 1)
            {
                cout << "|" << "\t" << " |" << "\t" << "  |" << endl;
            }
            
        }
    }
};

void saveGridToFile(int n, Grid& cityGrid) 
{
    ofstream outFile("project1.txt");
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open output file." << endl;
        exit(1);
    }

    // Write grid size
    outFile << "Grid Size: " << n << " x " << n << endl << endl;

    // Write visual grid layout
    outFile << "Visual Grid Layout (Node Indices):" << endl;
    cityGrid.printVisualGrid(outFile);
    outFile << endl;

    // Write node connections
    outFile << "Node Connections:" << endl;
    cityGrid.printConnections(outFile);

    outFile.close();
}


int main() 
{
    int n;
    cout << "Enter the grid size (N x N): ";
    cin >> n;

    if (cin.fail() || n <= 0) 
    {
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
    cityGrid.printVisualGrid();

    cout << endl<<"Node Connections:" << endl;
    cityGrid.printConnections();

    // Save grid data to file
    saveGridToFile(n, cityGrid);
    return 0;
}



