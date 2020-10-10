#include "HW4-Todo-StackLinkedList.hpp"
#include <iostream>

using namespace std;

TodoStackLinkedList::TodoStackLinkedList()
{
  stackHead = NULL;
}
TodoStackLinkedList::~TodoStackLinkedList()
{
}
bool TodoStackLinkedList::isEmpty()
{
  return(stackHead==NULL);
}
void TodoStackLinkedList::push(string todoItem)
{
  TodoItem *item = new TodoItem;
  item->todo = todoItem;
  item->next = stackHead;
  stackHead = item;
}
void TodoStackLinkedList::pop()
{
  if(!isEmpty())
  {
    TodoItem *item = stackHead;
    stackHead = stackHead->next;
    delete item;
  }
  else
  {
    cout << "Stack empty, cannot pop an item." << endl;
  }
}
TodoItem* TodoStackLinkedList::peek()
{
  if(!isEmpty())
  {
    return stackHead;
  }
  else
  {
    TodoItem *item = new TodoItem;
    item->todo = "Empty";
    item->next = NULL;
    cout << "Stack empty, cannot peek." << endl;
    return item;
  }
}
