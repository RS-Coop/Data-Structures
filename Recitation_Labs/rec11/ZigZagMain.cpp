#include"BinaryTree.hpp"
#include <stack>

/*
***************************************************************************
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                      Implement this function
    This function prints all the elements in a tree in a zigzag order
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
***************************************************************************
*/

void Tree::ZigZagTraverse(Node *root)
{
  // if null then return
  if (!root)
  {
    return;
  }

  queue<Node*> queue;
  stack<int> stack;

  // push the root
  queue.push(root);

  // Push a marker to indicate end of level
  queue.push(NULL);

  // Tells us if we need to print elements left to right
  // or right to left
  bool lefttoright = true;

  while (!queue.empty())
  {

    // Done with traversing all the levels
    // Break the loop
    if(queue.size() == 1 && queue.front() == NULL)
    {
      break;
    }

    // pop out of queue
    Node *temp = queue.front();
    queue.pop();

    if(temp == NULL)
    {
      // Marker for next level
      queue.push(NULL);

      // Print the elements from the stack
      // Prints a level in right to left fashion
      if(!lefttoright)
      {
        // Print the contents of the stack and empty it
        while(!stack.empty())
        {
          cout << stack.top() << "-->";
          stack.pop();
        }
      }

      // Invert the order for next level
      if(lefttoright)
        lefttoright = false;
      else
        lefttoright = true;
    }
    else
    {
      // Print the elements normally
      if(lefttoright)
      {
        cout<<temp->data << "-->";
      }
      else
      {
        // Push the elements into stack
        stack.push(temp->data);
      }

      // Add the node's children to the queue
      if(temp->left != NULL)
        queue.push(temp->left);
      if(temp->right != NULL)
        queue.push(temp->right);
    }
  }
}

/*
Main function that calls create tree, print Tree and the traversal function.
*/
int main()
{
  Tree t;
  t.createTree();
  //cout<<t.root->data<<endl;
  t.print2DUtil(t.root, 0);

  cout << "Zig Zag traversal of binary tree is \n";
  t.ZigZagTraverse(t.root);
  cout<<endl;

  return 0;
}
