#ifndef PHRASEGRAPH_HPP
#define PHRASEGRAPH_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
//#include "hashTable.hpp"
using namespace std;

struct edge;

struct node //Node struct for graph class.
{
  string word; //Word at node.
  vector <edge> edges; //Nodes adjacent to this one.
  int totWeight; //Total weight of all edges leaving node.

  node() //Default constructor.
  {
  }

  node(string word) //Node constructor. Sets word variable.
  {
    this->word = word; //Sets the word.
    totWeight = 0; //Sets total weight to zero as no edges exist.
  }
};

struct edge //Edge struct for graph class.
{
  int prev; //Word at beginning of edge. Directed.
  int nxt; //Word at the end of the edge.
  int weight; //Weight of edge.

  int max; //Max of range.
  int min; //Min of range.

  edge(int ind1, int ind2) //Edge constructor.
  {
    prev = ind1; //Sets prev index for start word.
    nxt = ind2; //Sets nxt index for following word.
    weight = 1; //Weight is one as this is edge creation.
  }
};

class phraseGraph //Graph class.
{
private:
  vector <node> nodes; //List of all nodes in graph. Might be hash

  //hashTable hashNodes(500);

  int findNode(string word); //Finds node if it exists in graph.

  int findEdge(int ind1, int ind2); //Finds if there is an edge or not.

  void calcProbability(int idx); //Calculates probability in form of min and max
  //for all of the nodes edges.

  int random(int totWeight); //Random number generator for generate phrase.

public:
  phraseGraph(); //Constructor
  ~phraseGraph(); //Deconstructor.

  int addNode(string word); //Adds a new node to the graph.

  void addEdge(int ind1, int ind2); //Adds an edge between two nodes.

  void addWeight(int nodeIdx, int Edge); //Adds weight to edge.

  void generatePhrase(string word, int length); //Traverses graph and generates phrase.

  void buildBookGraph(string filename); //Builds basic test graph.

  void buildQuoteGraph(string filename); //Builds graph from quote data set.

  void buildNewsGraph(string filename); //Builds graph from news data set.

  void buildMovieGraph(string filename);

  void buildQuipGraph(string filename);

  void displayEdges(); //Displays all edges for debuggin purposes.
};
#endif
