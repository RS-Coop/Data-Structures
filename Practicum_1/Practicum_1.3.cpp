#include <iostream>

using namespace std;

void resize(int **arrayPtr, int *capacity);
void halfSize(int **arrayPtr, int *capacity);

class StackArray //Class for a stack.
{
public:
  StackArray();
  bool isEmpty();
  bool isFull();
  void push(int num);
  void pop();
  int getStackTop() { return stackTop; }
  int* getStack() { return stack; }
  void printStack();
private:
  int stackTop; //the index in stack[] that will be popped next
  int size;
  int capacity;
  int *stack;
};

StackArray::StackArray()
{
  stackTop = -1;
  size = 0;
  capacity = 5;
  stack = new int[capacity];
}

bool StackArray::isEmpty()
{
  return(stackTop<0);
}
bool StackArray::isFull()
{
  return(stackTop+1==capacity);
}
void StackArray::push(int num)
{
  if(!isFull())
  {
    stack[++stackTop] = num;
  }
  else //If stack is full resize and add the new value.
  {
    resize(&stack, &capacity);
    stack[++stackTop] = num;
  }
}
void StackArray::pop()
{
  if(!isEmpty())
  {
    stackTop--; //First pop the item.

    if(capacity/2 >= stackTop+1) //Check to see if stack is half empty. If so resize.
    {
      halfSize(&stack, &capacity);
    }
  }
  else
  {
    cout << "Stack empty, cannot pop an item." << endl;
  }
}

void resize(int **arrayPtr, int *capacity) //Doubles the size of an array.
{
	int newCapacity = *capacity*2;
	int *newArray = new int [newCapacity];

	for(int i=0; i<*capacity; i++)
	{
		*(newArray+i) = *(*arrayPtr+i);
	}
	delete [] *arrayPtr;

	*arrayPtr = newArray;
	*capacity = newCapacity;

  //cout << "The capacity is: " << *capacity << endl;

  //return *capacity;
}

void halfSize(int **arrayPtr, int *capacity) //Halves the size of an array.
{
	int newCapacity = *capacity/2;
	int *newArray = new int [newCapacity];

	for(int i=0; i<*capacity; i++)
	{
		*(newArray+i) = *(*arrayPtr+i);
	}
	delete [] *arrayPtr;

	*arrayPtr = newArray;
	*capacity = newCapacity;

  //return *capacity;
}

void StackArray::printStack() //Prints the entire stack from the top down.
{
  for(int i=stackTop; i>=0; i--)
  {
    cout << stack[i] << endl;
  }
  cout << "The capacity is: " << capacity << endl;
  cout << "There are " << stackTop+1 << " elements" << endl;
}

int main()
{
  //What follows is a series of test cases.

  StackArray S1; //Defines an instance of a stack.

  S1.push(5);
  S1.push(3);
  S1.push(7);
  S1.push(8);
  S1.push(6);

  S1.printStack(); //Stack should be five elements with a cap of 5.
  cout << "##########" << endl;

  S1.pop();

  S1.printStack(); //Stack should be four elements with a cap of 5.
  cout << "##########" << endl;

  S1.push(69);
  S1.push(21);
  S1.push(46);
  S1.push(3);

  S1.printStack(); //Stack should be eight elements with a cap of 10;
  cout << "##########" << endl;

  S1.pop();
  S1.pop();
  S1.pop();
  S1.pop();

  S1.printStack(); //Stack should be four elements with a cap of 5.
  cout << "##########" << endl;

  S1.push(5);
  S1.push(3);
  S1.push(7);
  S1.push(9);
  S1.push(10);
  S1.push(3);
  S1.push(2);
  S1.push(0);
  S1.push(6);
  S1.push(4);
  S1.push(534);
  S1.push(23);
  S1.push(51);
  S1.push(59);
  S1.push(56);

  S1.printStack(); //Stack should be ninteen elements with a cap of 20.
  cout << "##########" << endl;

  S1.push(43);
  S1.push(11);

  S1.printStack(); //Stack should be twenty-one elements with a cap of 40.
  cout << "##########" << endl;

  S1.pop();
  S1.pop();
  S1.pop();
  S1.pop();
  S1.pop();
  S1.pop();
  S1.pop();
  S1.pop();
  S1.pop();
  S1.pop();
  S1.pop();

  S1.printStack(); //Stack should be ten elements with a cap of 10.
  cout << "##########" << endl;

  return 0;
}
