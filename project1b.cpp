#include <iostream>
#include <fstream>
#include<string>
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
    int** adjacencyList;  // 2D array to store adjacency list

    // Constructor
    Grid(int n) : size(n)
    {
        // Allocate memory for nodes and adjacency list
        nodes = new GraphNode * [n * n];
        adjacencyList = new int* [n * n];
        for (int i = 0; i < n * n; i++)
        {
            nodes[i] = new GraphNode(i);
            adjacencyList[i] = new int[n * n];
            // Initialize adjacency list to 0
            for (int j = 0; j < n * n; j++)
            {
                adjacencyList[i][j] = 0;  // Initialize all values to 0
            }
        }
    }

    // Destructor
    ~Grid()
    {
        // Deallocate memory for nodes and adjacency list
        for (int i = 0; i < size * size; i++)
        {
            delete nodes[i];
            delete[] adjacencyList[i];
        }
        delete[] nodes;
        delete[] adjacencyList;
    }

    // Add edge between two nodes
    void addEdge(int from, int to)
    {
        if (from >= 0 && from < size * size && to >= 0 && to < size * size)
        {
            // Add edge to graph nodes
            nodes[from]->addEdge(to);
            nodes[to]->addEdge(from);
            // Update adjacency list
            adjacencyList[from][to] = 1;
            adjacencyList[to][from] = 1;
        }
    }

    // Print adjacency list (for debugging)
    void printAdjacencyList()
    {
        cout << "Adjacency List:" << endl;
        for (int i = 0; i < size * size; ++i)
        {
            cout << "Node " << i << " connects to:";
            for (int j = 0; j < size * size; ++j)
            {
                if (adjacencyList[i][j] == 1)
                {
                    cout << j << " ";
                }
            }
            cout << endl;
        }
    }

    // Print connections of each node (for debugging)
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

    // Print visual grid layout (for debugging)
    void printVisualGrid()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << (i * size + j);
                //it is to display the link more visibly for horizontal
                if (j != size - 1)
                {
                    if (j > 9) 
                    {
                        cout << "--";
                    }
                    else
                    {
                        cout << "   --   ";
                    }
                  
                }
            }
            cout << endl;
            // for vertical connections.
            if (i != size - 1)
            {
                for (int k = 0; k < size; k++)
                {
                    cout << "|" << "\t ";
                }
                cout<< endl;
            }
        }
    }
};


void writeDataToFile() {
    ofstream file("project1.txt");
    int T, N, I, R, O, location, orderLocation, deliveryTimeLimit;
    string restaurantName, orderName;

    cout << "Enter the number of test cases: ";
    cin >> T;
    file << T << "\n";

    for (int i = 0; i < T; ++i) {
        cout << "Test Case " << i + 1 << ":" << endl;
        cout << "Enter grid size (N), number of riders (I), and number of restaurants (R): ";
        cin >> N >> I >> R;
        file << N << " " << I << " " << R << "\n";

        // Create Grid here
        int extreme = N * N;
        if (N > extreme || N <= 0) {
            cout << "Invalid input: Grid size must be a positive integer and within limit." << endl;
            return;
        }

        Grid cityGrid(N);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int current = i * N + j;
                if (j < N - 1) cityGrid.addEdge(current, current + 1);
                if (i < N - 1) cityGrid.addEdge(current, current + N);
            }
        }

        cout << "Visual Grid Layout (Node Indices):" << endl;
        cityGrid.printVisualGrid();

        cout << endl << "Node Connections:" << endl;
        cityGrid.printAdjacencyList();


        for (int j = 0; j < R; ++j) {
            cout << "Restaurant " << j + 1 << ":" << endl;
            cout << "Enter restaurant name, location, and number of orders: ";
            cin.ignore(); // Clears the input buffer
            getline(cin, restaurantName);
            cin >> location >> O;
            file << restaurantName << " " << location << " " << O << "\n";

            for (int k = 0; k < O; ++k) {
                cout << "Order " << k + 1 << ":" << endl;
                cout << "Enter order name, order location, and delivery time limit: ";
                cin.ignore(); // Clears the input buffer
                getline(cin, orderName);
                cin >> orderLocation >> deliveryTimeLimit;
                file << orderName << " " << orderLocation << " " << deliveryTimeLimit << "\n";
            }
        }
    }

    file.close();
    cout << "Data successfully written to project1.txt." << endl;
}



//---------------------------------------------------------------------------------------------
//---------------------------------------------QUEUE--------------------------------------
//                      ___________________    _________________ 
//                      |     data (int)                    |    |     data (int)               |
//front -------->|     aerial_root (bool)      |    |     aerial_root (bool) |  <------------  rear
//                      |     node* next------------|->|     node* next---------|--->NULL
//                      -------------------------------    ----------------------------



class Queue {
    ListNode* front;
    ListNode* rear;
public:
    Queue() 
    {
        front = NULL;
        rear = NULL;
    }
    // enqueue () Inserts the element at the rear of the queue.
    void enqueue(int value) {
        ListNode* newNode = new ListNode(value);
        newNode->id = value;
        newNode->next = NULL;
        if ((front == NULL) && (rear == NULL)) 
        {
            front = newNode;
            rear = newNode;
        }
        else 
        {
            rear->next = newNode;
            rear = newNode;
        }
    }
    void dequeue() 
    {
        if (front == NULL) 
        {
            cout << "List is empty" << endl;
        }
        else if (front == rear) 
        {
            ListNode* p = front;
            front = rear = NULL;
            delete p;
        }
        else 
        {
            ListNode* p = front;
            front = front->next;
            delete p;
        }
    }
    //Front() Returns the value of the element at front of the queue.
    int Front() 
    {
        return front->id;
    }
    //isEmpty () Returns True if the queue is empty else returns False.
    bool isEmpty() 
    {
        if (front == NULL) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
};
class Dijkstra_algorithm
{
public:
    int size;
    int** adjacencyMatrix;
    int source;

    Dijkstra_algorithm(int n, int** adjMatrix)
    {
        size = n;
        adjacencyMatrix = adjMatrix;
        source = 0; // Default source node
    }

    // Function to implement Dijkstra's algorithm
    void dijkstraShortestPath()
    {
        // Create arrays for distances and visited nodes
        int* distance = new int[size];
        bool* visited = new bool[size];

        // Initialize distances and visited arrays
        for (int i = 0; i < size; ++i) {
            distance[i] = INT_MAX;
            visited[i] = false;
        }

        // Distance of source node from itself is always 0
        distance[source] = 0;

        // Main loop of Dijkstra's algorithm
        for (int i = 0; i < size - 1; ++i) {
            // Find the vertex with minimum distance
            int minDistance = INT_MAX;
            int minIndex;
            for (int j = 0; j < size; ++j) {
                if (!visited[j] && distance[j] <= minDistance) {
                    minDistance = distance[j];
                    minIndex = j;
                }
            }

            // Mark the selected vertex as visited
            visited[minIndex] = true;

            // Update distance values of adjacent vertices
            for (int k = 0; k < size; ++k) {
                if (!visited[k] && adjacencyMatrix[minIndex][k] && distance[minIndex] != INT_MAX &&
                    distance[minIndex] + adjacencyMatrix[minIndex][k] < distance[k]) {
                    distance[k] = distance[minIndex] + adjacencyMatrix[minIndex][k];
                }
            }
        }

        // Print the shortest distances from source node to all other nodes
        cout << "Shortest distances from source node " << source << ":" << endl;
        for (int i = 0; i < size; ++i) {
            cout << "Node " << i << ": " << distance[i] << endl;
        }

        // Free memory
        delete[] distance;
        delete[] visited;
    }
};


int main()
{

    int choice;
    cout << "Menu:\n";
    cout << "1. Input Data and Write to File\n";
    cout << "2. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        writeDataToFile();
        // Create Dijkstra_algorithm object and run Dijkstra's algorithm
        /*Dijkstra_algorithm dijkstra(size, adjacencyMatrix);
        dijkstra.dijkstraShortestPath();*/
        break;
    case 2:
        cout << "Exiting program.\n";
        return 0;
    default:
        cout << "Invalid choice.\n";
        return 1;
    }
    return 0;
}

