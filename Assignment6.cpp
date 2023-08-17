#include <iostream>
#include <string>
using namespace std;
#define MAX_SIZE 1000

class Queue
{
private:
    int myqueue[MAX_SIZE], front, rear;

public:
    Queue()
    {
        front = -1;
        rear = -1;
    }

    bool isFull()
    {
        if (front == 0 && rear == MAX_SIZE - 1)
        {
            return true;
        }
        return false;
    }

    bool isEmpty()
    {
        if (front == -1)
            return true;
        else
            return false;
    }

    void enQueue(int value)
    {
        if (isFull())
        {
            cout << endl
                 << "Queue is full!!";
        }
        else
        {
            if (front == -1)
                front = 0;
            rear++;
            myqueue[rear] = value;
        }
    }
    int deQueue()
    {
        int value;
        if (isEmpty())
        {
            cout << "Queue is empty!!" << endl;
            return (-1);
        }
        else
        {
            value = myqueue[front];
            if (front >= rear)
            {
                front = -1;
                rear = -1;
            }
            else
            {
                front++;
            }
            return (value);
        }
    }

    void displayQueue()
    {
        int i;
        if (isEmpty())
        {
            cout << endl
                 << "Queue is Empty!!" << endl;
        }
        else
        {
            cout << endl
                 << "Front = " << front;
            cout << endl
                 << "Queue elements : ";
            for (i = front; i <= rear; i++)
                cout << myqueue[i] << " ";
        }
    }
};

class Node
{
    int dest;
    Node *next;
    friend class Graph;

public:
    Node(int d = 0)
    {
        dest = d;
        next = NULL;
    }
};

class Graph
{
    int v;
    int e;
    Node **header;
    bool *visit;
    string *names;

public:
    Graph(int vert = 0, int edg = 0)
    {
        v = vert;
        e = edg;
        header = new Node *[v];
        visit = new bool[v];
        names = new string[v];
        for (int i = 0; i < v; i++)
        {
            header[i] = NULL;
            visit[i] = 0;
            names[i] = "";
        }
    }
    int search(string key)
    {
        for (int i = 0; i < v; i++)
        {
            if (names[i] == key)
            {
                return i;
            }
        }
        // return -1;
    }
    void reset_visit()
    {
        for (int i = 0; i < v; i++)
        {
            visit[i] = 0;
        }
    }
    void accept()
    {
        cout << "Enter the name of all locations:\n";
        for (int i = 0; i < v; i++)
        {
            cout << "Loacation " << i + 1 << ": ";
            // cin.ignore();
            // getline(cin,names[i]);
            cin >> names[i];
        }
        for (int i = 0; i < e; i++)
        {
            // for (int i = 0; i < v; i++)
            // {
            //     cout<<"Loacation "<<i+1<<": ";
            //     cout<<names[i]<<" ";
            // }

            int src, des;
            string pos1, pos2;
            cout << "Enter Location 1: ";
            cin >> pos1;
            // cin.ignore();
            // getline(cin, pos1);
            cout << "Enter Location 2: ";
            cin >> pos2;
            // cin.ignore();
            // getline(cin, pos1);
            src = search(pos1);
            des = search(pos2);
            cout << pos1 << src << endl;
            cout << pos2 << des << endl;
            Node *p = new Node(des);
            Node *q = new Node(src);
            if (header[src] == NULL)
            {
                header[src] = p;
            }
            else
            {

                Node *temp = header[src];
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = p;
            }
            if (header[des] == NULL)
            {
                header[des] = q;
            }
            else
            {

                Node *temp = header[des];
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = q;
            }
        }
    }

    void displist(int ind)
    {
        Node *temp = header[ind];
        while (temp != NULL)
        {
            cout << names[temp->dest] << "-->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
    void display()
    {
        for (int i = 0; i < v; i++)
        {
            cout << names[i] << " :";
            displist(i);
        }
    }
    void DFS(int v)
    {
        cout << names[v] << " ";
        visit[v] = 1;
        Node *temp = header[v];
        while (temp != NULL)
        {
            int t = temp->dest;
            if (visit[t] == 0)
            {
                DFS(t);
            }
            temp = temp->next;
        }
    }

    void BFS(int v)
    {
        Queue q1;
        visit[v] = 1;
        q1.enQueue(v);
        cout << names[v] << " ";
        while (!q1.isEmpty())
        {
            Node *temp = header[v];
            if (visit[v] == 0)
            {
                cout << names[v] << " ";
                visit[v] = 1;
            }
            while (temp != NULL)
            {
                if (visit[temp->dest] == 0)
                {
                    q1.enQueue(temp->dest);
                    visit[temp->dest] = 1;
                    cout << names[temp->dest] << " ";
                }
                temp = temp->next;
            }
            q1.deQueue();
            v++;
        }
    }
};
int main()
{
    int a, b;
    cout << "Enter number of vertices: ";
    cin >> a;
    cout << "Enter number of edges: ";
    cin >> b;
    Graph g1(a, b);
    g1.accept();
    g1.display();
    cout<<"DFS : ";
    g1.DFS(0);
    g1.reset_visit();
    cout <<"\nBFS : ";
    g1.BFS(0);
    return 0;
}

// Enter number of vertices: 7
// Enter number of edges: 11
// Enter Vertex 1: 0
// Enter Vertex 2: 1
// Enter Vertex 1: 0
// Enter Vertex 2: 3
// Enter Vertex 1: 3
// Enter Vertex 2: 1
// Enter Vertex 1: 3
// Enter Vertex 2: 4
// Enter Vertex 1: 3
// Enter Vertex 2: 2
// Enter Vertex 1: 1
// Enter Vertex 2: 2
// Enter Vertex 1: 1
// Enter Vertex 2: 6
// Enter Vertex 1: 1
// Enter Vertex 2: 5
// Enter Vertex 1: 5
// Enter Vertex 2: 2
// Enter Vertex 1: 4
// Enter Vertex 2: 2
// Enter Vertex 1: 4
// Enter Vertex 2: 6

// Enter number of vertices: 7
// Enter number of edges: 11
// Enter the name of all locations:
// Loacation 1: A
// Loacation 2: B
// Loacation 3: C
// Loacation 4: D
// Loacation 5: E
// Loacation 6: F
// Loacation 7: G
// Enter Location 1: A
// Enter Location 2: B
// Enter Location 1: A
// Enter Location 2: D
// Enter Location 1: D
// Enter Location 2: B
// Enter Location 1: D
// Enter Location 2: E
// Enter Location 1: D
// Enter Location 2: C
// Enter Location 1: B
// Enter Location 2: C
// Enter Location 1: B
// Enter Location 2: G
// Enter Location 1: B
// Enter Location 2: F
// Enter Location 1: F
// Enter Location 2: C
// Enter Location 1: E
// Enter Location 2: C
// Enter Location 1: E
// Enter Location 2: G
// A :B-->D-->NULL
// B :A-->D-->C-->G-->F-->NULL
// C :D-->B-->F-->E-->NULL
// D :A-->B-->E-->C-->NULL
// E :D-->C-->G-->NULL
// F :B-->C-->NULL
// G :B-->E-->NULL
// A B D E C F G
// A B D C G F E