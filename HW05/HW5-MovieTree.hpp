#ifndef MOVIETREE_HPP
#define MOVIETREE_HPP

#include <string>
using namespace std;

struct MovieNode
{
  int ranking;
  string title;
  int year;
  int quantity;

  MovieNode *parent;
  MovieNode *leftChild;
  MovieNode *rightChild;

  MovieNode(){
    parent = leftChild = rightChild = nullptr;
  }

  MovieNode(int r, string t, int y, int q) {
    ranking = r;
    title = t;
    year = y;
    quantity = q;
    parent = leftChild = rightChild = nullptr;
  }
};

class MovieTree
{
public:
  MovieTree();
  ~MovieTree();
  void printMovieInventory();
  void printMovie(MovieNode* root); //Helper function
  void addMovieNode(int ranking, string title, int year, int quantity);
  void findMovie(string title);
  void rentMovie(string title);
private:
  MovieNode *search(string title);
  void deleteNode(MovieNode* temp); //Helper function for destructor.
  MovieNode *root;
};

#endif
