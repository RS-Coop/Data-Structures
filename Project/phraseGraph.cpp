#include "phraseGraph.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
//#include <random>

using namespace std;

phraseGraph::phraseGraph()
{
}
phraseGraph::~phraseGraph()
{
}

int phraseGraph::addNode(string thing)
{
  node newNode(thing);

  nodes.push_back(newNode);

  //cout << "Added node: " << newNode.word << endl;

  //return &nodes.at(nodes.size()-1);

  return nodes.size()-1;
}

void phraseGraph::addEdge(int ind1, int ind2)
{
  edge newEdge(ind1, ind2);

  nodes[newEdge.prev].totWeight += 1;

  nodes[ind1].edges.push_back(newEdge);

  //cout << "Added edge: " << nodes[newEdge.prev].word << "->" << nodes[newEdge.nxt].word << endl;
}

void phraseGraph::generatePhrase(string word, int length)
{
  //cout << "phrase: ";
  //cout << endl << endl;
  locale loc;
  int nodeIdx = findNode(word);

  while(nodeIdx == -1 || nodes[nodeIdx].totWeight == 0)
  {
    nodeIdx = random(nodes.size());
    //cout << "Here" << endl;
  }

  int l = 0;
  int prob;
  vector<edge>::iterator i;
  bool loop = true;

  while(l < length)
  {
    loop = true;

    if(l == 0)
    {
      cout << toupper(nodes[nodeIdx].word[0],loc);
      cout << nodes[nodeIdx].word.substr(1,nodes[nodeIdx].word.length()-1);
    }
    else
      cout << nodes[nodeIdx].word;

    if(l != length)
      cout << " ";

    while(loop)
    {
    //cout << "Total weight: " << nodes[nodeIdx].totWeight << endl;
      prob = random(nodes[nodeIdx].totWeight);
      //cout << nodes[nodeIdx].word << " " << nodes[nodeIdx].totWeight << endl;

      for(i=nodes[nodeIdx].edges.begin(); i!=nodes[nodeIdx].edges.end(); i++)
      {
        //cout << i->max << " " << i->min << endl;
        if(i->max >= prob && i->min <= prob)
        {
          if(nodes[i->nxt].totWeight == 0 && nodes[nodeIdx].totWeight == 1)
          {
            l = length;
            loop = false;
            cout << nodes[i->nxt].word;
            break;
          }
          else if(nodes[i->nxt].totWeight != 0)
          {
            nodeIdx = i->nxt;
            loop = false;
            break;
          }
        }
      }
    }

    l++;
  }

  cout << endl;
}

void phraseGraph::buildBookGraph(string filename)
{
  ifstream infile(filename);

  if(infile.is_open())
  {
    string pre,post,line;
    int anEdge;
    int preI, postI;

    while(getline(infile,line))
    {
      stringstream ss(line);
      getline(ss,line,'.');
      getline(ss,line,';');

      line = line.substr(1,line.length());

      stringstream s2(line);
      getline(s2,pre,' ');

      //cout << pre << endl;
      for(int i=0; i<pre.length(); i++)
      {
        pre[i] = tolower(pre[i]);
      }
      preI = findNode(pre);
      //cout << "PreI: " << preI << endl;

      while(getline(s2,post,' '))
      {
        if(post[0] == '\r')
          break;

        for(int i=0; i<post.length(); i++)
        {
          post[i] = tolower(post[i]);
        }

        postI = findNode(post);
        //cout << "PostI: " << postI << endl;

        if(preI == -1 || postI == -1)
          anEdge = -1;
        else
        {
          anEdge = findEdge(preI,postI);
        }

        if(preI == -1)
        {
          preI = addNode(pre);
        }
        if(postI == -1)
        {
          //cout << "Before adding: " << nodes[preI].word << endl;
          postI = addNode(post);
          //cout << "After adding: " << nodes[preI].word << endl;
        }

        if(anEdge == -1)
          addEdge(preI,postI);
        else
          addWeight(preI,anEdge);

          pre = post;
          preI = postI;
      }
    }

    vector<node>::iterator i;

    for(i=nodes.begin(); i!=nodes.end(); i++)
    {
      calcProbability(distance(nodes.begin(),i));
    }

    cout << "File read, graph built." << endl;

    infile.close();
  }
  else
  {
    cout << "File could not be opened." << endl;
  }
}

void phraseGraph::buildQuoteGraph(string filename)
{
  ifstream infile(filename);

  if(infile.is_open())
  {
    string pre,post,line;
    int anEdge;
    int preI, postI;
    int lines = 0;

    while(getline(infile,line,';') && lines < 5000)
    {
      stringstream ss(line);
      getline(infile,line,';');
      getline(infile,line);
      getline(ss,pre,' ');

      for(int i=0; i<pre.length(); i++)
      {
        pre[i] = tolower(pre[i]);
      }
      preI = findNode(pre);

      while(getline(ss,post,' '))
      {
        if(post[0] == '\r')
          break;

        for(int i=0; i<post.length(); i++)
        {
          post[i] = tolower(post[i]);
        }

        postI = findNode(post);
        //cout << "PostI: " << postI << endl;

        if(preI == -1 || postI == -1)
          anEdge = -1;
        else
          anEdge = findEdge(preI,postI);

        if(preI == -1)
          preI = addNode(pre);
        if(postI == -1)
          postI = addNode(post);

        if(anEdge == -1)
          addEdge(preI,postI);
        else
          addWeight(preI,anEdge);

          pre = post;
          preI = postI;
    }
    lines++;
  }

    vector<node>::iterator i;

    for(i=nodes.begin(); i!=nodes.end(); i++)
    {
      calcProbability(distance(nodes.begin(),i));
    }

    cout << "File read, graph built." << endl;

    infile.close();
  }
  else
  {
    cout << "File could not be opened." << endl;
  }
}

void phraseGraph::buildMovieGraph(string filename)
{
  ifstream infile(filename);

  if(infile.is_open())
  {
    string pre,post,line;
    int anEdge;
    int preI, postI;

    while(getline(infile,line))
    {
      stringstream ss(line);
      getline(ss,pre,' ');

      //cout << pre << endl;
      for(int i=0; i<pre.length(); i++)
      {
        pre[i] = tolower(pre[i]);
      }
      preI = findNode(pre);
      //cout << "PreI: " << preI << endl;

      while(getline(ss,post,' '))
      {
        if(post[0] == '\r')
          break;

        for(int i=0; i<post.length(); i++)
        {
          post[i] = tolower(post[i]);
        }

        postI = findNode(post);
        //cout << "PostI: " << postI << endl;

        if(preI == -1 || postI == -1)
          anEdge = -1;
        else
        {
          anEdge = findEdge(preI,postI);
        }

        if(preI == -1)
        {
          preI = addNode(pre);
        }
        if(postI == -1)
        {
          //cout << "Before adding: " << nodes[preI].word << endl;
          postI = addNode(post);
          //cout << "After adding: " << nodes[preI].word << endl;
        }

        if(anEdge == -1)
          addEdge(preI,postI);
        else
          addWeight(preI,anEdge);

          pre = post;
          preI = postI;
      }
    }

    vector<node>::iterator i;

    for(i=nodes.begin(); i!=nodes.end(); i++)
    {
      calcProbability(distance(nodes.begin(),i));
    }

    cout << "File read, graph built." << endl;

    infile.close();
  }
  else
  {
    cout << "File could not be opened." << endl;
  }
}

void phraseGraph::buildNewsGraph(string filename)
{
  ifstream infile(filename);

  if(infile.is_open())
  {
    string pre,post,line;
    int anEdge;
    int preI, postI;
    int lines = 0;

    while(getline(infile,line) && lines < 5000)
    {
      stringstream ss(line);
      getline(ss,pre,' ');

      //cout << pre << endl;
      for(int i=0; i<pre.length(); i++)
      {
        pre[i] = tolower(pre[i]);
      }
      preI = findNode(pre);
      //cout << "PreI: " << preI << endl;

      while(getline(ss,post,' '))
      {
        if(post[0] == '\r')
          break;

        for(int i=0; i<post.length(); i++)
        {
          post[i] = tolower(post[i]);
        }

        postI = findNode(post);
        //cout << "PostI: " << postI << endl;

        if(preI == -1 || postI == -1)
          anEdge = -1;
        else
        {
          anEdge = findEdge(preI,postI);
        }

        if(preI == -1)
        {
          preI = addNode(pre);
        }
        if(postI == -1)
        {
          //cout << "Before adding: " << nodes[preI].word << endl;
          postI = addNode(post);
          //cout << "After adding: " << nodes[preI].word << endl;
        }

        if(anEdge == -1)
          addEdge(preI,postI);
        else
          addWeight(preI,anEdge);

          pre = post;
          preI = postI;
      }
      lines++;
    }

    vector<node>::iterator i;

    for(i=nodes.begin(); i!=nodes.end(); i++)
    {
      calcProbability(distance(nodes.begin(),i));
    }

    cout << "File read, graph built." << endl;

    infile.close();
  }
  else
  {
    cout << "File could not be opened." << endl;
  }
}

void phraseGraph::buildQuipGraph(string filename)
{
  ifstream infile(filename);

  if(infile.is_open())
  {
    string pre,post,line;
    int anEdge;
    int preI, postI;

    while(getline(infile,line))
    {
      stringstream ss(line);
      getline(ss,pre,' ');

      //cout << pre << endl;
      for(int i=0; i<pre.length(); i++)
      {
        pre[i] = tolower(pre[i]);
      }
      preI = findNode(pre);
      //cout << "PreI: " << preI << endl;

      while(getline(ss,post,' '))
      {
        if(post[0] == '\r')
          break;

        for(int i=0; i<post.length(); i++)
        {
          post[i] = tolower(post[i]);
        }

        postI = findNode(post);
        //cout << "PostI: " << postI << endl;

        if(preI == -1 || postI == -1)
          anEdge = -1;
        else
        {
          anEdge = findEdge(preI,postI);
        }

        if(preI == -1)
        {
          preI = addNode(pre);
        }
        if(postI == -1)
        {
          //cout << "Before adding: " << nodes[preI].word << endl;
          postI = addNode(post);
          //cout << "After adding: " << nodes[preI].word << endl;
        }

        if(anEdge == -1)
          addEdge(preI,postI);
        else
          addWeight(preI,anEdge);

          pre = post;
          preI = postI;
      }
    }

    vector<node>::iterator i;

    for(i=nodes.begin(); i!=nodes.end(); i++)
    {
      calcProbability(distance(nodes.begin(),i));
    }

    cout << "File read, graph built." << endl;

    infile.close();
  }
  else
  {
    cout << "File could not be opened." << endl;
  }
}

void phraseGraph::displayEdges()
{
  vector<node>::iterator i;
  vector<edge>::iterator j;
  for(i = nodes.begin(); i != nodes.end(); i++)
  {
    cout << i->word << "-->" << i->totWeight << endl;
    // for(j = i->edges.begin(); j != i->edges.end(); j++)
    // {
    //   cout << nodes[j->nxt].word;
    //
    //   if(j != i->edges.end()-1)
    //   {
    //     cout << "***";
    //   }
    // }

    //cout << endl;
  }
}

void phraseGraph::addWeight(int nodeIdx, int Edge)
{
  //cout << "Pre Weight: " << nodes[nodeIdx].totWeight << endl;
  nodes[nodeIdx].edges[Edge].weight++;
  nodes[nodeIdx].totWeight++;
  //cout << "Post Weight: " << nodes[nodeIdx].totWeight << endl;
}

int phraseGraph::findNode(string word)
{
  vector<node>::iterator i;
  int found = -1;

  for(i=nodes.begin(); i!=nodes.end(); i++)
  {
    if(i->word == word)
    {
      //cout << "finding " << i->word << " size: " << i->edges.size() << endl;
      found =  distance(nodes.begin(),i);
    }
  }

  return found;
}

int phraseGraph::findEdge(int ind1, int ind2)
{
  vector<edge>::iterator i;
  int foundEdge = -1;

  for(i=nodes[ind1].edges.begin(); i!=nodes[ind1].edges.end(); i++)
  {
    if(nodes[i->nxt].word == nodes[ind2].word)
    {
      foundEdge = distance(nodes[ind1].edges.begin(),i);
    }
  }

  return foundEdge;
}

void phraseGraph::calcProbability(int idx)
{
  vector<edge>::iterator i;
  int curMax = 0;

  for(i=nodes[idx].edges.begin(); i!=nodes[idx].edges.end(); i++)
  {
    i->min = curMax+1;
    curMax = curMax+(i->weight);
    i->max = curMax;
  }
}

int phraseGraph::random(int totWeight)
{
  //cout << "Weight: " << totWeight << endl;
  int k;

  k = 1 + (rand()%(totWeight));

  //cout << "Probability: " << k << endl;

  return k;
}
