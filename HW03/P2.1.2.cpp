#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

struct city
{
  string name; // name of the city
  city *next; // pointer to the next city
  int numberMessages; // how many messages passed through this city
  string message; // message we are sending accross
};

city* searchNetwork(city *head, string cityName);
void printPath(city *head);

city* searchNetwork(city *head, string cityName)
{
  city *path = head;

  while(path->next != NULL)
  {
    if(path->name == cityName)
    {
      return path;
    }
    path = path->next;
  }

  return NULL;
}

void printPath(city *head)
{
  city *path = head;

  cout << "== CURRENT PATH ==" << endl;
  if (head == NULL) {
    cout << "nothing in path" << endl;
  }

  while(path->next != NULL)
  {
    cout << path->name << "->";
    path = path->next;
  }

  cout << "===" << endl;
}

int main()
{
  
}
