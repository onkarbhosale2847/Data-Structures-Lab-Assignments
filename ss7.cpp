#include <iostream>
using namespace std;

class Graph
{
    int v;
    int e;
    int **header;
    bool *visit;
    int *parent;

public:
    Graph(int vert = 0, int edg = 0)
    {
        v = vert;
        e = edg;
        header = new int *[v];
        visit = new bool[v];
        parent = new int[v];
        for (int i = 0; i < v; i++)
        {
            header[i] = new int[v];
        }
        for (int i = 0; i < v; i++)
        {
            visit[i] = 0;
            parent[i] = i;
            for (int j = 0; j < v; j++)
            {
                header[i][j] = 0;
            }
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
            int src, dest, wt;
            cout << "Enter Source: ";
            cin >> src;
            cout << "Enter Destination: ";
            cin >> dest;
            cout << "Enter Weight: ";
            cin >> wt;
            header[src][dest] = header[dest][src] = wt;
        }
    }
    void display()
    {
        cout << "---------------------------------" << endl;
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {
                cout << header[i][j] << "\t";
            }
            cout << endl;
        }
        cout << "---------------------------------" << endl;
    }

    bool isValid(int u, int v)
    {
        if (u == v)
            return 0;
        if (visit[u] == 0 && visit[v] == 0)
            return 0;
        else if (visit[u] == 1 && visit[v] == 1)
            return 0;
        return 1;
    }

    void prims()
    {
        cout << "--------------PRIM'S ALGORITHM--------------" << endl;
        reset_visit();
        visit[0] = 1;
        int edge_count = 0;
        int mincost = 0;
        int a, b;
        while (edge_count < v - 1)
        {
            int min = 99999,
                a = b = -1;
            for (int i = 0; i < v; i++)
            {
                for (int j = 0; j < v; j++)
                {
                    if (header[i][j] < min)
                    {
                        if (isValid(i, j)) // checks and finds the minimum weight edge among the adjacent vertices of current MST
                        {
                            min = header[i][j];
                            a = i;
                            b = j;
                        }
                    }
                }
            }
            if (a != (-1) && b != (-1))
            {
                cout << "Edge " << edge_count++ << ": (" << a << "," << b << ")\tCost: " << min << endl;
                mincost = mincost + min;
                visit[b] = visit[a] = 1;
            }
        }
        cout << "Minimum cost:" << mincost << endl;
        cout << "--------------------------------------------" << endl;
    }

    int find(int i)
    {
        while (parent[i] != i)
        {
            i = parent[i];
        }
        return i;
    }

    void union1(int i, int j)
    {
        int a = find(i);
        int b = find(j);
        parent[a] = b;
    }

    void kruskal()
    {

        cout << "--------------KRUSKAL'S ALGORITHM-----------" << endl;
        int mincost = 0; // Cost of min MST.

        int edge_count = 0;
        int a, b;
        while (edge_count < v - 1)
        {
            int min = 99999;
            a = b = -1;
            for (int i = 0; i < v; i++)
            {
                for (int j = 0; j < v; j++)
                {
                    if (find(i) != find(j) && header[i][j] < min) // checks and finds the minimum weight edge w/o cycle
                    {
                        min = header[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
            union1(a, b);
            cout << "Edge " << edge_count++ << ": (" << a << "," << b << ")\tCost:" << min << endl;
            mincost += min;
        }
        cout << "Minimum cost:" << mincost << endl;
        cout << "--------------------------------------------" << endl;
    }
};

int main()
{
    int verti, desti;
    cout << "Enter number of vertices: ";
    cin >> verti;
    cout << "Enter number of edges: ";
    cin >> desti;
    Graph g(verti, desti);
    g.accept();
    g.display();
    g.prims();
    g.kruskal();
    return 0;
}