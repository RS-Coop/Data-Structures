#include "Graph.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
  ifstream infile(argv[1]);

  if(infile.is_open())
  {
    Graph cityG;
    string line, city, dist, city2;
    int distN;
    vector<string> cities;

    getline(infile,line);
    stringstream ss;
    ss << line;

    while(getline(ss,city,','))
    {
      if(city != "cities")
      {
        //cout << city << endl;
        cities.push_back(city);
        cityG.addVertex(city);
      }
    }

    vector<string>::iterator i;

    while(getline(infile,line))
    {
      i = cities.begin();
      ss.clear();
      //cout << line << endl;
      ss << line;
      getline(ss,city,',');
      //cout << "Edges " << city << endl;

      while(getline(ss,dist,','))
      {
        //cout << "Distance read " << dist << endl;
        distN = stoi(dist);

        if(distN > 0)
        {
          city2 = *i;
          //cities.pop();
          cout << " ... Reading in " << city << " -- " << city2 << " -- " << distN << endl;
          cityG.addEdge(city,city2,distN);
        }

        i++;
      }
    }

    cityG.assignDistricts();

    cityG.displayEdges();

  }
  else
  {
    cout << "File could not open." << endl;
  }
}
