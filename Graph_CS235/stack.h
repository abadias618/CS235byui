/***********************************************************************
 * Header:
 *    Stack
 * Summary:
 *    This class contains the notion of a stack: a bucket to hold
 *    data for the user.
 *
 *    This will contain the class definition of:
 *       stack             : similar to std::stack
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <cassert>  // because I am paranoid
#include <iostream>
#include <cstddef>
// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * STACK
 * A class that holds stuff
 ***********************************************/
template <class T>
class stack
{
private:
   void resize(int cap);
public:
   // constructors and destructors
   stack() throw (const char *);
   stack(int num)                  throw (const char *);
   stack(const stack & rhs)        throw (const char *);
   ~stack()                         {  delete [] data;   }
   stack & operator = (const stack & rhs) throw (const char *);
   
   // the push method to add data to the stack
   void push(const T t);
	
	void pop();
	
	T top() const throw (const char *);
   T & top() throw (const char *); 
// standard container interfaces
   int  size()     const { return numElements;                 }
   int  capacity() const { return numCapacity;                 }

   bool empty() const { return numElements == 0;}
   void clear();
  
   // a debug utility to display the stack
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
private:
   T * data;              // dynamically allocated array of T
   int numElements;               
   int numCapacity;
};

/*******************************************
 * STACK :: Assignment
 *******************************************/
template <class T>
stack <T> & stack <T> :: operator = (const stack <T> & rhs)
          throw (const char *)
{
   for (int i = 0; i < rhs.numElements; i++)
      {
		   if (i == numCapacity)
			   resize(numCapacity);
			data[i] = rhs.data[i];
		}
   numElements = rhs.numElements;
   return *this;
}

/*******************************************
 *
 STACK :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
stack <T> :: stack(const stack <T> & rhs) throw (const char *)
{
   assert(rhs.numElements >= 0);

   // do nothing if there is nothing to do
   if (rhs.numElements == 0)
   {
      numElements = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.numElements];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity
   numCapacity = rhs.numCapacity;
   numElements = rhs.numElements;
   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      data[i] = rhs.data[i];
}

   
/******************************************* 
 * 
 STACK :: DEFAULT CONSTRUCTOR
 *******************************************/
   template <class T>
   stack <T> :: stack() throw (const char *)
   {
      numElements = 0;
      numCapacity = 0;
      this->data = NULL;
      // attempt to allocate                                                          
   try
   {
      data = new T[numElements];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   }
/**********************************************
 * STACK : NON-DEFAULT CONSTRUCTOR
 * Preallocate the stack to "capacity"
 **********************************************/
template <class T>
stack <T> :: stack(int num) throw (const char *)
{
   assert(num >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an array, this is kinda pointless
   if (num == 0)
   {
      this->numElements = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[num];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->numElements = num;
   this->numCapacity = num;
}



/********************************************                                     
 * STACK : clear                  
 * clears the contents of the stack                          
 *******************************************/
   template <class T>
   void stack <T> :: clear()
   {
      numElements = 0;
   }

/********************************************                                     
 * STACK : push
 * Adds data to the end of the stack                          
 *******************************************/
template <class T>
void stack <T> :: push(const T t)
{
   if(numCapacity == 0 || numElements + 1 > numCapacity)
   {
      resize(numCapacity);
   }
   
   data[this->numElements++] = t;
}

template <class T>
void stack <T> :: pop()
{
	numElements--;
}

template <class T>
T stack <T> :: top() const throw (const char *)
{
	if (numElements != 0)
   {
      return data[numElements - 1];
   }
   else
   {
      throw "ERROR: Unable to reference the element from an empty stack";
   }
}

template <class T>
T & stack <T> :: top() throw (const char *)
{
	if (numElements != 0)
   {
      return data[numElements - 1];
   }
   else
   {
      throw "ERROR: Unable to reference the element from an empty stack";
   }
}

/********************************************                                      
 * STACK : resize
 * Resizes the stack to twice the capacity
 *******************************************/
template <class T>
void stack <T> :: resize(int cap)
{
   if (cap == 0)
      cap = 2;
   numCapacity = cap * 2;
   T * temp = new T[numCapacity];
   temp = data;
   data = NULL;
   data = new T[numCapacity];
   data = temp;
}
/********************************************
 * STACK : DISPLAY
 * A debug utility to display the contents of the stack
 *******************************************/
template <class T>
void stack <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "stack<T>::display()\n";
   std::cerr << "\tnum = " << numElements << "\n";
   for (int i = 0; i < numElements; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}


}; // namespace custom

#endif // STACK_H

