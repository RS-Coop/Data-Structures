#include "practice3.hpp"
#include <vector>
#include <list>

using namespace std;

void Graph::shortestPath(int startV, int endV)
{
  vertex* temp = findVertex(startNum);
  list<vertex*> q1;

  int dist[vertices.size()]; //Holds distance

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
