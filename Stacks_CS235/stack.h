/***********************************************************************
 * Header:
 *    Array
 * Summary:
 *    contains a stack template class, using an array as
 *	  the base inner container.
 *
 *    This will contain the class definition of:
 *       stack             : similar to std::stack
 * Author
 *    Abdias Baldiviezo
 *	  Kevin Hisel
 ************************************************************************/

#ifndef STACK_H
#define STACK_H
namespace custom 
{
/************************************************
 * STACK
 * A class that holds stuff with the filo philosophy
 * ,grows when inserting elements
 ***********************************************/
	template <class T>
	class stack
	{
	public:
		//default constructor
		stack();
		//non-default constructor
		stack(int numCapacity);
		//copy-constructor
		stack(const stack & rhs);
		// destructor
		~stack();
		//assignment operator
		stack & operator = (const stack & rhs);
		//generic
		int size() const;
		int capacity() const;
		void clear();
		bool empty() const;
		//access
		void push(const T& t);
		void pop();
		const T& top() const;
		T& top();
		


	private:

		T* array;
		int numElements;
		int numCapacity;
		void resize(int numCapacity);


	}; //class stack
/*******************************************
 * STACK :: resize
 * Param: int capacity to expand the array memory alloc
 *******************************************/
	//resize
	template <class T>
	void stack <T> ::resize(int numCapacity) {
		if (numCapacity < 1)
		{
			this->numCapacity = 1;
			// attempt to allocate
			try
			{
				T* temp = new T[this->numCapacity];
				for (int i = 0; i < numElements; i++)
				{
					temp[i] = array[i];
				}
				delete[]array;
				array = temp;
			}
			catch (std::bad_alloc)
			{
				throw ("ERROR: Unable to allocate a new buffer for vector");
			}
		}
		else
		{
			this->numCapacity = numCapacity * 2;
			// attempt to allocate
			try
			{
				T* temp = new T[this->numCapacity];
				for (int i = 0; i < numElements; i++)
				{
					temp[i] = array[i];
				}
				delete [] array;
				array = temp;
			}
			catch (std::bad_alloc)
			{
				throw ("ERROR: Unable to allocate a new buffer for vector");
			}

		}
		
	}
	//resize
/*******************************************
 * STACK :: default constructor
 * sets data fields to 0
 *******************************************/
	//default constructor
	template <class T>
	stack <T> ::stack() {
		array = NULL;
		numElements = 0;
		numCapacity = 0;
	} //default constructor

/*******************************************
 * STACK :: non-default constructor
 * Param: int initial capacity for the array
 *******************************************/
	//non-default constructor
	template <class T>
	stack <T> ::stack(int numCapacity) {
		numElements = 0;
		if (numCapacity > 0){
			
			// attempt to allocate
			try
			{
				array = new T[numCapacity];
				
			}
			catch (std::bad_alloc)
			{
				throw "ERROR: Unable to allocate a new buffer for Stack";
			}
			this->numCapacity= numCapacity;
			
		}
		else
		{
			array = NULL;
			this->numCapacity = 0;
		}
	
	} //non-default constructor
/*******************************************
 * STACK :: copy constructor
 * Param: a stack to copy
 *******************************************/
	//copy constructor
	template <class T>
	stack <T> ::stack(const stack <T > & rhs ) {
		if (rhs.numElements>0) {

			// attempt to allocate
			try
			{
				array = new T[rhs.numElements];
			}
			catch (std::bad_alloc)
			{
				throw "ERROR: Unable to allocate a new buffer for Stack";
			}

			// copy over the capacity
			numCapacity = rhs.numCapacity;
			numElements = rhs.numElements;

			// copy the items over one at a time using the assignment operator
			for (int i = 0; i < numElements; i++) {
				array[i] = rhs.array[i];
			
			}
				
		}
		else
		{
			array = NULL;
			numElements = 0;
			numCapacity = 0;
		}
		
	}  //copy constructor 
/*******************************************
 * STACK :: destructor
 * destroys the main container
 *******************************************/
	//destructor
	template <class T>
	stack <T> ::~stack() {
		delete [] array;
	} //destructor
/*******************************************
 * STACK :: assignment operator 
 * Param: a stack to copy
 *******************************************/
	//assignment operator
	template <class T>
	stack <T> & stack<T>::operator = (const stack <T> & rhs){

		if (rhs.numCapacity < 1)
		{
			array = NULL;
			numElements = 0;
			numCapacity = 0;
			
		}
		else if (rhs.numElements <= numCapacity)
		{
			numElements = rhs.numElements;
			numCapacity = rhs.numCapacity;
			// attempt to allocate
			try
			{
				array = new T[numCapacity];
			}
			catch (std::bad_alloc)
			{
				throw ("ERROR: Unable to allocate a new buffer for Stack");
			}
			// copy the items over one at a time using the assignment operator
			for (int i = 0; i < numElements; i++)
			{
				array[i] = rhs.array[i];
			}
			return *this;

		}
		else if (rhs.numElements > numCapacity)
		{
			resize(rhs.numElements);
			numElements = rhs.numElements;
			numCapacity = rhs.numCapacity;
			// attempt to allocate
			try
			{
				array = new T[numCapacity];
			}
			catch (std::bad_alloc)
			{
				throw ("ERROR: Unable to allocate a new buffer for Stack");
			}
			// copy the items over one at a time using the assignment operator
			for (int i = 0; i < numElements; i++)
			{
				array[i] = rhs.array[i];
			}
			
		}
		return *this;
	} // assignment operator
/*******************************************
 * STACK :: empty
 * Return: true if empty, false if not
 *******************************************/
	//empty
	template <class T>
	bool stack <T> ::empty() const {
		if (size() == 0) {
			return true;
		}
		else return false;
	} //empty
/*******************************************
 * STACK :: size
 * Return: the number of elements in the stack
 *******************************************/
	//size
	template <class T>
	int stack <T> ::size() const {
		return numElements;
	} //size
/*******************************************
 * STACK :: capacity
 * Return: the capacity of alloc memory for the array
 *******************************************/
	//capacity
	template <class T>
	int stack <T> ::capacity() const {
		return numCapacity;
	} //capacity
/*******************************************
 * STACK :: clear
 * sets the numElements to 0
 *******************************************/
	//clear
	template <class T>
	void stack <T> ::clear()  {
		numElements = 0;
	} //clear
/*******************************************
 * STACK :: push
 * Param: takes a T element to add to the stack
 *******************************************/
	//push
	template <class T>
	void stack <T> ::push(const T& t) {
		if (size()==capacity()) {
			resize(capacity());
		}
		array[numElements] = t;
		numElements++;
	} //push
/*******************************************
 * STACK :: pop
 * takes a element from the top of the stack
 *******************************************/
	//pop
	template <class T>
	void stack <T> ::pop() {
		if (!empty())
		{
			--numElements;
		}
		
	} //pop
/*******************************************
 * STACK :: top (changeable)
 * Return: the top element that can be changed
 *******************************************/
	//top non-changing
	template <class T>
	const T & stack <T> ::top() const {

		if (!empty()) {
			return array[size()-1];
		}
		else {
			throw "ERROR: Unable to reference the element from an empty Stack";
		}
	} //top non-changing
/*******************************************
 * STACK :: top (unchangeable)
 * Return: the top element that cannot be changed
 *******************************************/
	//top non-changing
	template <class T>
	T&stack<T>::top(){

		if (!empty()) {
			return array[size()-1];
		}
		else {
			throw "ERROR: Unable to reference the element from an empty Stack";
		}
	} //top changing
	
}; //namespace custom

#endif // STACK_H
