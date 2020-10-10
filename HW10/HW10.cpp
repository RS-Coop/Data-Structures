#include "HW10.hpp"
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
  //cout << "EDGE: " << v1 << "->" << v2 << endl;

  Edge newEdge1;
  Edge newEdge2;

  int vert1 = findVertex(v1);
  int vert2 = findVertex(v2);

  newEdge1.v = vert2;
  newEdge2.v = vert1;

  vertices[vert1].Edges.push_back(newEdge1);
  vertices[vert2].Edges.push_back(newEdge2);

  //cout << "Pre: " << nodes[vert1].Edges.at(vert1->Edges.size()-1).v->num << endl << endl;
}


void Graph::addVertex(int number) //Completed
{
  vertex newVert;
  newVert.num = number;
  newVert.visited = false;
  newVert.dst = 0;
  newVert.parent = -1;

  vertices.push_back(newVert);
}


void Graph::displayEdges() //Print statement needs work.
{
  vector<vertex>::iterator i;
  vector<Edge>::iterator j;
  for(i = vertices.begin(); i != vertices.end(); i++)
  {
    cout << i->num << "-->";
    //cout << i->Edges.size() << endl;
    for(j = i->Edges.begin(); j != i->Edges.end(); j++)
    {
      cout << vertices[j->v].num;

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


int Graph::findVertex(int number)
{
  vector<vertex>::iterator i;
  int found = -1;

  for(i = vertices.begin(); i != vertices.end(); i++)
  {
    if(i->num == number)
    {
      found = distance(vertices.begin(),i);
    }
  }

  return found;
}


void Graph::BFTPath(int startNum, int endNum)
{

  setAllVerticesUnvisited();
  int temp = findVertex(startNum);
  list<int> q1;
  list<int> dist;
  int cd;

  vector<Edge>::iterator i;

  vertices[temp].visited = true;
  vertices[temp].dst = 0;
  q1.push_back(temp);
  dist.push_back(0);

  //q1.push_back(NULL); //

  while(!q1.empty())
  {
    temp = q1.front();
    q1.pop_front();
    cd = dist.front(); //Current distance.
    dist.pop_front(); //Pops.


    for(i =vertices[temp].Edges.begin(); i != vertices[temp].Edges.end(); i++)
    {
      if(!vertices[i->v].visited)
      {
        vertices[i->v].visited = true;
        q1.push_back(i->v);

        vertices[i->v].parent = temp;
        vertices[i->v].dst = cd+1;
        dist.push_back(cd+1);
      }
    }
  }

  int end = findVertex(endNum);

  cout << "Distance: " << vertices[end].dst << endl;

  list<int> path;
  temp = end;

  while(vertices[temp].parent != -1)
  {
    //cout << vertices[temp].num << endl;
    path.push_back(vertices[temp].num);
    temp = vertices[temp].parent;
  }

  cout << "Path: " << endl;

  while(!path.empty())
  {
    temp = path.back();
    path.pop_back();

    cout << temp/10 << "," << temp%10 << endl;
  }
}

int main(int argc, char* argv[])
{
  int n = atoi(argv[1]);
  cout << "Building matrix of size " << n << endl << endl;

  int iM1 = atoi(argv[2]);
  int iM2 = atoi(argv[3]);

  int tH1 = atoi(argv[4]);
  int tH2 = atoi(argv[5]);

  Graph g1;

  for(int i=1; i<=n; i++)
  {
    for(int j=1; j<=n; j++)
    {
      //cout << "Adding vertex: " << (i*10+j) << endl;
      g1.addVertex(i*10+j);

      if(j>1)
      {
        //cout << "Adding edge: " << (i*10+j-1) << "," << (i*10+j) << endl;
        g1.addEdge((i*10+j-1),(i*10+j));
        //cout << "Post: " << g1.vertices[g1.vertices[0].Edges[0].v].num << endl;
      }

      if(i>1)
        g1.addEdge(((i-1)*10+j),(i*10+j));
    }
  }
  //g1.displayEdges();

  g1.BFTPath((iM1*10+iM2),(tH1*10+tH2));
}
