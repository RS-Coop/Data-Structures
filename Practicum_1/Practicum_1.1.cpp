#include <iostream>

using namespace std;

struct Node //Node structure.
{
  int data;
  Node *next;
  Node(int data);
  Node();
};

Node::Node(int data)
{
	this->data = data;
	this->next = NULL;
}
Node::Node()
{}

class LinkedList //Linked list class from previous class work
{
public:
	Node *head;
	int size;
	LinkedList();

	// Insert and traversal Functions
	void insertAtHead(int data);
	void insertAtIndex(int index, int data);
	void insertAtTail(int data);
	int getValAtIndex(int index);
	void printList();

  // Delete functions
	bool deleteAtHead();
	bool deleteAtIndex(int index);
	bool deleteAtTail();

};

LinkedList::LinkedList() //Constructor for linked list.
{
	this->size = 0;
	this->head = NULL;
}

void LinkedList::insertAtHead(int data) //Inserts new node at the head of the list.
{
	Node *newNode = new Node(data);
	newNode->next = this->head;
	this->head = newNode;
	this->size++;
}

void LinkedList::printList() //Prints the list in the class.
{
	Node *temp = this->head;
	while(temp->next != NULL)
	{
		cout<<temp->data;
		cout<<"->";
		temp = temp->next;
	}
	cout<<temp->data;
	cout<<" "<<endl;
}

bool lengthIsEven(Node *head) //Returns true if even amount of elements or false if not.
{
  if(head == NULL) //If there are no elements return true.
  {
    return true;
  }
  else
  {
    Node *temp = new Node;
    temp = head;
    int i = 0; //Counter.
    while(temp->next != NULL) //Iterates through all but last element of list.
    {
      i++; //Counts elements.
      temp = temp->next;
    }
    i++; //Counts last element.

    if(i%2 == 0) //If divisible by two and thus even.
    {
      return true;
    }
    else return false; //Odd if not divisible by two.
  }
}

int main()
{
  //Creates four linked lists for test cases.
  LinkedList L1;
  LinkedList L2;
  LinkedList L3;
  LinkedList L4;

  L1.insertAtHead(1);
  L1.insertAtHead(5);
  L1.insertAtHead(3);
  L1.insertAtHead(10);
  L1.insertAtHead(7);
  L1.insertAtHead(2);

  L1.printList();

  cout << lengthIsEven(L1.head) << endl; //Should be true as there are six elements.

  L2.insertAtHead(3);
  L2.insertAtHead(2);
  L2.insertAtHead(0);
  L2.insertAtHead(9);
  L2.insertAtHead(7);

  L2.printList();

  cout << lengthIsEven(L2.head) << endl; //Should be false as there are five elements.

  L3.insertAtHead(1);

  L3.printList();

  cout << lengthIsEven(L3.head) << endl; //Should be false as there is one element.

  cout << lengthIsEven(L4.head) << endl; //Should be true as there are no elements.

  return 0;
}
