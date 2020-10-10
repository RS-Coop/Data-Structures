#include <iostream>
#include <queue>

using namespace std;

struct Node
{
  int data;
  Node *left;
  Node *right;
  Node(int data)
    {
        this->data = data;
        this->left = this->right = NULL;
    }
};


void LevelOrderTraverse(Node *root)
{
    int height = 0;
    // Base Case
    if (root == NULL)  return;

    // Create an empty queue for level order tarversal
    queue <Node*> q;
    Node* node;
    // Enqueue Root
    q.push(root);

    while (q.empty() == false)
    {
        q.push(NULL);
        // Print front of queue
        node = q.front();
        if(node == NULL)
        {
          height++;
          q.pop();
          node = q.front();
        }
        if(node != NULL)
          cout << node->data << " ";

        q.pop();

        // TODO
        if(node != NULL)
        {
          if(node->left != NULL)
            q.push(node->left);
          if(node->right != NULL)
            q.push(node->right);
        }
    }

    cout << "Height: " << height-1 << endl;
}




int main()
{
  Node* root = new Node(10);
  root->left = new Node(9);
  root->right = new Node(2);
  root->left->left = new Node(3);
  root->right->right = new Node(7);
  root->left->left->left = new Node(4);

  LevelOrderTraverse(root);
}
