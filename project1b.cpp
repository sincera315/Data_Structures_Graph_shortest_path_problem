#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <limits> 
using namespace std;

// it creates nodes to form linked list which will further be used to connect nodes to indexes of arrays to create an
// adjacency list. Here nodeid creates a unique id for each time to works.

//--------------------------------------------------------------------------------
//-----------------------------LINKED LIST---------------------------------
//      node1:                                                node2:
//      _________________   __________________________ 
//      |     id (int)                   |    |     id (int)                   |
//      |      (vertex value)      |    |     (vertex value)        |
//      |     node* next--------|->|     node* next---------|--->NULL
//      --------------------------      --------------------------
class ListNode {
public:
    int id;
    ListNode* next;
    ListNode(int nodeId) : id(nodeId), next(NULL) {}// MIL(Member Initialization List.) 
};

//---------------------------------------------------------------------------------------------
//---------------------------------------------QUEUE--------------------------------------
//                      ___________________    _________________ 
//                      |     id (int) (vertex)          |    |     id (int)(vertex)      |
//front -------->|                                        |    |                                   |  <------------  rear
//                      |     node* next------------|->|     node* next---------|--->NULL
//                      -------------------------------    ----------------------------
//---------------------------------------------------------------------------------------------

class Queue
{
    ListNode* front;
    ListNode* rear;
public:
    //constructor.
    Queue()
    {
        front = NULL;
        rear = NULL;
    }

    //to add values.
    void enqueue(int value)
    {
        ListNode* newNode = new ListNode(value);
        newNode->id = value;
        newNode->next = NULL;
        // if there are no starting and ending nodes than  create them.
        if ((front == NULL) && (rear == NULL))
        {
            front = newNode;
            rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // to delete values
    void dequeue()
    {
        // list is empty.
        if (front == NULL)
        {
            cout << "List is empty" << endl;
        }
        // if there is a front node but no end node then we create the rear node.
        else if (front == rear)
        {
            ListNode* p = front;
            front = rear = NULL;
            delete p;
        }
        // than add next node in it.
        else
        {
            ListNode* p = front;
            front = front->next;
            delete p;
        }
    }

    // the vertex value will be stored in front data as it helps in graph traversal understanding
    int Front() {
        return front->id;
    }

    //if no front node is made then it will return null.
    bool isEmpty() {
        return (front == NULL);
    }
};

// it is the function which will help to create a graph using the node class and adding their nodes by connecting them to several other nodes.
class GraphNode
{
public:
    int id;
    ListNode* head;
    // parameterized constructor.
    GraphNode(int nodeId) : id(nodeId), head(NULL) {} //MIL (Member Initialization List).

    // to add the values to each edge that attaches vertex.
    void addEdge(int to)
    {
        ListNode* newNode = new ListNode(to);
        newNode->next = head;
        head = newNode;
    }

    //Destructor.
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

// Logic: Grid(double pointer calling) --> GraphNode(single pointer calling) --> ListNode(Node is formed here)
class Grid
{
public:
    int size;
    GraphNode** nodes;
    int** adjacencyList;
    // parameterized constructor to ensure that memory is allocated for the size user asked for
    Grid(int n) : size(n)
    {
        nodes = new GraphNode * [n * n];
        adjacencyList = new int* [n * n];
        for (int i = 0; i < n * n; i++)
        {
            nodes[i] = new GraphNode(i);
            adjacencyList[i] = new int[n * n];
            for (int j = 0; j < n * n; j++)
            {
                adjacencyList[i][j] = 0;
            }
        }
    }

    //Destructor. to avoid memory leaks
    ~Grid()
    {
        for (int i = 0; i < size * size; i++)
        {
            delete nodes[i];
            delete[] adjacencyList[i];
        }
        delete[] nodes;
        delete[] adjacencyList;
    }

    // it adds edges to make connections in adjacency list.
    void addEdge(int from, int to)
    {
        if (from >= 0 && from < size * size && to >= 0 && to < size * size)
        {
            nodes[from]->addEdge(to);
            nodes[to]->addEdge(from);
            adjacencyList[from][to] = 1;
            adjacencyList[to][from] = 1;
        }
    }
    // it prints the Adjacency list.
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
    // for printing the connections
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


    //   printing the entire grid.
    void printVisualGrid()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << (i * size + j);
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
            if (i != size - 1)
            {
                for (int k = 0; k < size; k++)
                {
                    cout << "|" << "\t ";
                }
                cout << endl;
            }
        }
    }
    //Applying the Dijkstras algorithm to find the shortest path.
    int dijkstraShortestPath(int source, int target)
    {
        int* distance = new int[size * size];
        bool* visited = new bool[size * size];
        int* parent = new int[size * size]; // To store parent vertices for reconstructing the path
        int time = 0; // Initialize time to 0

        for (int i = 0; i < size * size; ++i)
        {
            distance[i] = INT_MAX;
            visited[i] = false;
            parent[i] = -1; // Initialize parent array
        }

        distance[source] = 0;

        Queue q;
        q.enqueue(source);

        while (!q.isEmpty())
        {
            int u = q.Front();
            q.dequeue();

            if (visited[u])
                continue;

            visited[u] = true;

            if (u == target) // Stop the traversal if we reached the target vertex
                break;

            for (ListNode* temp = nodes[u]->head; temp != NULL; temp = temp->next)
            {
                int v = temp->id;
                if (!visited[v] && distance[u] != INT_MAX && distance[u] + 1 < distance[v])
                {
                    distance[v] = distance[u] + 1; // Since each edge weight is 1
                    parent[v] = u; // Update parent array
                    q.enqueue(v);
                }
            }
        }

        // Reconstruct the shortest path and count the number of edges along it
        int current = target;
        while (parent[current] != -1)
        {
            current = parent[current];
            time++;
        }

        delete[] distance;
        delete[] visited;
        delete[] parent;

        return time; // Return time taken (total number of connections along the shortest path)
    }

};

void writeDataToFile()
{
    ofstream file("project1.txt");
    int T, N, I, R, O, location, orderLocation, deliveryTimeLimit, totalTime = 0;
    string restaurantName, orderName;

    cout << "Enter the number of test cases: ";
    cin >> T;
    file << T << endl;

    for (int i = 0; i < T; ++i)
    {
        cout << "Test Case " << i + 1 << ":" << endl;
        cout << "Enter grid size (N), number of riders (I), and number of restaurants (R): ";
        cin >> N >> I >> R;
        file << N << " " << I << " " << R << endl;

        int extreme = N * N;
        if (N > extreme || N <= 0)
        {
            cout << "Invalid input: Grid size must be a positive integer and within limit." << endl;
            return;
        }

        Grid cityGrid(N);

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int current = i * N + j;
                if (j < N - 1) cityGrid.addEdge(current, current + 1);
                if (i < N - 1) cityGrid.addEdge(current, current + N);
            }
        }
        cityGrid.printVisualGrid();
        cityGrid.printConnections();


        for (int j = 0; j < R; ++j)
        {
            cout << "Restaurant " << j + 1 << ":" << endl;
            cout << "Enter restaurant name, location, and number of orders: ";
            cin.ignore();
            getline(cin, restaurantName);
            cin >> location >> O;
            file << restaurantName << " " << location << " " << O << endl;

            for (int k = 0; k < O; k++)
            {
                cout << "Order " << k + 1 << ":" << endl;
                cout << "Enter order name, order location, and delivery time limit: ";
                cin.ignore();
                getline(cin, orderName);
                cin >> orderLocation >> deliveryTimeLimit;
                file << orderName << " " << orderLocation << " " << deliveryTimeLimit << endl;
            }
        }
        cout << "Running Dijkstra's algorithm..." << endl;
        // Assuming the last location and order location are needed for Dijkstra's algorithm
        int timePerOrder = cityGrid.dijkstraShortestPath(location, orderLocation); // Get time taken per order
        totalTime += timePerOrder; // Accumulate time for each test case
        cout << "Total time taken to reach destination for test case " << i + 1 << ": " << timePerOrder << endl;

    }
    cout << "Total time taken for all test cases: " << totalTime << endl;
    file.close();
    cout << "Data successfully written to project1.txt." << endl;
}

int main()
{
    int choice;
    cout << "Menu:" << endl;
    cout << "1. Input Data and Write to File" << endl;
    cout << "2. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        writeDataToFile();
        break;
    case 2:
        cout << "Exiting program." << endl;
        return 0;
    default:
        cout << "Invalid choice." << endl;
        return 1;
    }
    return 0;
}
