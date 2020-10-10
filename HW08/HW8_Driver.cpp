#include "PriorityQueue.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
  PriorityQueue Q1(atoi(argv[1]));

  bool loop = true;
  string line, name, injury, time;
  int choice, _injury, _time, totalTime = 0;
  ifstream infile;

  while(loop == true)
  {
    cout << "======Main Menu======" << endl;
    cout << "1. Get Patient Information from File" << endl;
    cout << "2. Add Patient to Priority Queue" << endl;
    cout << "3. Show Next Patient" << endl;
    cout << "4. Treat Next Patient" << endl;
    cout << "5. Treat Entire Queue" << endl;
    cout << "6. Quit" << endl;

    getline(cin,line);
    choice = stoi(line);

    switch (choice)
    {
      case 1:
        cout << "Enter a file name:" << endl;
        getline(cin,line);

        infile.open(line);

        if(infile.is_open())
        {
          while(!infile.eof() && !Q1.isFull())
          {
            getline(infile, line);

            stringstream ss(line);

            getline(ss,name,' ');
            getline(ss,injury,' ');
            _injury = stoi(injury);
            getline(ss,time,' ');
            _time = stoi(time);

            Q1.enqueue(name,_injury,_time);
          }
        }
        else
        {
          cout << "Could not open file. Try again." << endl;
        }

        break;
      case 2:
        cout << "Enter Patient Name:" << endl;
        getline(cin,name);
        cout << "Enter Injury Severity:" << endl;
        getline(cin,injury);
        cout << "Enter Treatment Time:" << endl;
        getline(cin,time);
        _injury = stoi(injury);
        _time = stoi(time);

        Q1.enqueue(name, _injury, _time);
        break;
      case 3:
        if(!Q1.isEmpty())
        {
          cout << "Patient Name: " << Q1.peekName() << endl;
          cout << "Injury Severity: " << Q1.peekInjurySeverity() << endl;
          cout << "Treatment Time: " << Q1.peekTreatmentTime() << endl;
        }
        else
          cout << "Queue empty." << endl;
        break;
      case 4:
        if(!Q1.isEmpty())
        {
          cout << "Patient Name: " << Q1.peekName();
          totalTime += Q1.peekTreatmentTime();
          cout << " - Total Time Treating Patients: " << totalTime << endl;
          Q1.dequeue();
        }
        else
          cout << "Queue empty." << endl;
        break;
      case 5:
        if(!Q1.isEmpty())
        {
          while(!Q1.isEmpty())
          {
            cout << "Patient Name: " << Q1.peekName();
            totalTime += Q1.peekTreatmentTime();
            cout << " - Total Time Treating Patients: " << totalTime << endl;
            Q1.dequeue();
          }
        }
        else
          cout << "Queue empty." << endl;
        break;
      case 6:
        cout << "Goodbye!" << endl;
        loop = false;
        break;
      default:
        break;
    }
  }
}
