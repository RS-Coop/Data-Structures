#include "HW4-Todo-StackArray.hpp"
#include <iostream>

using namespace std;

TodoStackArray::TodoStackArray()
{
  stackTop = -1;
}

bool TodoStackArray::isEmpty()
{
  return(stackTop<0);
}
bool TodoStackArray::isFull()
{
  return(stackTop+1==MAX_STACK_SIZE);
}
void TodoStackArray::push(string todoItem)
{
  if(!isFull())
  {
    TodoItem item;
    item.todo = todoItem;
    stack[++stackTop] = item;
  }
  else
  {
    cout << "Stack full, cannot add new todo item." << endl;
  }
}
void TodoStackArray::pop()
{
  if(!isEmpty())
  {
    stackTop--;
  }
  else
  {
    cout << "Stack empty, cannot pop an item." << endl;
  }
}
TodoItem TodoStackArray::peek()
{
  if(!isEmpty())
  {
    return (stack[stackTop]);
  }
  else
  {
    cout << "Stack empty, cannot peek." << endl;
    TodoItem item;
    item.todo = "Empty";
    return item;
  }
}
