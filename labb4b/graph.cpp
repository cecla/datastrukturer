/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    // *** TODO ***
    int totalW = 0;
    bool* done = new bool[size]; //need to mark the visited nodes
    int* path = new int[size];
    int* dist = new int[size];

    //want to set dist = INFINITY, path = 0 and done = false
    for (int i = 1; i <= size; ++i)
    {
        done[i] = false;
        path[i] = 0;
        dist[i] = INFINITY;
    }
    
    //The vertex we want to start with
    int start = 1;
    done[start] = true;
    
    //step forward with help of v
    int v = start;

    //loop trough until all the vertex have been true
    while (true)
    {
        Node *p = array[v].getFirst();
        
        while (p)
        {
            if (!done[p->vertex] && dist[p->vertex] > p->weight)
            {
                dist[p->vertex] = p->weight;
                path[p->vertex] = v;
            }
            p = array[v].getNext();
        }
        //find the smallest
        int d = INFINITY;
        
        done[v] = true; //mark the vertex as visited
        
        //find the smallest undone distance vertex
        for(int i = 1; i <= size; i++)
        {
            if (!done[i] && dist[i] < d) //if we have not visited the loop and the weight is smaller, do the if
            {
                d = dist[i]; //update wight to the smallest undone vertex
                v = i; //update v so we start from a new v the next time we enter the loop
            }
        }
        
        //insert the smallest undone distance vertex
        Edge temp = Edge(path[v], v, d);
        
        if (d == INFINITY) break;
        
        //add weight
        totalW += temp.weight;

        cout << temp << endl;
    }
    cout << "Total weight = " << totalW << endl;
}
// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    Heap<Edge> minHeap;
    DSets D(size);
    bool* done= new bool[size];
    int countEdges = 0;
    int totalW = 0;

    for(int i = 0; i < size; i++)
    {
        done[i] = false;
    }
    // insert all edges in the heap by traversing the tree
    for(int i = 0; i < size ; i++)
    {
        Node* p = array[i].getFirst();

        while(p)
        {
            if(!done[p->vertex])
            {
                minHeap.insert(Edge(i, p->vertex, p->weight));
                countEdges++;
            }
            p = array[i].getNext();
        }
        done[i] = true;
    }


    int counter = 0;
    Edge temp;
    while(counter < countEdges)
    {
        temp = minHeap.deleteMin();

     //   cout << "edge: " << temp <<endl;
        if(D.find(temp.head) != D.find(temp.tail))
        {
            totalW += temp.weight;
            D.join(D.find(temp.head), D.find(temp.tail));

            cout << temp<< endl;
        }
        counter++;
    }
    cout <<endl <<  "Total weight: " << totalW << endl;
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
