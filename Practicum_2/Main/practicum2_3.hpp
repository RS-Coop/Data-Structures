#include <iostream>
#include <vector>

using namespace std;

struct vertex;

struct Edge
{
    vertex*v;
};
struct vertex
{
    int num;
    bool visited;
    vector<Edge> Edges; //stores edges to adjacent vertices

    int incoming;
    int outgoing;

    vertex()
    {
      incoming = 0;
      outgoing = 0;
    }
};

class Graph
{
  public:
    Graph();
    ~Graph();
    void addEdge(int v1, int v2);
    void addVertex(int number);
    void displayEdges();
    void setAllVerticesUnvisited();
    int mostIncoming();
    int mostOutgoing();
    void BFTEdges(vertex* start);

  private:
    vector<vertex> vertices; //stores vertices
    vertex *findVertex(int number);

};
