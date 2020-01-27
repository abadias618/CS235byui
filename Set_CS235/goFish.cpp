/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    Abdias Baldiviezo
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <fstream>
#include "set.h"
#include "card.h"
#include "goFish.h"
#include <string>
using namespace std;

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
	//read the hand

	//Open File
	// C:/Users/abadi/source/repos/Set_CS235/hand.txt
	ifstream fin("/home/cs235/week05/hand.txt");
	if (fin.fail())
	{
		throw "failed to open";
	}
	custom::set<Card> hand;
	char word[128];

	while (fin >> word)
	{
		hand.insert(word);
	}
	fin.close();
	//
	int round = 1;
	int match = 0;
	
	cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand\n";
	while (round<=5)
	{
		Card input;
		cout << "round " << round << ": ";
		cin >> input;

		if (hand.find(input) != hand.end())
		{
			cout << "\tYou got a match!" << endl;
			hand.erase(input);
			match++;
		}
		else
		{
			cout << "\tGo Fish!" << endl;
		}
		round++;
	}
	//score
	cout << "You have " << match << " matches!" << endl;
	cout << "The remaining cards: ";
	string coma = ", ";
	int counter = 1;
	for (custom::set<Card>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		if (it!=hand.begin())
		{
			cout << coma << *it ;
		}
		else
		{
			cout << *it;
		}
		
		if (counter==hand.size())
		{
			cout << "\n";
		}
		counter++;
	}
   return ;
}


