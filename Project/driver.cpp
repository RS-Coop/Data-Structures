#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include "phraseGraph.hpp"

using namespace std;


int main(int argc, char *argv[])
{
  srand(time(NULL));

  phraseGraph g1;

  g1.buildQuoteGraph(argv[1]);

  g1.displayEdges();

  //g1.generatePhrase("old",10);

  return 0;
}
