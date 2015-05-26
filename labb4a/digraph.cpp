/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>

using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }
    Queue<int> Q;

    // for all vertexes v in the graph, set dist(v) to INFINITY and path(v) to 0
    for(int i = 1; i <= size; i++)
    {
        dist[i] = INFINITY;
        path[i] = 0;
    }
    dist[s] = 0;

    Q.enqueue(s);

    while(!Q.isEmpty())
    {
        // fetch the first element in the queue and remove it from queue
        int v = Q.getFront();
        Q.dequeue();

        // Get the first vertex pointed to by v
        Node* p = array[v].getFirst();

        // for every vertex adjacent to v,
        // visit and check if it has been visited before        while(p)
        {
            cout << "Vertex " << v << " is pointing to " << p->vertex << endl;

            // If dist is inf, the node has not been visited
            if(dist[p->vertex] == INFINITY)
            {
                // set the dist to one more than the vertex it came from, v
                dist[p->vertex] = dist[v]+1;
                // path is the vertex it came from, v
                path[p->vertex] = v;
                // put it on the queue to later visit its neighbors too
                Q.enqueue(p->vertex);
            }
            // move to the next vertex pointed to by v            p = array[v].getNext();
        }
        // when all of the vertexes pointed by v have been visited, got a correct distance and path
        // and been put on the queue, go to the next on the queue and do the same there.
    }
}

// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    // *** TODO ***
}

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }
    // look for the source value, which is where dist = 0
    int source;
    for(int i = 1; i <= size; i++)
    {
        cout << i << " dist = " << dist[i] << endl;
        if(dist[i] == 0)
        {
            source = i;
            break;
        }
    }
    // use a vector to get the path in the right direction,
    // which is the opposite of the way we receive them
    vector<int> toPrint;
    // start the path with the source
    toPrint.push_back(source);

    // create temp int to not have to modify the target value
    int temp = t;
    // loop while the path have not reached the source, starting from the target
    while(path[temp] != source)
    {
        // save the path and advance to the next target
        toPrint.push_back(path[temp]);        temp = path[temp];
    }

    // use an iterator to go through the vector and display the path
    vector<int>::iterator it = toPrint.begin();
    while(it != toPrint.end())
    {
        cout<< " "<<*it;
        it++;
    }
    cout << " (" << t << ")";
}
