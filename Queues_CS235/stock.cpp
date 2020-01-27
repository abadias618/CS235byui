/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"	   // for QUEUE
#include "dollars.h"   // for DOLLARS
using namespace std;
/************************************************
 * CLASS TRANSACTION
 * creates a tranasaction with all its details
 ***********************************************/
class transaction 
{
public:
	transaction() 
	{
		price = 0;
		action = "";
		proceeds = 0;
		sharesNum = 0;
	}
	transaction(Dollars price, int sharesNum, string action)
	{
		if (action == "buy")
		{
			buy(price, sharesNum, action);
		}
		else if (action == "sell")
		{
			sell(price, sharesNum, action);
		}
		else
		{
			throw "Invalid transaction";
		}
		
	}
	//data fields
	Dollars price;
	int sharesNum;
	string action;
	Dollars proceeds;
	//
	/************************************************
	 * TRANSACTION :: BUY
	 * set the transaction to buy
	 ***********************************************/
	void buy(Dollars price, int shares, string action)
	{
		this->action = "buy";
		this->sharesNum = shares;
		this->price = price;
		this->proceeds = 0;
		
	}
	/************************************************
	 * TRANSACTION :: SELL
	 * set the transaction to sell
	 ***********************************************/
	void sell(Dollars price, int shares, string action)
	{
		this->action = "sell";
		this->sharesNum = shares;
		this->price = price;
		this->proceeds = 0;
	}
	
};
/************************************************
* CLASS PORTFOLIO
* 2 QUEUES WITH ALL THE TRANSACTIONS
***********************************************/
class portfolio 
{
public:
	portfolio()
	{
	}
	//data fields
	custom::queue<transaction> heldQ;
	custom::queue<transaction> sellQ;
	Dollars proceeds;
	//
	/************************************************
	* PORTFOLIO :: ADD
	* adds the transaction to its respective queue
	***********************************************/
	void add(transaction t)
	{
		if (t.action=="buy")
		{
			heldQ.push(t);
		}
		else if (t.action == "sell")
		{
			//sell logic
			int num = t.sharesNum;
			Dollars localProceeds=0;
			custom::queue<transaction> copyheldQ = heldQ;
			while (num>0)
			{	
				//find the last sale
				//calc proceeds
				if (copyheldQ.front().sharesNum - num > 0)
				{
					Dollars proceedsPre = (t.price - copyheldQ.front().price) * num;
					//proceeds calculated from the stocks we have
					localProceeds = localProceeds +  ((t.price - copyheldQ.front().price) * num);
					//stocks reduced from the transaction
					int diff = (copyheldQ.front().sharesNum + num)- copyheldQ.front().sharesNum;
					copyheldQ.front().sharesNum = copyheldQ.front().sharesNum - num;
					//substract the number of stocks reduced from num
					
					transaction x = transaction(t.price, num, "sell");
					x.proceeds = proceedsPre;
					sellQ.push(x);
					num = num - diff;
						
				}
				else if (copyheldQ.front().sharesNum - num <= 0)
				{
					//assuming that num is higher than what we have in the
					//stack we calculate the difference and sub that from the stock
					//(should be the difference should be the same as the numShares from the stock)
					int difference = (num + copyheldQ.front().sharesNum)-num;
					//proceeds calculated from the stocks we have
					Dollars proceedsPre = (t.price - copyheldQ.front().price) * difference;
					localProceeds = localProceeds + ((t.price - copyheldQ.front().price) * difference);
					//stocks reduced from the transaction
					copyheldQ.front().sharesNum = copyheldQ.front().sharesNum - difference;
					//substract the number of stocks reduced from num
					num = num - difference;
					//delete the stock if empty
					if (copyheldQ.front().sharesNum==0)
					{
						transaction x = transaction(t.price, difference, "sell");
						x.proceeds = proceedsPre;
						sellQ.push(x);
						copyheldQ.pop();
					}
					
				}
				
			}
			//the held queue is now the copy queue
			heldQ = copyheldQ;
			//set the results to the sale
			t.proceeds = localProceeds;
			//set the proceeds to the total proceeds data field
			this->proceeds = this->proceeds + localProceeds;
			//sellQ.push(t);

		}
	}
	/************************************************
	 * PORTFOLIO :: DISPLAY
	 * DISPLAYS THE DATA IN THE PORTFOLIO
	 ***********************************************/
	void display()
	{
		if (heldQ.size()>0)
		{
			cout << "Currently held:" << "\n";
		}
		custom::queue<transaction> copyheldQ=heldQ;
		while (!copyheldQ.empty())
		{
			cout << "\t" << "Bought " << copyheldQ.front().sharesNum << " shares at " 
				<< copyheldQ.front().price << "\n";
			copyheldQ.pop();
		}
		if (sellQ.size()>0)
		{
			cout << "Sell History:" << "\n";
			custom::queue<transaction> copysellQ = sellQ;
			while (!copysellQ.empty())
			{
				cout << "\t" << "Sold " << copysellQ.front().sharesNum << " shares at " 
					<< copysellQ.front().price << " for a profit of " << copysellQ.front().proceeds << "\n";
				copysellQ.pop();
			}
		}
		cout << "Proceeds: " << this->proceeds << "\n";

	}
};
/************************************************
* GET INPUT
* The interactive function allowing the user to
* buy and sell stocks
***********************************************/
void userinput(string input, string& action, int& shares, Dollars& price)
{
	int tokencounter = 0;
	string token = "";
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] != ' ')
		{
			token = token + input[i];
		}
		else
		{
			tokencounter++;
		}

		if (tokencounter == 1 && i == input.length() - 1
			|| i == input.length() - 1 && tokencounter == 0)
		{
			action = token;
		}
		else if (tokencounter == 1)
		{
			action = token;
			token = "";
			tokencounter++;
		}
		else if (tokencounter == 3)
		{
			shares = stoi(token);
			token = "";
			tokencounter++;
		}
		else if (tokencounter == 4 && i == input.length() - 1)
		{
			float tokenf;
			if (token[0]=='$')
			{
				token = token.substr(1, token.length() - 1);
			}
			tokenf = stof(token);
			tokenf = tokenf+0.00001;
			price = tokenf;
			token = "";
		}
	}
}


/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";


   // your code here...
  
   string action="";
   int shares = 0;
   string input;
   Dollars price = 0;;
   bool quit = false;
   //portfolio
   portfolio p;
   cin.ignore();
   while (!quit)
   {
	   
	   cout << "> ";
	   getline (cin, input);
	      
	   userinput(input,action,shares,price);

	   if (action == "buy")
	   {
		   p.add(transaction(price, shares, action));
	   }
	   else if (action == "sell")
	   {
		   p.add(transaction(price, shares, action));

	   }
	   else if (action == "display")
	   {
		   p.display();
	   }
	   else if (action == "quit")
	   {
		   quit = true;
	   }
   }
   
}


