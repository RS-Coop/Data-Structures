#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

struct User
{
  strng username;
  float gpa;
  int age;
};

void addUser(vector<User> *users, string _username, float _gpa, int _age);
void printList(const vector<User> users);

int main(int argc, char *argv[])
{
  ifstream infile(argv[1]);
  string line;

  if(infile.is_open())
  {
    while(getline(infile,line))
    {
      string usrName;
      float GPA;
      int age;

      stringstream ss(line);
      getline(ss,line,',');
      usrName = line;
      getline(ss,line,',');
      GPA = stof(line);
      getline(ss,line,',');
      age = stoi(line);
    }
  }

  else
  {
    cout << "Error";
  }

  infile.close();
  return(0);
}

void addUser(vector<User> *users, string _username, float _gpa, int _age)
{
  User useri;

  useri.username = _username;
  useri.gpa = _gpa;
  useri.age = _age;

  users->push_back(useri);
}

void printList(const vector<User> users)
{
  for(int i=0; i<users.size(); i++)
  {
    cout << users[i].username << " [" << users[i].gpa << "] age: "
    << users[i].age << endl;
  }
}
