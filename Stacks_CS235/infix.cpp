/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
using namespace custom;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::ios;;

bool lexComparator(string a, string b) 
{
	int value1=0;
	int value2=0;
	if (a=="+" || a=="-")
	{
		value1 = 1;
	}
	else if (a=="*" || a=="/")
	{
		value1 = 2;
	}
	else if (a == "^" || a == "%")
	{
		value1 = 3;
	}

	if (b == "+" || b == "-")
	{
		value2 = 1;
	}
	else if (b == "*" || b == "/")
	{
		value2 = 2;
	}
	else if (b == "^" || b == "%")
	{
		value2 = 3;
	}
	return value1 <= value2;
}
/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
	string postfix;
	int iPostfix = 0;
	int iInfix = 0;
	stack<string> stack;
	string token;
	for ( iInfix; iInfix < infix.length(); iInfix++)
	{
		//get the whole token
		token = "";
		while (infix[iInfix]!= ' ' && infix[iInfix] != '+' && infix[iInfix] != '-' 
			&& infix[iInfix] != '*' && infix[iInfix] != '/' && infix[iInfix] != '%' 
			&& infix[iInfix] != '^' && infix[iInfix] != '(' && infix[iInfix] != ')')
		{
			token = token + infix[iInfix];
			if (iInfix < infix.length()-1)
			{
				iInfix++;
			}
			else
			{
				break;
			}
		}	
		// add the token to the postfix
		if (token != "")
		{
			postfix = postfix + token + " ";
		}
		
		//cases of symbols
		if (infix[iInfix] == '(')
		{
			token = infix[iInfix];
			stack.push(token);
			token = "";
		}
		else if (infix[iInfix] == ')')
		{
			while (stack.top() != "(")
			{
				postfix = postfix + stack.top() + " ";
				stack.pop();
			}
			stack.pop();
		}
		//if its a space or a symbol put it into the stack
		else if (!isalnum(infix[iInfix]) && infix[iInfix] != ' ')
		{
			token = infix[iInfix];
			while (!stack.empty() && lexComparator( token, stack.top()))
			{
				postfix = postfix + stack.top() + " ";
				stack.pop();
			}
			//token = infix[iInfix];
			stack.push(token);
			

		}
	}
	//take all the symbols from the stack and place them into the array
	while (!stack.empty())
	{
		postfix = postfix + stack.top() + " ";
		stack.pop();
	}
	//strip off the extra space at the end if there is one
	if (postfix[postfix.length()-1]==' ')
	{
		postfix = postfix.substr(0,postfix.length()-1);
	}
	return postfix;
	
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix:  " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
	string newVar = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int newVarCounter = 0;
	stack<string> stack;
	string assembly;
	string rhs;
	string lhs;
	string token;
	int loadcounter = 0;;
	for (int i = 0; i < postfix.length(); i++)
	{
		//get the whole token
		token = "";
		while (postfix[i] != ' ' && postfix[i] != '+' && postfix[i] != '-'
			&& postfix[i] != '*' && postfix[i] != '/' && postfix[i] != '%'
			&& postfix[i] != '^')
		{
			token = token + postfix[i];
			if (i < postfix.length() - 1)
			{
				i++;
			}
			else
			{
				break;
			}
		}
		// add the token to the postfix
		if (token != "")
		{
			stack.push(token);
			loadcounter++;
		}

		//if (isalnum(postfix[i]))
		//{
		//	//define the variable

		//	stack.push(postfix[i]);
		//}
		if (postfix[i] == '+' || postfix[i] == '-'
			|| postfix[i] == '*' || postfix[i] == '/'
			|| postfix[i] == '%' || postfix[i] == '^')
		{
			//to erase the simbol and just use it directly from token
			//stack.pop();
			rhs = stack.top();
			stack.pop();
			lhs = stack.top();
			stack.pop();
			string variable = newVar.substr(newVarCounter,1);
			if (lhs.length()==1 && lhs[0] >= 'A' && lhs[0] <= 'Z')
			{
				assembly = assembly + "\t" + "LOD " + lhs + "\n";
			}
			else
			{
				if (loadcounter>=3)
				{
					assembly = assembly + "\t" + "LOD " + lhs + "\n";
				}
				else
				{
					assembly = assembly + "\t" + "SET " + lhs + "\n";
				}
				
			}
			string operation;
			if (postfix[i] == '+')
			{
				operation = "ADD ";
			}
			else if (postfix[i] == '-')
			{
				operation = "SUB ";
			}
			else if (postfix[i] == '*')
			{
				operation = "MUL ";
			}
			else if (postfix[i] == '/')
			{
				operation = "DIV ";
			}
			else if (postfix[i] == '%')
			{
				operation = "MOD ";
			}
			else if (postfix[i] == '^')
			{
				operation = "EXP ";
			}
			assembly = assembly + "\t" + operation + rhs + "\n";
			assembly = assembly + "\t" + "SAV " + variable + "\n";

			stack.push(variable);

			newVarCounter++;
		}
	}

	return assembly;

}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
