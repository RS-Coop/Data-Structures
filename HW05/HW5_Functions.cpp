#include <iostream>
#include "HW5-MovieTree.hpp"
#include <string>

using namespace std;

MovieTree::MovieTree()
{
  root = NULL;
}

MovieTree::~MovieTree()
{
  if(root != NULL)
  {
  deleteNode(root->leftChild);
  deleteNode(root->rightChild);

  cout << "Deleting: " << root->title << endl;

  delete root;
  }
}

void MovieTree::deleteNode(MovieNode* temp)
{
  if(temp->leftChild != NULL)
  {
    deleteNode(temp->leftChild);
  }

  if(temp->rightChild != NULL)
  {
    deleteNode(temp->rightChild);
  }

  cout << "Deleting: " << temp->title << endl;

  if(temp->parent->leftChild == temp)
  {
    temp->parent->leftChild = NULL;
  }
  else temp->parent->rightChild = NULL;

  delete temp;
}

void MovieTree::printMovieInventory()
{
  printMovie(this->root);
}

void MovieTree::printMovie(MovieNode* root)
{
  if(root == NULL) return;

  printMovie(root->leftChild);

  cout << "Movie: " << root->title << " " << root->quantity << endl;

  printMovie(root->rightChild);
}

void MovieTree::addMovieNode(int ranking, string title, int year, int quantity)
{
  MovieNode* newnode = new MovieNode(ranking, title, year, quantity);
  MovieNode* temp = root;

  if(temp == NULL)
  {
    root = newnode;
  }
  else
  {
    while(temp != NULL)
    {
      for(unsigned int i=0; i<title.length(); i++)
      {
        if(tolower(title[i]) < tolower(temp->title[i]))
        {
          if(temp->leftChild == NULL)
          {
            temp->leftChild = newnode;
            newnode->parent = temp;
            temp = NULL;
            break;
          }
          else
          {
          temp = temp->leftChild;
          break;
          }
        }
        else if(tolower(title[i]) > tolower(temp->title[i]))
        {
          if(temp->rightChild == NULL)
          {
            temp->rightChild = newnode;
            newnode->parent = temp;
            temp = NULL;
            break;
          }
          else
          {
          temp = temp->rightChild;
          break;
          }
        }
      }
    }
  }
}

void MovieTree::findMovie(string title)
{
  MovieNode* node;
  node = search(title);

  if(node != NULL)
  {
    cout << "Movie Info:" << endl;
    cout << "===========" << endl;
    cout << "Ranking:" << node->ranking << endl;
    cout << "Title:" << node->title << endl;
    cout << "Year:" << node->year << endl;
    cout << "Quantity:" << node->quantity << endl;
  }
  else
  {
    cout << "Movie not found." << endl;
  }
}

void MovieTree::rentMovie(string title)
{
  MovieNode* node;
  node = search(title);

  if(node != NULL)
  {
    if(node->quantity > 0)
    {
      //(node->quantity)--;
      cout << "Movie has been rented." << endl;
      cout << "Movie Info:" << endl;
      cout << "===========" << endl;
      cout << "Ranking:" << node->ranking << endl;
      cout << "Title:" << node->title << endl;
      cout << "Year:" << node->year << endl;
      cout << "Quantity:" << --(node->quantity) << endl;
    }
    else
    {
      cout << "Movie out of stock." << endl;
    }
  }
  else
  {
    cout << "Movie not found." << endl;
  }
}

MovieNode* MovieTree::search(string title)
{
  MovieNode* temp = root;
  while(temp != NULL)
  {
    if(temp->title == title)
    {
      return temp;
    }
    for(unsigned int i=0; i<title.length(); i++)
    {
      if(title[i] < temp->title[i])
      {
        cout << "Left" << endl;
        temp = temp->leftChild;
        break;
      }
      else if(title[i] > temp->title[i])
      {
        cout << "Right" << endl;
        temp = temp->rightChild;
        break;
      }
    }
  }
  return temp;
}
