#include "PriorityQueue.hpp"
#include <iostream>
using namespace std;

PriorityQueue::PriorityQueue(int queueSize)
{
  maxQueueSize = queueSize;
  currentQueueSize = 0;

  priorityQueue = new PatientNode[maxQueueSize+1];
}
PriorityQueue::~PriorityQueue()
{
  delete[] priorityQueue;
}
void PriorityQueue::enqueue(string _name, int _injurySeverity, int _treatmentTime)
{
  PatientNode newPatient;

  newPatient.name = _name;
  newPatient.injurySeverity = _injurySeverity;
  newPatient.treatmentTime = _treatmentTime;

  if(!isFull())
  {
    priorityQueue[++currentQueueSize] = newPatient;
    repairUpward(currentQueueSize);
  }
  else
    cout << "Priority Queue full. Send Paitent to another hospital" << endl;
}
void PriorityQueue::dequeue()
{
  priorityQueue[1] = priorityQueue[currentQueueSize--];
  repairDownward(1);
}
string PriorityQueue::peekName()
{
  return priorityQueue[1].name;
}
int PriorityQueue::peekInjurySeverity()
{
  return priorityQueue[1].injurySeverity;
}
int PriorityQueue::peekTreatmentTime()
{
  return priorityQueue[1].treatmentTime;
}
bool PriorityQueue::isFull()
{
  if(currentQueueSize == maxQueueSize)
    return true;
  else
    return false;
}
bool PriorityQueue::isEmpty()
{
  if(currentQueueSize == 0)
    return true;
  else
    return false;
}
void PriorityQueue::repairUpward(int nodeIndex)
{
  int parent = nodeIndex/2;

  int big = nodeIndex;
  PatientNode temp;

  if(parent >= 1 && priorityQueue[big].injurySeverity > priorityQueue[parent].injurySeverity)
    big = parent;
  else if(parent >=1 && priorityQueue[big].injurySeverity == priorityQueue[parent].injurySeverity
    && priorityQueue[big].treatmentTime < priorityQueue[parent].treatmentTime)
      big = parent;

  if(big != nodeIndex)
  {
    temp = priorityQueue[big];
    priorityQueue[big] = priorityQueue[nodeIndex];
    priorityQueue[nodeIndex] = temp;
    repairUpward(big);
  }
}
void PriorityQueue::repairDownward(int nodeIndex)
{
  int left = nodeIndex*2;
  int right = nodeIndex*2 + 1;

  int small = nodeIndex;
  PatientNode temp;

  if(left <= currentQueueSize && priorityQueue[small].injurySeverity < priorityQueue[left].injurySeverity)
    small = left;
  else if(left <= currentQueueSize && priorityQueue[small].treatmentTime > priorityQueue[left].treatmentTime
    && priorityQueue[small].injurySeverity == priorityQueue[left].injurySeverity)
    small = left;
  if(right <= currentQueueSize && priorityQueue[right].injurySeverity > priorityQueue[small].injurySeverity)
    small = right;
  else if(right <= currentQueueSize && priorityQueue[right].treatmentTime < priorityQueue[small].treatmentTime
    && priorityQueue[right].injurySeverity == priorityQueue[small].injurySeverity)
    small = right;

  if(small != nodeIndex)
  {
    temp = priorityQueue[small];
    priorityQueue[small] = priorityQueue[nodeIndex];
    priorityQueue[nodeIndex] = temp;
    repairDownward(small);
  }
}
