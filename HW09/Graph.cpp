 #include "Graph.hpp"
#include <iostream>
#include <list>

using namespace std;

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::addEdge(std::string v1, std::string v2, int distance) //Completed
{
  Edge *newEdge1 = new Edge;

  vertex* vert1 = findVertex(v1);
  vertex* vert2 = findVertex(v2);

  newEdge1->v = vert2;
  newEdge1->distance = distance;

  vert1->Edges.push_back(*newEdge1);
}

void Graph::addVertex(std::string name) //Completed
{
  vertex *newVert = new vertex;
  newVert->name = name;
  newVert->district = -1;
  newVert->visited = false;

  vertices.push_back(*newVert);
}

void Graph::displayEdges() //Print statement needs work.
{
  vector<vertex>::iterator i;
  vector<Edge>::iterator j;
  for(i = vertices.begin(); i != vertices.end(); i++)
  {
    cout << i->district << ":" << i->name << "-->";

    for(j = i->Edges.begin(); j != i->Edges.end(); j++)
    {
      cout << j->v->name << " (" << j->distance << " miles)";

      if(j != i->Edges.end()-1)
      {
        cout << "***";
      }
    }

    cout << endl;
  }
}

void Graph::assignDistricts()
{
  setAllVerticesUnvisited();
  int districts = 1;

  vector<vertex>::iterator i;
  for(i = vertices.begin(); i != vertices.end(); i++)
  {
    if(!i->visited)
    {
      BFTraversalLabel(i->name, districts);
      districts++;
    }
  }
}

void Graph::printDFS() //Completed
{
  setAllVerticesUnvisited();

  vector<vertex>::iterator i;
  for(i = vertices.begin(); i != vertices.end(); i++)
  {
    DFTraversal(&*i);
  }
}

void Graph::setAllVerticesUnvisited()
{
  vector<vertex>::iterator i;
  for(i = vertices.begin(); i != vertices.end(); i++)
  {
    i->visited = false;
  }
}

vertex* Graph::findVertex(std::string name)
{
  vector<vertex>::iterator i;
  for(i = vertices.begin(); i != vertices.end(); i++)
  {
    if(i->name == name)
    {
      return &*i;
    }
  }

  return NULL;
}

void Graph::BFTraversalLabel(std::string startingCity, int distID)
{
  vertex* temp = findVertex(startingCity);
  list<vertex*> q1;

  vector<Edge>::iterator i;

  temp->visited = true;
  q1.push_back(temp);

  while(!q1.empty())
  {
    temp = q1.front();
    temp->district = distID;
    q1.pop_front();

    for(i = temp->Edges.begin(); i != temp->Edges.end(); i++)
    {
      if(!i->v->visited)
      {
        i->v->visited = true;
        q1.push_back(i->v);
      }
    }
  }
}

void Graph::DFTraversal(vertex* v) //Completed
{
  if(!v->visited)
  {
    cout << v->name << endl;
    v->visited = true;
  }

  vector<Edge>::iterator i;
  for(i = v->Edges.begin(); i != v->Edges.end(); i++)
  {
    if(!i->v->visited)
      DFTraversal(i->v);
  }
}
