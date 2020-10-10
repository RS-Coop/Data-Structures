#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class Movie
{
private:
  string title;
  int year;
  float rating;

public:
  Movie()
  {
    title = "unknown";
    year = 2018;
    rating = 0.0;
  }
  Movie(string newTitle, int newYear, float newRating)
  {
    title = newTitle;
    year = newYear;
    rating = newRating;
  }

  string getTitle()
  {
    return title;
  }
  void setTitle(string newTitle)
  {
    title = newTitle;
  }

  int getYear()
  {
    return year;
  }
  void setYear(int newYear)
  {
    year = newYear;
  }

  float getRating()
  {
    return rating;
  }
  void setRating(float newRating)
  {
    rating = newRating;
  }

};

int main
