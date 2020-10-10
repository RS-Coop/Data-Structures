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
    int dst;
    vertex* parent;
    vector<Edge> Edges; //stores edges to adjacent vertices

    vertex()
    {
      parent = NULL;
      dst = 0;
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
    void BFTPath(int startNum, int endNum);

  private:
    vector<vertex> vertices; //stores vertices
    vertex *findVertex(int number);

};
