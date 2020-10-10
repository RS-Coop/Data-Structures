#include <iostream>
#include <ctime>

#include "phraseGraph.hpp"

using namespace std;

int main(int argc, char *argv[]){

  // Welcome
  cout << "Welcome to the Weighted Graph Phrase Generator" << endl;

  // Seading the random number generator
  srand(time(NULL));

  // Boolean Flags to check the loading status for each catagory
  bool news_load = false;
  bool book_load = false;
  bool movie_load = false;
  bool quip_load = false;
  bool wQuote_load = false;

  // Input variables for the word generator
  string headlineWord, S_newsLength;
  string bookWord, S_bookLength;
  string movieWord, S_movieLength;
  string quipWord, S_quipLength;
  string wiseWord, S_wiseLength;

  int newsLength, bookLength, movieLength, quipLength, wiseLength;

  // Menu variables
  bool quit = false;
  string s_input;
  int input;

  phraseGraph newsGraph;
  phraseGraph bookGraph;
  phraseGraph movieGraph;
  phraseGraph quipGraph;
  phraseGraph wQuoteGraph;


  while (!quit){
    cout << "____ Please Choose a genre: ____" << endl;
    cout << "1. Newspaper Headlines" << endl; // Not sure how to limit this data set
    cout << "2. Book Titles" << endl; //CHECK
    cout << "3. Movie Titles" << endl; //CHECK
    cout << "4. Quiplash Prompts" << endl; //CHECK
    cout << "5. Wise Quotes" << endl; // Probably check
    cout << "6. Quit" << endl;

    // Read in an input and enter the menu
    getline(cin, s_input);
    input = stoi(s_input);
    switch (input){

    case 1: // Newspaper Headlines

      //phraseGraph newsGraph;

      // Checking if the news headlines graph has been constucted
      if(news_load == false){

        cout << "Loading Newspaper Headlines Generator..." << endl;

        newsGraph.buildNewsGraph("thousandHeadlines.txt");

        news_load = true;
      }

        // The Graph has been created
        // The user can now interact with it
        cout << "Please enter the first word: ";
        getline(cin, headlineWord);
        cout << "Please choose a length between 5 and 10 words: ";
        getline(cin, S_newsLength);
        cout << endl;

        newsLength = stoi(S_newsLength);

        cout << "Your generated phrase: " << endl;
        newsGraph.generatePhrase(headlineWord, newsLength);
        cout << endl;

        break;

      case 2: // Book Titles

        //phraseGraph bookGraph;

        // Checking if the book title graph has been constucted
        if(book_load == false){

          cout << "Loading Book Title Generator..." << endl;

          bookGraph.buildBookGraph("thousandBooks.txt");

          book_load = true;
        }

          // The Graph has been created
          // The user can now interact with it
          cout << "Please enter the first word: ";
          getline(cin, bookWord);
          cout << "Please choose a length between 2 and 5 words: ";
          getline(cin, S_bookLength);
          cout << endl;

          bookLength = stoi(S_bookLength);

          cout << "Your generated title: " << endl;
          bookGraph.generatePhrase(bookWord, bookLength);
          cout << endl;

          break;


      case 3: // Movie Titles

        //phraseGraph movieGraph;

        // Checking if the movie title graph has been constucted
        if(movie_load == false){
          cout << "Loading Movie Title Generator..." << endl;

          movieGraph.buildMovieGraph("thousandMovies.txt");

          movie_load = true;
        }

          // The Graph has been created
          // The user can now interact with it
          cout << "Please enter the first word: ";
          getline(cin, movieWord);
          cout << "Please choose a length between 2 and 5 words: ";
          getline(cin, S_movieLength);
          cout << endl;

          movieLength = stoi(S_movieLength);

          cout << "Your generated title: " << endl;
          movieGraph.generatePhrase(movieWord, movieLength);
          cout << endl;

          break;


      case 4: // Quiplash Prompts

        // Checking if the motivational quotes graph has been constucted
        if(quip_load == false){
          cout << "Loading Quiplash Prompt Generator..." << endl;

          quipGraph.buildQuipGraph("thousandQuips.txt");

          quip_load = true;
        }

          // The Graph has been created
          // The user can now interact with it
          cout << "Please enter the first word: ";
          getline(cin, quipWord);
          cout << "Please choose a length between 5 and 20 words: ";
          getline(cin, S_quipLength);
          cout << endl;

          quipLength = stoi(S_quipLength);

          cout << "Your generated prompt: " << endl;
          quipGraph.generatePhrase(quipWord, quipLength);
          cout << endl;

          break;

      case 5: // Wise Quotes

        // Checking if the wise quotes graph has been constucted
        if(wQuote_load == false){
          cout << "Loading Wise Quotes Generator..." << endl;

          wQuoteGraph.buildQuoteGraph("WiseQuotes_List.txt");

          wQuote_load = true;
        }

          // The Graph has been created
          // The user can now interact with it
          cout << "Please enter the first word: ";
          getline(cin, wiseWord);
          cout << "Please choose a length between 5 and 20 words: ";
          getline(cin, S_wiseLength);
          cout << endl;

          wiseLength = stoi(S_wiseLength);

          cout << "Your generated quote: " << endl;
          wQuoteGraph.generatePhrase(wiseWord, wiseLength);
          cout << endl;

          break;


      case 6: // QUIT
        quit = true;
        cout << "Goodbye!" << endl;
        break;

      default: // Invalid input
        cout << "Invalid Input, Please Try Again" << endl;
        break;
    }
  }


}
