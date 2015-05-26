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
    Heap<Edge>minHeap;
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

    int start = 1;
    done[start] = true;
    dist[start] = 0;

    int v = start;

    //loop trough until all the vertex have been true
    while (true)
    {
        Node *p = array[v].getFirst();
        
        Edge e;
        
        while (p)
        {
            if (!done[p->vertex] && dist[p->vertex] > p->weight)
            {
                //cout << p->vertex << "  " << p->weight << endl;
                e = Edge(v, p->vertex, p->weight);
                minHeap.insert(e);
                dist[p->vertex] = p->weight;
            }
            p = array[v].getNext();
        }
        //find the smallest
        int d = INFINITY;
        Edge temp;
        
        //här blir det fel
        for(int i = 1; i <= size; i++)
        {
            if (!done[i] && dist[i] < d)
            {
                temp = minHeap.deleteMin();
                d = temp.weight;
                v = temp.tail;
            }
            //cout << temp.head << " " << temp.tail << " " << temp.weight << endl;
            if (minHeap.isEmpty()) break;
        }
        
        if (d == INFINITY) break;
       
        //cout << temp.head << " " << temp.tail << " " << temp.weight << endl;
        totalW += temp.weight;
        done[v] = true;
        
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
