#include <iostream>
#include <vector>

using namespace std;

struct node
{
  node* left;
  node* right;
  int value;
};
class binaryTree
{
public:
  node* root;

  binaryTree()
  {
    root = NULL;
  }
  void addNode(int data)
  {
    node newNode;
    newNode.value = data;

    node* temp = root;

    if(temp!= NULL) cout << temp->value << endl;

    if(temp == NULL)
    {
      cout << "Root" << endl;
      this->root = &newNode;
      cout << root->value << endl;
    }

    else
    {
      cout << "here" << endl;
      while(temp != NULL)
      {
        if(data < temp->value)
        {
          cout << "Left" << endl;
          if(temp->left == NULL)
          {
            temp->left = &newNode;
            return;
          }
          else
          {
            temp = temp->left;
          }
        }
        else if(data > temp->value)
        {
          cout << "Right" << endl;
          if(temp->right == NULL)
          {
            temp->right = &newNode;
            return;
          }
          else
          {
            temp = temp->right;
          }
        }
      }
    }
  }
  int calculateProduct(node* root)
  {
    int prod = 1;

    if(root == NULL) return prod;

    prod = calculateProduct(root->left);

    prod = root->value*prod;

    prod = calculateProduct(root->right);

    return prod;

  }
  void printTree(node* root)
  {
    if(root == NULL) return;

    printTree(root->left);

    cout << "Node: " << root->value;

    printTree(root->right);
  }
};

int main()
{
  binaryTree T1;

  T1.addNode(5);
  T1.addNode(3);
  T1.addNode(6);
  cout << "Here" << endl;

  T1.printTree(T1.root);

  return 0;
}
