/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"		// for DEQUE
using namespace std;

/************************************************
 * CLASS REQUEST
 * Contains the request data fields
 ***********************************************/
class Request 
{
public:
	Request()
	{
		this->clas ="";
		this->urgent ="";
		this->name = "";
		this->minutes = NULL;
	}
	Request(string urgent, string clas, string name, int minutes)
	{
		this-> urgent=urgent;
		this-> clas=clas;
		this-> name=name;
		this-> minutes=minutes;
	}
	Request(const Request & rhs) 
	{
		urgent = rhs.urgent;
		clas = rhs.clas;
		name = rhs.name;
		minutes = rhs.minutes;
	}
	~Request()
	{
	}
	Request& operator = (const Request& rhs)
	{
		this->urgent = rhs.urgent;
		this->clas = rhs.clas;
		this->name = rhs.name;
		this->minutes = rhs.minutes;
		return *this;
	}
	Request& operator [] (int i)
	{
		return *this;
	}
	string clas;
	string urgent;
	string name;
	int minutes;
};
/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   std::cout << "Every prompt is one minute.  The following input is accepted:\n";
   std::cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   std::cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   std::cout << "\tnone                         : no new request this minute\n";
   std::cout << "\tfinished                     : end simulation\n";

   // your code here

   int timeGeneral = 0;
   string command;
   string clas;
   string name;
   int minutes;
   string urgent = "";
   custom::deque<Request*> maindeque;
   while (true)
   {
	   std::cout << "<" << timeGeneral++ << "> ";
	   cin >> command;

	   try
	   {
		   if (command == "!!")
		   {
			   urgent = command;
			   cin >> clas;
			   cin >> name;
			   cin >> minutes;
			   //Request* req = new Request(urgent, clas, name, minutes);
			   if (maindeque.size()>0 /*&& maindeque.front()->minutes < 2*/)
			   {
				   Request* temp = maindeque.front();
				   maindeque.pop_front();
				   maindeque.push_front(new Request(urgent, clas, name, minutes));
				   maindeque.push_front(temp);
			   }
			   else
			   {
				   maindeque.push_front(new Request(urgent, clas, name, minutes));
			   }
			   
			   
		   }
		   else if (command == "finished")
		   {
			   break;
		   }
		   else if (command != "none")
		   {
			   cin >> name;
			   cin >> minutes;
			   urgent = "";
			   clas = command;
			   maindeque.push_back(new Request(urgent, clas, name, minutes));
		   }
		   //display queue
		   
		   if (maindeque.size()>0 && maindeque.front()->minutes>0)
		   {
			   if (maindeque.front()->urgent != "!!")
			   {
				   std::cout << '\t' << "Currently serving " << maindeque.front()->name
					   << " for class " << maindeque.front()->clas << ". Time left: "
					   << maindeque.front()->minutes << '\n';
					   
			   }
			   else
			   {
				   std::cout << '\t' << "Emergency for " << maindeque.front()->name
					   << " for class " << maindeque.front()->clas << ". Time left: "
					   << maindeque.front()->minutes << '\n';
			   }
			   //reduce the time
			   maindeque.front()->minutes--;
		   }
		   if (maindeque.size() > 0 && maindeque.front()->minutes == 0)
		   {
			   maindeque.pop_front();
		   }
		   
	   }
	   catch (const char* e)
	   {
		   std::cout << '\t' << e << endl;
	   }
   } 




   // end
   std::cout << "End of simulation\n";
}


