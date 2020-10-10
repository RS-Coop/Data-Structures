#include "HW4-Todo-QueueArray.hpp"
#include <iostream>

using namespace std;

TodoQueueArray::TodoQueueArray()
{
  queueFront = -1;
  queueEnd = -1;
}
bool TodoQueueArray::isEmpty()
{
  return(queueFront < 0);
}
bool TodoQueueArray::isFull()
{
  return((queueEnd+1)%MAX_QUEUE_SIZE == queueFront ? true : false);
}

void TodoQueueArray::enqueue(string todoItem)
{
  if(!isFull())
  {
    TodoItem item;
    item.todo = todoItem;

    if(isEmpty())
    {
      queue[++queueFront] = item;
      queueEnd++;
    }
    else
    {
      queueEnd = (queueEnd+1)%MAX_QUEUE_SIZE;
      queue[queueEnd] = item;
    }
  }
  else
  {
    cout << "Queue full, cannot add new todo item." << endl;
  }
}
void TodoQueueArray::dequeue()
{
  if(!isEmpty())
  {
    if(queueFront == queueEnd)
    {
      queueEnd = -1;
      queueFront = -1;
    }
    else
    {
    queueFront = (queueFront+1)%MAX_QUEUE_SIZE;
    }
  }
  else
  {
    cout << "Queue empty, cannot dequeue an item." << endl;
  }
}
TodoItem TodoQueueArray::peek()
{
  if(!isEmpty())
  {
    return(queue[queueFront]);
  }
  else
  {
    TodoItem item;
    item.todo = "Empty";
    cout << "Queue empty, cannot peek." << endl;
    return item;
  }
}
