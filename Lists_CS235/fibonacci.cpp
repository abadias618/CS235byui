/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    Abdias Baldiviezo & Kevin Hisel
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
#include <string>
using namespace std;


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{

   //show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;
   
   // your code to display the first <number> Fibonacci numbers
   wholeNumber firstNum=wholeNumber(0);
   wholeNumber secondNum = wholeNumber(1);
   wholeNumber thirdNum;
   std::cout << secondNum << endl;
   while (number!=1)
   {
	   firstNum += secondNum;
	   thirdNum = firstNum;
	   firstNum = secondNum;
	   secondNum = thirdNum;
	   std::cout << thirdNum << endl;
	   number--;
   }
   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   // your code to display the <number>th Fibonacci number
   wholeNumber firstNum2 = wholeNumber(0);
   wholeNumber secondNum2 = wholeNumber(1);
   wholeNumber thirdNum2;
   if (number==1)
   {
	   cout << "1";

   }
   while (number != 1)
   {
	   firstNum2 += secondNum2;
	   thirdNum2 = firstNum2;
	   firstNum2 = secondNum2;
	   secondNum2 = thirdNum2;
	   number--;
   }
   std::cout << thirdNum2 << endl;

	/*
	//DEBUG
	WholeNumber one = WholeNumber(7778742049);
	WholeNumber two = WholeNumber(12586269025);
	one += two;
	WholeNumber three;
	three = one;
	cout << three << endl;*/

}
/************************************************
 * WHOLENUMBER :: default constructor
 * initiates the list to null
 ***********************************************/
wholeNumber::wholeNumber()
{
	digits = new custom::list<std::string>;
};
/************************************************
 * WHOLENUMBER :: non-default constructor
 * inititates a list with the number provided
 ***********************************************/
wholeNumber::wholeNumber(unsigned int num)
{
	digits = new custom::list<std::string>;
	std::string digit = to_string(num);
	std::string nodeNumber;
	int numSize = digit.length();
	int j = 0;
	for (int i = numSize; i != 0;)
	{
		i--;
		nodeNumber = digit[i] + nodeNumber;
		j++;
		if (j % 3 == 0)
		{
			digits->push_front(nodeNumber);
			nodeNumber = "";
			j = 0;
		}
		
	}
	if (nodeNumber!="")
	{
		digits->push_front(nodeNumber);
	}
	
};
/************************************************
 * WHOLENUMBER :: copy constructor
 * copies the list from rhs to our digit data member
 ***********************************************/
wholeNumber::wholeNumber(const wholeNumber& rhs)
{
	digits = rhs.digits;
};
/************************************************
 * WHOLENUMBER :: destructor
 * clears the inner list
 ***********************************************/
wholeNumber::~wholeNumber()
{
	digits->clear();
};
/************************************************
 * WHOLENUMBER :: assignment operator
 * assigns a wholenumber to another wholenumber
 ***********************************************/
wholeNumber& wholeNumber::operator = (const wholeNumber& rhs)
{
	if (!digits->empty())
	{
		digits->clear();
	}
	//custom::list<std::string> *templist = new custom::list<std::string> (rhs.digits);
	digits->operator=(*rhs.digits);

	return *this;

};
/************************************************
 * WHOLENUMBER :: insertion operator
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
ostream& operator << (ostream& out, wholeNumber& rhs)
{
	custom::list<std::string> ::iterator it;
	string output_string;
	for (it = rhs.digits->begin(); it != rhs.digits->end(); ++it)
	{
		if (rhs.digits->size()<2)
		{
			output_string += *it;
			
		}
		else if (*it == rhs.digits->back()/* && ++it==NULL*/)
		{
			output_string += *it;
		}
		else if (*it!=rhs.digits->back())
		{
			output_string = output_string + *it + ",";
		}
		
	}
	cout <<"\t"+output_string;
	return out;
};
/************************************************
 * WHOLENUMBER :: extraction operator
 * Allows to insert a number from the console
 ***********************************************/
istream& operator >> (istream& in, wholeNumber& rhs)
{
	std::string digit;
	cout << "insert ANY integer positive number without comas";
	cin >>digit;
	rhs.digits = new custom::list<std::string>;
	std::string nodeNumber;
	int numSize = digit.length();
	int j = 0;
	for (int i = numSize; i != 0;)
	{
		i--;
		nodeNumber = digit[i] + nodeNumber;
		j++;
		if (j % 3 == 0)
		{
			rhs.digits->push_front(nodeNumber);
			nodeNumber = "";
			j = 0;
		}

	}
	if (nodeNumber != "")
	{
		rhs.digits->push_front(nodeNumber);
	}
	return in;
};
/************************************************
 * WHOLENUMBER :: addition operator
 * adds 2 wholenumbers
 ***********************************************/
wholeNumber& wholeNumber::operator += (const wholeNumber& rhs)
{
	int nodeNumber=0;
	int nodeNumberRHS=0;
	int numresult;
	int carry = 0;
	custom::list<std::string>* templist = new custom::list<std::string>;
	custom::list<std::string> ::reverse_iterator rit;
	custom::list<std::string> ::reverse_iterator it;
	rit = digits->rbegin();
	it = rhs.digits->rbegin();
	//counter to keep track of last iteration
	int counter = 1;
	while ( it != 0 || rit != 0)
	{
		if (it!=0)
		{
			nodeNumber = std::stoi(*it);
		}
		if (rit!=0)
		{
			nodeNumberRHS = std::stoi(*rit);
		}
		
		
		numresult = nodeNumber + nodeNumberRHS + carry;
		carry = 0;
		std::string lastinsert;
		std::string insert = to_string(numresult);
		std::string carrychar="";
		
		if (insert.length() > 3)
		{
			carrychar = insert.substr(0, insert.length() - 3);
			carry = std::stoi(carrychar);
			lastinsert = insert.substr(insert.length() - 3, 3);
		}
		else if (insert.length()==2)
		{
			lastinsert = "0" + insert;
		}
		else if (insert.length()==1)
		{
			lastinsert = "00" + insert;	
		}
		else
		{	
			lastinsert = insert;
		}
		//determines if the carry will be inserted (only if it is the last iteration)
		//it wouldnt work well if we didn't know the next number is bigger
		if (it!=0 && *it == rhs.digits->front() && counter==rhs.digits->size())
		{
			
			templist->push_front(lastinsert);
			if (carrychar != "")
			{
				templist->push_front(carrychar);
			}
		}
		else
		{
			templist->push_front(lastinsert);
		}
		//
		if ( it!=0 && *it==rhs.digits->front() && counter == rhs.digits->size())
		{
			it = 0;
			nodeNumber = 0;
		}
		else if (it != 0)
		{
			
			++it;
		}
		if (rit!=0 && *rit == digits->front() && counter == digits->size())
		{
			rit = 0;
			nodeNumberRHS = 0;
		}
		else if (rit != 0)
		{
			++rit;
		}
		counter++;

	}
	//to eliminate the zeros in front
	int temp = std::stoi(templist->front());
	std::string ins = to_string(temp);
	templist->front() = ins;
	digits = templist;
	return *this;
};
/************************************************
 * WHOLENUMBER :: substraction operator
 * adds 2 wholenumbers
 ***********************************************/
//wholeNumber& wholeNumber::operator -= (const wholeNumber& rhs)
//{
//	int nodeNumber = 0;
//	int nodeNumberRHS = 0;
//	int numresult;
//	int carry = 0;
//	custom::list<std::string>* templist = new custom::list<std::string>;
//	custom::list<std::string> ::reverse_iterator rit;
//	custom::list<std::string> ::reverse_iterator it;
//	rit = digits->rbegin();
//	it = rhs.digits->rbegin();
//	//counter to keep track of last iteration
//	int counter = 1;
//	while (it != 0 || rit != 0)
//	{
//		if (it != 0)
//		{
//			nodeNumber = std::stoi(*it);
//		}
//		if (rit != 0)
//		{
//			nodeNumberRHS = std::stoi(*rit);
//		}
//
//
//		numresult = nodeNumber + nodeNumberRHS + carry;
//		carry = 0;
//		std::string lastinsert;
//		std::string insert = to_string(numresult);
//		std::string carrychar = "";
//
//		if (insert.length() > 3)
//		{
//			carrychar = insert.substr(0, insert.length() - 3);
//			carry = std::stoi(carrychar);
//			lastinsert = insert.substr(insert.length() - 3, 3);
//		}
//		else if (insert.length() == 2)
//		{
//			lastinsert = "0" + insert;
//		}
//		else if (insert.length() == 1)
//		{
//			lastinsert = "00" + insert;
//		}
//		else
//		{
//			lastinsert = insert;
//		}
//		//determines if the carry will be inserted (only if it is the last iteration)
//		//it wouldnt work well if we didn't know the next number is bigger
//		if (it != 0 && *it == rhs.digits->front() && counter == rhs.digits->size())
//		{
//
//			templist->push_front(lastinsert);
//			if (carrychar != "")
//			{
//				templist->push_front(carrychar);
//			}
//		}
//		else
//		{
//			templist->push_front(lastinsert);
//		}
//		//
//		if (it != 0 && *it == rhs.digits->front() && counter == rhs.digits->size())
//		{
//			it = 0;
//			nodeNumber = 0;
//		}
//		else if (it != 0)
//		{
//
//			++it;
//		}
//		if (rit != 0 && *rit == digits->front() && counter == digits->size())
//		{
//			rit = 0;
//			nodeNumberRHS = 0;
//		}
//		else if (rit != 0)
//		{
//			++rit;
//		}
//		counter++;
//
//	}
//	//to eliminate the zeros in front
//	int temp = std::stoi(templist->front());
//	std::string ins = to_string(temp);
//	templist->front() = ins;
//	digits = templist;
//	return *this;
//};



