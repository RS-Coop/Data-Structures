#include "HW4-Todo-QueueLinkedList.hpp"
#include <iostream>

using namespace std;

TodoQueueLinkedList::TodoQueueLinkedList()
{
  queueFront = NULL;
  queueEnd = NULL;
}
TodoQueueLinkedList::~TodoQueueLinkedList()
{
}
bool TodoQueueLinkedList::isEmpty()
{
  return(queueFront == NULL);
}
void TodoQueueLinkedList::enqueue(string todoItem)
{
  TodoItem *item = new TodoItem;
  item->todo = todoItem;
  item->next = NULL;

  if(queueFront == NULL)
  {
    queueFront = item;
    queueEnd = queueFront;
  }
  else
  {
    queueEnd->next = item;
    queueEnd = item;
  }
}
void TodoQueueLinkedList::dequeue()
{
  if(!isEmpty())
  {
    TodoItem *temp = queueFront;
    queueFront = queueFront->next;
    delete temp;
  }
  else
  {
    cout << "Queue empty, cannot dequeue an item." << endl;
  }
}
TodoItem* TodoQueueLinkedList::peek()
{
  if(!isEmpty())
  {
    return queueFront;
  }
  else
  {
    TodoItem *item = new TodoItem;
    cout << "Queue empty, cannot peek." << endl;
    return item;
  }
}
