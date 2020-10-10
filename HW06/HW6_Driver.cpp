#include "HW6_Functions.cpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
  ifstream infile(argv[1]);

  string line, word2;
  int rank, year, quantity;
  stringstream ss;
  MovieTree T1;

  if(infile.is_open())
  {
    while(getline(infile,line))
    {
      //getline(infile,line);
      stringstream ss(line);
      //cout << "Here" << endl;
      getline(ss,line,',');
      //cout << line << endl;
      //cout << temp <<endl;
      rank = stoi(line);
      getline(ss,word2,',');
      //cout << word2 << endl;
      getline(ss,line,',');
      //cout << line << endl;
      year = stoi(line);
      getline(ss,line);
      //cout << line << endl;
      quantity = stoi(line);

      T1.addMovieNode(rank, word2, year, quantity);
    }
    
    infile.close();
  }
  else
  {
    cout << "error" << endl;
  }


  bool loop = true;
  int choice;

  while(loop == true)
  {
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Rent a movie" << endl;
    cout << "3. Print the inventory" << endl;
    cout << "4. Delete a movie" << endl;
    cout << "5. Count movies" << endl;
    cout << "6. Quit" << endl;

    getline(cin,line);
    choice = stoi(line);

    switch (choice)
    {
      case 1:
        cout << "Enter title: " << endl;
        getline(cin,word2);
        //cout << "here" << endl;
        T1.findMovie(word2);
        break;
      case 2:
        cout << "Enter title: " << endl;
        getline(cin,word2);
        T1.rentMovie(word2);
        break;
      case 3:
        T1.printMovieInventory();
        break;
      case 4:
        cout << "Enter a title:" << endl;
        getline(cin,word2);
        T1.deleteMovie(word2);
        break;
      case 5:
        T1.countMovies();
        break;
      case 6:
        cout << "Goodbye!" << endl;
        loop = false;
        break;
      default:
        cout << "You have not entered a valid choice. Please enter a valid number 1-4";
        break;
    }
  }
}
