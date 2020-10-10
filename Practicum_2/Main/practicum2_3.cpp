//cpp file for practicum 2 problem

#include "practicum2_3.hpp"
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
    i->incoming = 0;
    i->outgoing = 0;
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

void Graph::BFTEdges(vertex* start)
{
  vertex* temp = start;
  list<vertex*> q1;

  vector<Edge>::iterator i;

  //temp->visited = true;
  q1.push_back(temp);

  while(!q1.empty())
  {
    temp = q1.front();
    q1.pop_front();


    for(i = temp->Edges.begin(); i != temp->Edges.end(); i++)
    {
      if(!i->v->visited)
      {
        i->v->visited = true;
        q1.push_back(i->v);
      }
      if(!temp->visited) //Only want to increment temps outgoing if it hasn't been visited.
      {
        //i->v->incoming++; //Think it should go here but wont work.
        temp->outgoing++;
      }
      i->v->incoming++; //Increment incoming.
    }
    temp->visited = true;
  }
}

int Graph::mostIncoming()
{
  vector<vertex>::iterator j;

  for(j = vertices.begin(); j != vertices.end(); j++) //Run modified BFS on all vertices.
  {
    BFTEdges(&*j);
  }

  vertex* largest = &*vertices.begin();

  for(j = vertices.begin(); j != vertices.end(); j++) //Find largest.
  {
    if(largest->incoming < j->incoming)
    {
      largest = &*j;
    }
  }

  cout << "Node with most incoming edges: " << largest->num << "->"
  << largest->incoming << endl;

  return largest->num;
}

int Graph::mostOutgoing()
{
  vector<vertex>::iterator j;

  for(j = vertices.begin(); j != vertices.end(); j++) //Run modified BFS on all vertices.
  {
    BFTEdges(&*j);
  }

  vertex* largest = &*vertices.begin();

  for(j = vertices.begin(); j != vertices.end(); j++) //Find largest.
  {
    if(largest->outgoing < j->outgoing)
    {
      largest = &*j;
    }
  }

  cout << "Node with most outgoing edges: " << largest->num << "->"
  << largest->outgoing << endl;

  return largest->num;
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
  g1.addEdge(5,31);
  g1.addEdge(6,31);

  cout << "Test 1" << endl;

  g1.setAllVerticesUnvisited();
  g1.mostIncoming(); //Expect 31.
  g1.mostOutgoing(); //Expect 5.

  //////////////////

  Graph g2;

  g2.addVertex(1);
  g2.addVertex(2);
  g2.addVertex(3);
  g2.addVertex(4);
  g2.addVertex(5);
  g2.addVertex(6);

  g2.addEdge(2,1);
  g2.addEdge(3,2);
  g2.addEdge(2,3);
  g2.addEdge(2,5);
  g2.addEdge(5,3);
  g2.addEdge(6,3);
  g2.addEdge(5,4);
  g2.addEdge(4,5);

  cout << endl;
  cout << "Test 2" << endl;

  g2.setAllVerticesUnvisited();
  g2.mostIncoming(); //Excpect 3
  g2.mostOutgoing(); //Expect 2

  /////////////////


}
