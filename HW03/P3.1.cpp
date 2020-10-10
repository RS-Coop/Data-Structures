// ==========================================
// File: Assignment 3 starter code
// Author: Matt Bubernak
// Date: 1/29/2015
// Modified: Fall 2016 E.S.Boese
// Fall 2017 W.Temple
// Description: Linked List Fun
// Modified: Fall 2018 Cooper Simpson
// CSCI 2270 - Data Structures Assignment 3
// ==========================================
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

// DO NOT MODIFY THIS STRUCT
struct city
{
  string name; // name of the city
  city *next; // pointer to the next city
  int numberMessages; // how many messages passed through this city
  string message; // message we are sending accross
};

/* Function prototypes */
city* addCity(city *head, city *previous, string cityName );
city* deleteCity(city *head, string cityName);
city* deleteEntireNetwork(city *head);
city* searchNetwork(city *head, string cityName);
city* loadDefaultSetup(city *head);
void transmitMsg(city *head, string receiver, string filename);
void printPath(city *head);
void displayMenu();
city* handleUserInput(city *head);

/* Do NOT modify main function */
int main(int argc, char* argv[])
{
  // pointer to the head of our network of cities
  city *head = NULL;

  head = handleUserInput(head);
  printPath(head);
  head = deleteEntireNetwork(head);
  if (head == NULL)
  cout << "Path cleaned" << endl;
  else
  printPath(head);
  cout << "Goodbye!" << endl;
  return 0;
}

/*
 * Purpose: handle the interaction with the user
 * @param head: the start of the linked list
 * @return: the start of the linked list
 *
 * DO NOT MODIFY THIS FUNCTION
 */
city* handleUserInput(city *head)
{
  bool quit = false;
  string s_input;
  int input;
  // loop until the user quits
  while (!quit)
  {
    displayMenu();
    // read in input, assuming a number comes in
    getline(cin, s_input);
    input = stoi(s_input);
    switch (input)
    {
      // print all nodes
      case 1: //rebuild network
        head = loadDefaultSetup(head);
        //printPath(head);
        break;

      case 2: // print path
        printPath(head);
        break;

      case 3: //message is read in from file
        {
          string cityReceiver;

          cout << "Enter name of the city to receive the message: "
          << endl;
          getline(cin, cityReceiver);
          cout << "Enter the message to send: " << endl;
          string message;
          getline(cin, message);

          transmitMsg(head, cityReceiver, message);
        }
        break;

      case 4:
        {
          string newCityName;
          string prevCityName;
          cout << "Enter a new city name: " << endl;
          getline(cin, newCityName);
          cout << "Enter the previous city name (or First): " << endl;
          getline(cin, prevCityName);
          // find the node containing prevCity
          city *tmp = NULL;
          if(prevCityName !="First")
          tmp = searchNetwork(head, prevCityName);
          // add the new node
          head = addCity(head, tmp, newCityName);
          printPath(head);
        }
        break;

      case 5: // delete city
        {
          string city;
          cout << "Enter a city name: " << endl;
          getline(cin, city);
          head = deleteCity(head, city);
          printPath(head);

        }
        break;

      case 6: // delete network
        head = deleteEntireNetwork(head);
        break;

      case 7: // quit
        quit = true;
        cout << "Quitting... cleaning up path: " << endl;
        break;

      default: // invalid input
        cout << "Invalid Input" << endl;
        break;
    }
  }
  return head;
}

/*
 * Purpose: Add a new city to the network
 * between the city *previous and the city that follows it in the network.
 * Prints: `prev: <city name> new: <city name>` when a city is added,
 * prints _nothing_ if the city is being added to the _first_ position in
 * the list.
 * @param head: pointer to start of the list
 * @param previous: name of the city that comes before the new city
 * @param cityName: name of the new city
 * @return: pointer to first node in list
 */
city* addCity(city *head, city *previous, string cityName )
{
  city *newCity = new city;
  newCity->name = cityName;

  city *path = head;

  if(previous == NULL)
  {
    newCity->next = path;
    newCity->message = "";
    newCity->numberMessages = 0;
    head = newCity;
    return head;
  }

  else
  {
    while(path != NULL)
    {
      if(path == previous)
      {
        newCity->next = previous->next;
        previous->next = newCity;
        break;
      }
      path = path->next;
    }

    cout << "prev: " << previous->name << "  new: " << cityName << endl;
    return head;
  }
}

/*
 * Purpose: Search the network for the specified city and return a pointer
 * to that node
 * @param head: head of the list
 * @param cityName: name of the city to look for in network
 * @return: pointer to node of cityName, or NULL if not found
 * @see addCity, deleteCity
 */
 city* searchNetwork(city *head, string cityName)
 {
   city *path = head;

   while(path != NULL)
   {
     if(path->name == cityName)
     {
       return path;
     }
     path = path->next;
   }

   return path;
 }

/*
 * Purpose: deletes all cities in the network starting at the head city.
 * @param head: head of list
 * @return: NULL as the list is empty
 */
city* deleteEntireNetwork(city *head)
{
  if(head != NULL)
  {
    city * temp;
    temp = head;

    while(head->next != NULL)
    {
      cout << "deleting: " << head->name << endl;
      head = head->next;
      delete temp;
      temp = head;
    }
    cout << "deleting: " << head->name << endl;
    delete head;
    head = NULL;

    cout << "Deleted network" << endl;
  }

  return head;
}

/*
 * Purpose: transmit a message from city to city
 * @param head: pointer to head of the list
 * @param receiver: the name of the City to receive the message
 * @param message: the message to transmit*/
void transmitMsg(city *head, string receiver, string message)
{
  if(head == NULL)
  {
    cout << "Empty list" << endl;
    return;
  }

  city *sender = head;
  // Use the following output statements to print each node of the linked list:

  while(sender->next != NULL)
  {
    (sender->numberMessages)++;
    sender->message = message;

    cout << sender->name << " [# messages passed: " <<
    sender->numberMessages << "] received: " <<
    sender->message << endl;

    if(sender->name == receiver)
    {
      break;
    }

    sender = sender->next;
  }
}

/*
 * Purpose: delete the city in the network with the specified name.
 * @param head: first node in list
 * @param cityName: name of the city to delete in the network
 * @return: head node of list
 */
city* deleteCity(city *head, string cityName)
{
  city *pres;
  city *cur = head;

  if(cur->name == cityName)
  {
    pres = cur;
    cur = cur->next;
    delete pres;
    return cur;
  }

  while(cur->next != NULL)
  {
    if(cur->name == cityName)
    {
      pres->next = cur->next;
      delete cur;

      return head;
    }
    pres = cur;
    cur = cur->next;
  }

  // If the city dosn't exist, use this output statement:
  cout << "City does not exist." << endl;

  return head;
}

/*
 * Purpose: prints the current list nicely
 * @param head: head of list
 */
void printPath(city *head)
{
  city *path = head;

  cout << "== CURRENT PATH ==" << endl;
  if (head == NULL) {
    cout << "nothing in path" << endl;
  }

  else
  {
    while(path->next != NULL)
    {
      cout << path->name << " -> ";
      path = path->next;
    }
    cout << path->name << " -> " << " NULL" << endl;

    cout << "===" << endl;
  }
}

/*
 * Purpose: populates the network with the predetermined cities
 * @param head: start of list
 * @return: head of list
 */
city* loadDefaultSetup(city *head)
{
  head = deleteEntireNetwork(head);
  head = addCity(head,NULL,"Los Angeles");

  string cities[6] = {"Los Angeles", "Phoenix", "Denver", "Dallas", "Atlanta", "New York"};

  city *prev = head;

  for(int i=1; i<6; i++)
  {
    head = addCity(head,prev,cities[i]);
    prev = prev->next;
  }

  printPath(head);

  return head;
}

/* Purpose: displays a menu with options
 * DO NOT MODIFY THIS FUNCTION
 */
void displayMenu()
{
  cout << "Select a numerical option:" << endl;
  cout << "======Main Menu=====" << endl;
  cout << "1. Build Network" << endl;
  cout << "2. Print Network Path" << endl;
  cout << "3. Transmit Message" << endl;
  cout << "4. Add City" << endl;
  cout << "5. Delete City" << endl;
  cout << "6. Clear Network" << endl;
  cout << "7. Quit" << endl;
}
