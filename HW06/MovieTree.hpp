#ifndef MOVIETREE_HPP
#define MOVIETREE_HPP
#include <string>
using namespace std;

struct MovieNode
{
  int ranking;
  std::string title;
  int year;
  int quantity;

  MovieNode *parent;
  MovieNode *leftChild;
  MovieNode *rightChild;

  MovieNode(){
    parent = leftChild = rightChild = nullptr;
  }

  MovieNode(int r, std::string t, int y, int q) {
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
  void addMovieNode(int ranking, std::string title, int year, int quantity);
  void findMovie(string title);
  void rentMovie(string title);
  void deleteMovie(string title);
  void countMovies();
private:
  void countHelper(MovieNode* root, int* cptr); //Helper function.
  MovieNode* deleteNode(MovieNode* root, string title); //Helper function.
  void deleteTree(MovieNode* temp); //Helper function for destructor.
  void printMovie(MovieNode* root); //Helper function
  MovieNode *search(string title);
  MovieNode *root;
};
#endif
