#include <iostream>
#include <cstdlib>
#include <vector>
#include "QueueA.cpp"
#include "StackA.cpp"

using namespace std;

// Using a source file of over 50000 words,
// program seg faults during runtime if more than 24562
// strings are attempted to be added to graph
const static int MAX_VERTICES = 24562;

template<class vertex>
class Graph {
private:
    int numVertices;  // number of vertices
    int maxVertices;  // maxVertices maximum number of vertices
    vertex* vertices; // vertex array
    bool* marks;      // marker array (true = visited and false otherwise)
    int** edges;     // edge array (1 = connected and 0 otherwise)
public:
    Graph(){
        init();
    }
    ~Graph(){
        clearGraph();
    }
    void init();
    void clearGraph();
    int indexIs(vertex x);

    //copy constructor
    Graph(const Graph& rhs){
        init();
        *this = rhs;
    }

    //overloaded assignment operator
    const Graph& operator = (const Graph& other){
            if(this == &other) return *this;
            clearGraph();
            init();
            maxVertices = other.maxVertices;
            numVertices = other.numVertices;
            for(int i = 0; i < other.maxVertices; i++){// removes row
                for(int j = 0; j < other.maxVertices; j++){// removes columns
                    edges[i][j] = other.edges[i][j];
                }
            }
            for(int i = 0; i < maxVertices; i++)
                marks[i] = other.marks[i];
            for(int i = 0; i < maxVertices; i++)
                vertices[i] = other.vertices[i];

            return *this;
    }

    // return true if there is no vertex in the graph
    bool isEmpty(){ return (numVertices == 0); }

    // return true if the is no more space for vertices
    bool isFull(){ return (numVertices == maxVertices); }

    // returns number of current vertices
    int getNumberVertices() { return numVertices; }

    // returns the list of vertices
    void printVertexList(){
        for(int i=0; i <= numVertices; i++){
            cout << vertices[i] << ", ";
        }
        cout << endl;
    }
    // returns the list of edges values
    void printEdgeList(){
        for(int i=0; i < (sizeof(edges))/(sizeof(edges[0])); i++){
            cout << *(edges[i]) << ", ";
        }
    }


    // display the graph
    void print();

    // add vertex to the vertex array
    void addVertex(vertex a);

    // set the element in the edge array to 1
    void addEdge(vertex from, vertex to);

    // return a vertex's connected list (queue) of vertices
    void getToVertices(vertex start, Queue<vertex>& chain);

    // set all markers to false
    void clearMarks(){
        for(int i = 0; i < maxVertices; i++){
            marks[i] = false;
        }
    }

    // set the vertex's marker to true
    void markVertex(vertex x){ marks[indexIs(x)] = true; }

    // return true if vertex's marker is true
    bool isMarked(vertex x){ return marks[indexIs(x)]; }
};


template<class vertex>
void Graph<vertex>::init(){
    this->numVertices = 0;
    this->maxVertices = MAX_VERTICES;
    vertices = new vertex[maxVertices];

    edges = new int *[maxVertices]; //first row
    for(int i = 0; i < maxVertices; i++) // generates columns
        edges[i] = new int[maxVertices];

        marks = new bool[maxVertices]; // should this be 'marks[i] = false;'
        clearMarks();
}


template<class vertex>
void Graph<vertex>::clearGraph(){
    delete[] vertices;
    for(int i = 0; i < maxVertices; i++)
        delete[] edges[i];
    delete[] edges;
    delete[] marks;
    numVertices = 0;
}

template<class vertex>
void Graph<vertex>::addVertex(vertex a){
    if(numVertices == maxVertices) return;

    vertices[numVertices] = a;
    numVertices++;

    // cleans up the rest of the array, to ensure no overlaps
    for(int i = 0; i < maxVertices; i++){
        edges[numVertices - 1][i] = 0; // fills the "from" column
        edges[i][numVertices - 1] = 0; // fills the "to" row
    }
}


// if graph does not need to be weighted, distance is unnecessary
// parameter could be removed. See asdf comment.
template<class vertex>
void Graph<vertex>::addEdge(vertex from, vertex to){
    //bool distance = true;
    int f = indexIs(from);
    int t = indexIs(to);
    if(f == numVertices || t == numVertices)
        return;
    edges[f][t]++;//    = distance; //asdf set to 'true' if edges is a bool array
}

template<class vertex>
int Graph<vertex>::indexIs(vertex x){
    int i = 0;
    while( !(x==vertices[i]) && i < numVertices)
        i++;
    return i;
}

template<class vertex>
void Graph<vertex>::print(){
    cout << "Number of vertices = " << numVertices << "/" << maxVertices << endl;
    cout << " ";
    for(int i = 0; i < numVertices; i++)
        cout << " " << vertices[i];
    cout<<endl;
    for(int i=0; i < numVertices; i++){
        cout << vertices[i] << ":";
        for(int j=0; j < numVertices; j++){
            cout << edges[i][j] << " ";
        }
        cout << endl;
    }
}

template<class vertex>
void Graph<vertex>::getToVertices(vertex x, Queue<vertex>& adjacent){
    int i = indexIs(x);
    // TO-DO: check for existence
    for(int j = 0; j < maxVertices; j++){
        if( edges[i][j])
            adjacent.push(vertices[j]);
    }
}


template<class vertex>
void BFS(Graph<vertex>& g, vertex sV, vertex eV){
    Queue<vertex> q;
    Queue<vertex> vertexQ;
    bool found = false;
    vertex v;
    vertex x;

    g.clearMarks();
    q.push(sV);
    do {
        v = q.front(); q.pop();
        if(v == eV){
            cout << "->"<<v;
            found = true;
        } else {
            if( !g.isMarked(v)){
                g.markVertex(v);
                cout << "->"<<v;
                g.getToVertices(v, vertexQ);// get next level
                while( !vertexQ.empty()){
                    x = vertexQ.front(); vertexQ.pop();
                    if( !g.isMarked(x))
                        q.push(x);
                }
            }
        }
    } while (!q.empty() && !found);
    cout<<endl;
}


template<class vertex>
void DFS(Graph<vertex>& g, vertex sV, vertex eV){
    Stack<vertex> q;
    Queue<vertex> vertexQ;
    bool found = false;
    vertex v;
    vertex x;

    g.clearMarks();
    q.push(sV);
    do {
        v = q.top(); q.pop();
        if(v == eV){
            cout << "->"<<v;
            found = true;
        } else {
            if( !g.isMarked(v)){
                g.markVertex(v);
                cout << "->"<<v;
                g.getToVertices(v, vertexQ);// get next level
                while( !vertexQ.empty()){
                    x = vertexQ.front(); vertexQ.pop();
                    if( !g.isMarked(x))
                        q.push(x);
                }
            }
        }
    } while ( !q.empty() && !found );
    cout<<endl;
}





template <class vertex>
void getPaths(Graph<vertex> graph, vertex startV, vertex endV,
              vector<vector<vertex> >& result){
    if(graph.indexIs(startV) == graph.indexIs(endV) )
        cout << "You are here!" <<endl;

    Queue<vector<vertex> > queue;
    Queue<vertex> vertexQ;
    vector<vertex> v;
    vertex x;

    v.push_back(startV);
    queue.push(v);

    do {
        v = queue.front(); queue.pop();
        if( v.back() == endV ){
            result.push_back(v);
        } else {
            graph.getToVertices(v.back(), vertexQ);
            while(!vertexQ.empty()) {
                x = vertexQ.front(); vertexQ.pop();
                vector<vertex> v2 = v;
                bool found = false; int i = 0;
                while( !found && i < v2.size() )
                    found = (v2[i++] == x); // if the next element in v2 is the vertex I just worked with, set found to true
                if( !found ){
                    v2.push_back(x);
                    queue.push(v2);
                }
            }
        }
    } while ( !queue.empty() );
}
