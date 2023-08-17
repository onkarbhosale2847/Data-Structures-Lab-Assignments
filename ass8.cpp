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
    int *in_arr;

public:
    Graph(int vert = 0, int edg = 0)
    {
        v = vert;
        e = edg;
        header = new Node *[v];
        visit = new bool[v];
        in_arr = new int[v];
        for (int i = 0; i < v; i++)
        {
            header[i] = NULL;
            visit[i] = 0;
            in_arr[i] = 0;
        }
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
        for (int i = 0; i < e; i++)
        {
            int src, des;
            cout << "Enter Source: ";
            cin >> src;
            cout << "Enter Destination: ";
            cin >> des;

            Node *p = new Node(des);
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
        }
    }

    void displist(int ind)
    {
        Node *temp = header[ind];
        while (temp != NULL)
        {
            cout << temp->dest << "-->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
    void display()
    {
        cout << "-------------------------------" << endl;
        for (int i = 0; i < v; i++)
        {
            cout << i << " :";
            displist(i);
        }
        cout << "-------------------------------" << endl;
    }
    void DFS(int v)
    {
        cout << v << " ";
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
        cout << v << " ";
        while (!q1.isEmpty())
        {
            Node *temp = header[v];
            while (temp != NULL)
            {
                if (visit[temp->dest] == 0)
                {
                    q1.enQueue(temp->dest);
                    visit[temp->dest] = 1;
                    cout << temp->dest << " ";
                    q1.deQueue();
                }
                temp = temp->next;
            }
            v++;
        }
    }

    void in_degree()
    {
        for (int i = 0; i < v; i++)
        {
            Node *temp = header[i];
            while (temp != NULL)
            {
                in_arr[temp->dest]++;
                temp = temp->next;
            }
        }
    }

    void print_inarr()
    {
        for (int i = 0; i < v; i++)
        {
            cout << in_arr[i] << " ";
        }
        cout << endl;
    }

    void delete_node(int v)
    {
        header[v] = NULL;
    }
    bool is_empty()
    {
        int count = 0;
        for (int i = 0; i < v; i++)
        {
            if (in_arr[i] == 0)
            {
                count++;
            }
        }
        if (count == v)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    void topo_sort()
    {
        in_degree();
        while (!is_empty())
        {

            for (int i = 0; i < v; i++)
            {
                if (in_arr[i] == 0 && visit[i] == 0)
                {
                    cout << i << " ";
                    Node *temp = header[i];
                    while (temp != NULL)
                    {
                        in_arr[temp->dest]--;
                        temp = temp->next;
                    }
                    visit[i] = 1;
                    delete_node(i);
                }
            }
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
    cout << "TOPOLOGICAL SORT IS: ";
    g1.topo_sort();

    return 0;
}