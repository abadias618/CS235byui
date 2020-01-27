/***********************************************************************
 * Header:
 *    STOCK
 * Summary:
 *    This will contain just the prototype for stocksBuySell(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef STOCK_H
#define STOCK_H

#include "dollars.h"   // for Dollars defined in StockTransaction
#include "queue.h"     // for QUEUE
#include <iostream>    // for ISTREAM and OSTREAM
#include <string>      // for STRING
#include <ostream>
// the interactive stock buy/sell function
void stocksBuySell();
class transaction;
class portfolio;
void userinput(std::string input, std::string& action, int& shares, Dollars& price);
#endif // STOCK_H

