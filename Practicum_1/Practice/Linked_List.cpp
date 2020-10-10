#include <iostream>

using namespace std;

struct Node
{
  int key;
  Node *next;
};

class LinkedList
{
  private:
    Node *head;

  public:
    LinkedList()
    {
      head = NULL;
    }

    Node* getHead()
    {
      return head;
    }

    void setHead(Node *newhead)
    {
      head = newhead;
    }

    void addFront(int data)
    {
      Node *newnode = new Node;
      newnode->key = data;
      newnode->next = head;
      head = newnode;
    }

    void printList()
    {
      if (head == NULL)
      {
        cout << "There is no list." << endl;
      }
      else
      {
        Node *temp = head;
        while(temp->next != NULL)
        {
          cout << temp->key << "->";
          temp = temp->next;
        }
        cout << temp->key;
        cout << endl;
      }
    }
};

int maximum(Node *head);
Node* deleteIndex(Node *head, int index);
Node* reverse(Node* head);

int main()
{
  LinkedList L1;

  cout << maximum(L1.getHead()) << endl;

  L1.addFront(2);
  L1.addFront(6);
  L1.addFront(1);
  L1.addFront(5);
  L1.addFront(9);

  L1.printList();

  cout << maximum(L1.getHead()) << endl;

  // L1.setHead(deleteIndex(L1.getHead(),0));
  // L1.printList();
  // L1.setHead(deleteIndex(L1.getHead(),2));
  // L1.printList();
  // L1.setHead(deleteIndex(L1.getHead(),2));

  reverse(L1.getHead());
  L1.printList();
}

int maximum(Node *head)
{
  if (head == NULL)
  {
    cout << "There is no list." << endl;
    return 0;
  }
  else
  {
    int max = head->key;
    Node *temp = head;
    while(temp->next != NULL)
    {
      if(temp->key > max)
      {
        max = temp->key;
      }
      temp = temp->next;
    }
    return max;
  }
}

Node* deleteIndex(Node *head, int index)
{
  if(head == NULL)
  {
    cout << "The list is empty." << endl;
    return head;
  }
  else
  {
    Node *temp = new Node;
    temp = head;
    int i = 0;

    if(index == 0)
    {
      head = temp->next;
      delete temp;
      return head;
    }

    else
    {
      while(i<index-1)
      {
        temp = temp->next;
        i++;
      }
      temp->next = temp->next->next;
      delete temp->next;
      return head;
    }
  }
}

Node* reverse(Node* head)
{
  if(head != NULL)
  {
    Node *first = head;
    Node *rest = head->next;

    while(rest != NULL)
    {
      rest = reverse(rest);
      rest->next = first;
    }
    first->next = NULL;

    return rest;
  }
  else
  {
    cout << "The list is empty." << endl;
    return head;
  }
}
