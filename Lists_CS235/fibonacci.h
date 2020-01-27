/***********************************************************************
 * Header:
 *    FIBONACCI
 * Summary:
 *    This will contain just the prototype for fibonacci(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Abdias Baldiviezo & Kevin Hisel
 ************************************************************************/

#ifndef FIBONACCI_H
#define FIBONACCI_H
#include "list.h"


// the interactive fibonacci program
void fibonacci();

class wholeNumber 
{
public:
	//constructor
	wholeNumber();
	//non default constructor
	wholeNumber(unsigned int);
	//copy constructor
	wholeNumber(const wholeNumber& rhs);
	//destructor
	~wholeNumber();
	//insertion operator
	friend std::ostream & operator << (std::ostream & out, wholeNumber & rhs);
	//extraction operator
	friend std::istream & operator >> (std::istream & in, wholeNumber & rhs);
	//add 2 WholeNumbers
	wholeNumber& operator += (const wholeNumber & rhs);
	//substract 2 WholeNumbers
	//WholeNumber& operator -= (const WholeNumber& rhs);
	//assignment operator
	wholeNumber& operator = (const wholeNumber& rhs);
private:

	custom::list<std::string>* digits;

};
#endif // FIBONACCI_H

