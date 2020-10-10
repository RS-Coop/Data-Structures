#include <iostream>
#include "MovieTree.hpp"
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
    deleteTree(root);
  }
}

void MovieTree::deleteMovie(string title)
{
  root = deleteNode(root,title);
}

MovieNode* MovieTree::deleteNode(MovieNode* root, string title)
{
  MovieNode* temp1 = root;

  while(temp1 != NULL && title != "")
  {
    if(temp1->title == title)
    {
      break;
    }

    for(unsigned int i=0; i<title.length() && i<temp1->title.length(); i++)
    {
      if(tolower(title[i]) < tolower(temp1->title[i]))
      {
        //cout << "Left" << endl;
        temp1 = temp1->leftChild;
        break;
      }
      else if(tolower(title[i]) > tolower(temp1->title[i]))
      {
        //cout << "Right" << endl;
        temp1 = temp1->rightChild;
        break;
      }
    }
  }
  //cout << temp1->title << endl;

  // We found the node with the value to be deleted
  if(temp1 != NULL)
  {
    //Case 1
    // Leaf node
    if(temp1->leftChild == NULL && temp1->rightChild == NULL)
    {
      cout << "-----No Children-----" << endl;

      if(temp1 == root)
      {
        root = NULL;
        cout << "Deleting " << temp1->title << endl;
        delete temp1;
      }

      else
      {
        //cout << "Here" << endl;
        if(temp1->parent->rightChild != NULL && temp1->parent->rightChild->title == title)
        {
          //cout << "Here" << endl;
          temp1->parent->rightChild = NULL;
        }
        else
        {
          //cout << "Here" << endl;
          temp1->parent->leftChild = NULL;
        }
        //cout << "Here" << endl;
        cout << "Deleting " << temp1->title << endl;
        delete temp1;
        //cout << "Here" << endl;
      }
    }
    /*************************
      Case 2 - Node with one child
      Has a right child
    *************************/
    else if(temp1->leftChild == NULL)
    {
      cout << "-----Right Children-----" << endl;
      MovieNode* temp2 = temp1->rightChild;

      temp2->parent = temp1->parent;

      *temp1 = *(temp2);

      if(temp1 == root)
        root = temp1;

      cout << "Deleting " << temp1->title << endl;
      delete temp2;
    }
    /*************************
      Case 2 - Node with one child
      Has a left child
    *************************/
    else if(temp1->rightChild == NULL)
    {
      cout << "-----Left Children-----" << endl;
      MovieNode* temp2 = temp1->leftChild;

      temp2->parent = temp1->parent;

      *temp1 = *(temp2);

      if(temp1 == root)
        root = temp1;

      cout << "Deleting " << temp1->title << endl;
      delete temp2;
    }
    /*************************
      Case 3 - Node with two children
      Complete this function
    *************************/
    else
    {
      cout << "-----Two Children-----" << endl;
      MovieNode* temp2 = temp1->rightChild;

      //Sets temp2 equal to inorder succesor.
      while(temp2->leftChild != NULL)
      {
        temp2 = temp2->leftChild;
      }

      temp1->quantity = temp2->quantity;
      temp1->title = temp2->title;
      temp1->ranking = temp2->ranking;
      temp1->year = temp2->year;

      temp1->rightChild = deleteNode(temp1->rightChild, temp2->title);

      // temp2->parent->leftChild = temp2->rightChild;
      // temp2->leftChild = temp1->leftChild;
      // temp2->rightChild = temp1->rightChild;
      // temp2->parent = temp1->parent;

      //*temp1 = *temp2;

      // if(temp1 == root)
      //   root = temp1;

      //cout << "Deleting " << temp2->title << endl;
      //delete temp2;
    }

  }

  else
  {
    cout << "Movie not found." << endl;
  }

  return root;

  // if(temp1 == root)
  //   return temp1;
  // else
  //   return root;
}

void MovieTree::deleteTree(MovieNode* temp)
{
  if(temp == NULL)
  {
    return;
  }

  deleteTree(temp->leftChild);

  deleteTree(temp->rightChild);

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

      if(node->quantity == 0)
      {
        deleteMovie(title);
      }
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

void MovieTree::countMovies()
{
  int count = 0;
  int* cptr = &count;

  countHelper(root, cptr);

  cout << "Count = " << count << endl;
}

void MovieTree::countHelper(MovieNode* root, int* cptr)
{
  MovieNode* temp = root;

  if(temp == NULL) return;

  countHelper(temp->leftChild, cptr);

  *cptr = *cptr + 1;

  countHelper(temp->rightChild, cptr);
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
        //cout << "Left" << endl;
        temp = temp->leftChild;
        break;
      }
      else if(title[i] > temp->title[i])
      {
        //cout << "Right" << endl;
        temp = temp->rightChild;
        break;
      }
    }
  }
  return temp;
}
