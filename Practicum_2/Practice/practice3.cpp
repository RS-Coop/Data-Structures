#include "practice3.hpp"
#include <vector>
#include <list>

using namespace std;

Graph::Graph()
{
}


Graph::~Graph()
{
}


void Graph::addEdge(int v1, int v2) //Completed
{
  Edge *newEdge1 = new Edge;

  vertex* vert1 = findVertex(v1);
  vertex* vert2 = findVertex(v2);

  newEdge1->v = vert2;

  vert1->Edges.push_back(*newEdge1);
}


void Graph::addVertex(int number) //Completed
{
  vertex *newVert = new vertex;
  newVert->num = number;
  newVert->visited = false;

  vertices.push_back(*newVert);
}


void Graph::displayEdges() //Print statement needs work.
{
  vector<vertex>::iterator i;
  vector<Edge>::iterator j;
  for(i = vertices.begin(); i != vertices.end(); i++)
  {
    cout << i->num << "-->";

    for(j = i->Edges.begin(); j != i->Edges.end(); j++)
    {
      cout << j->v->num;

      if(j != i->Edges.end()-1)
      {
        cout << "***";
      }
    }

    cout << endl;
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


vertex* Graph::findVertex(int number)
{
  vector<vertex>::iterator i;
  for(i = vertices.begin(); i != vertices.end(); i++)
  {
    if(i->num == number)
    {
      return &*i;
    }
  }

  return NULL;
}


void Graph::BFTPath(int startNum, int endNum)
{

  setAllVerticesUnvisited();
  vertex* temp = findVertex(startNum);
  list<vertex*> q1;
  list<int> dist;
  int cd;

  vector<Edge>::iterator i;

  temp->visited = true;
  temp->dst = 0;
  q1.push_back(temp);
  dist.push_back(0);

  //q1.push_back(NULL); //

  while(!q1.empty())
  {
    temp = q1.front();
    q1.pop_front();
    cd = dist.front(); //Current distance.
    dist.pop_front(); //Pops.


    for(i = temp->Edges.begin(); i != temp->Edges.end(); i++)
    {
      if(!i->v->visited)
      {
        i->v->visited = true;
        q1.push_back(i->v);

        i->v->parent = temp;
        i->v->dst = cd+1;
        dist.push_back(cd+1);
      }
    }
  }

  vertex* end = findVertex(endNum);

  cout << "Distance: " << end->dst << endl;

  temp = end;

  while(temp->parent != NULL)
  {
    cout << temp->parent->num << endl;
    temp = temp->parent;
  }
}

int main()
{
  Graph g1;

  g1.addVertex(5);
  g1.addVertex(10);
  g1.addVertex(2);
  g1.addVertex(7);
  g1.addVertex(6);
  g1.addVertex(1);
  g1.addVertex(8);
  g1.addVertex(30);
  g1.addVertex(31);

  g1.addEdge(5,10);
  g1.addEdge(10,7);
  g1.addEdge(7,6);
  g1.addEdge(5,2);
  g1.addEdge(10,1);
  g1.addEdge(1,8);
  g1.addEdge(6,8);
  g1.addEdge(8,30);
  g1.addEdge(30,31);

  g1.BFTPath(5,31);
}
