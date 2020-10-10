#include <iostream>

using namespace std;

//cpp file for practicum 2 problem 1.

struct node
{
  int key;
  node* left;
  node* right;

  node(int data)
  {
    key = data;
    left = NULL;
    right = NULL;
  }
};

bool isMinHeap(node* root, bool valid) //Root node and validity boolean.
{
  if(root == NULL) //Base case;
    return valid;

  if(root->left != NULL) //Can we check left child?
  {
    if(root->key > root->left->key) //If it violates property.
    {
      valid = false; //Set boolean to false.
    }
  }

  if(root->right != NULL) //Can we check right child?
  {
    if(root->key > root->right->key) //If it violates property.
    {
      valid = false; //Set boolean to fale;
    }
  }

  valid = isMinHeap(root->left,valid); //Call function for left child.
  valid = isMinHeap(root->right,valid); //Call function for right child.

  return valid; //Return current validity.
}


int main(int argc, char const *argv[])
{
  //Making a tree that should be a min heap.
  node* root = new node(1);
  root->left = new node(2);
  root->right = new node(3);
  root->left->left = new node(4);
  root->left->right = new node(5);
  root->right->left = new node(6);
  root->right->right = new node(7);

  bool validity = isMinHeap(root, true); //Assume it is a min heap and run function.

  cout << "Test 1" << endl;

  if(validity == true) //Should output true.
    cout << "This is a valid minheap." << endl;
  else
    cout << "This is not a valid minheap." << endl;

/////////////////////////////////////////////////////

  //Making a tree that is not a min heap due to the zero at a leaf.
  node* root1 = new node(1);
  root1->left = new node(2);
  root1->right = new node(3);
  root1->left->left = new node(4);
  root1->left->right = new node(5);
  root1->right->left = new node(6);
  root1->right->right = new node(0);

  validity = isMinHeap(root1, true);

  cout << endl;
  cout << "Test 2" << endl;

  if(validity == true) //Should output false.
    cout << "This is a valid minheap." << endl;
  else
    cout << "This is not a valid minheap." << endl;

/////////////////////////////////////////////////////

  //Making a tree that is not a min heap. From write-up.
  node* root2 = new node(2);
  root2->left = new node(1);
  root2->right = new node(6);
  root2->right->left = new node(5);
  root2->right->right = new node(8);

  validity = isMinHeap(root2, true);

  cout << endl;
  cout << "Test 3" << endl;

  if(validity == true)
    cout << "This is a valid minheap." << endl;
  else
    cout << "This is not a valid minheap." << endl;

  return 0;
}
