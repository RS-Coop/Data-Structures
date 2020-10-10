#include <iostream>
#include <vector>

using namespace std;

struct node
{
  node* left;
  node* right;
  int value;

  node()
  {
    left = NULL;
    right = NULL;
    value = 1;
  }
};

int calculateProduct(node* root, int prod)
{
  if(root == NULL) return prod;

  prod = calculateProduct(root->left,prod);

  prod = root->value*prod;
  cout << prod << endl;

  prod = calculateProduct(root->right,prod);

  return prod;
}

void printTree(node* root)
{
  if(root == NULL) return;

  printTree(root->left);

  cout << "Node: " << root->value;

  printTree(root->right);
}

int main()
{
  node root, nl1, nl2, nr1, nr2;

  root.value = 5;
  nl1.value = 3;
  nl2.value = 4;
  nr1.value = 2;
  nr2.value = 1;

  root.left = &nl1;
  root.right = &nr1;
  nl1.left = &nl2;
  nl1.right = &nr2;

  printTree(&root);

  cout << endl;

  cout << "Product = " << calculateProduct(&root,1) << endl;

  return 0;
}
