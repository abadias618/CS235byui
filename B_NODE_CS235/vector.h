/***********************************************************************
 * Header:
 *    Array
 * Summary:
 *    contains a vector template class with a nested iterator, using an array as
 *	  the base structure
 *
 *    This will contain the class definition of:
 *       vector             : similar to std::vector
 *       vector :: iterator : an iterator through the vector
 * Author
 *    Abdias Baldiviezo
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H
namespace custom
{
/************************************************
 * VECTOR
 * A class that holds stuff and grows when 
 * inserting elements
 ***********************************************/
template <class T>
class vector {
public:
	//default constructor
	vector();
	//non-default constructor with specified size
	vector(int numCapacity);
	//copy constructor
	vector(const vector <T>& rhs);
	//deconstructor ****introduce an IF if  default constructor is called
	~vector();
	//assignment operator
	vector& operator = (const vector& rhs);
	//standard container interfaces
	int  size() const; 
	int  capacity() const; 
	bool empty() const; 
	void clear();
	//operator
	T& operator [] (int index);
	const T&  operator [] (int index) const;
	void push_back(const T& t);

	// the various iterator interfaces
	class iterator;
	iterator begin() { return iterator(array); }
	iterator end();

	// the various const_iterator interfaces
	class const_iterator;
	const const_iterator cbegin() const { return const_iterator(array); }
	const const_iterator cend() const;
	
private:
	T * array;
	int numElements;
	int numCapacity;
	void resize(int numCapacity);

}; // class vector
/**************************************************
 * VECTOR ITERATOR
 * An iterator through the vector
 *************************************************/
template <class T>
class vector <T> ::iterator
{
public:
	// constructors, destructors, and assignment operator
	iterator() : p(NULL) {              }
	iterator(T * p) : p(p) {              }
	iterator(const iterator & rhs) { *this = rhs; }
	iterator & operator = (const iterator & rhs)
	{
	   this->p = rhs.p;
	   return *this;
	}

	// equals, not equals operator
	bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
	bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

	// dereference operator
		  T & operator * () { return *p; }
	const T & operator * () const { return *p; }

	// prefix increment
	iterator & operator ++ ()
	{
	   p++;
	   return *this;
	}

	// postfix increment
	iterator operator ++ (int postfix)
	{
	   iterator tmp(*this);
	   p++;
	   return tmp;
	}

	// prefix increment
	iterator& operator -- ()
	{
		p--;
		return *this;
	}
	// postfix decrement
	iterator operator -- (int prefix)
	{
		iterator tmp(*this);
		p--;
		return tmp;
	}

 private:
	T * p;
};
/**************************************************
 * VECTOR CONST_ITERATOR
 * An iterator through the vector that is constant
 *************************************************/
template <class T>
class vector <T> ::const_iterator
{
public:
	// constructors, destructors, and assignment operator
	const_iterator() : p(NULL) {              }
	const_iterator(T* p) : p(p) {              }
	const_iterator(const const_iterator& rhs) { *this = rhs; }
	const_iterator& operator = (const const_iterator& rhs)
	{
		this->p = rhs.p;
		return *this;
	}

	// equals, not equals operator
	bool operator != (const const_iterator& rhs) const { return rhs.p != this->p; }
	bool operator == (const const_iterator& rhs) const { return rhs.p == this->p; }

	// dereference operator
	T& operator * () { return *p; }
	const T& operator * () const { return *p; }

	// prefix increment
	const_iterator& operator ++ ()
	{
		p++;
		return *this;
	}

	// postfix increment
	const_iterator operator ++ (int postfix)
	{
		iterator tmp(*this);
		p++;
		return tmp;
	}

	// prefix increment
	const_iterator& operator -- ()
	{
		p--;
		return *this;
	}
	// postfix decrement
	const_iterator operator -- (int prefix)
	{
		iterator tmp(*this);
		p--;
		return tmp;
	}

private:
	T* p;
};
/********************************************
 * VECTOR :: ITERATOR :: end
 ********************************************/
template <class T>
typename vector<T> ::iterator vector <T> ::end()
{
	return iterator(array + numElements);
}
/********************************************
 * VECTOR :: CONST_ITERATOR :: cend
 ********************************************/
template <class T>
const typename vector<T> ::const_iterator vector <T> ::cend() const
{
	return const_iterator(array + numElements);
}


/*******************************************
 * VECTOR :: default constructor
 *******************************************/
template <class T>
vector<T>::vector() 
{
	array = NULL;
	numElements = 0;
	numCapacity = 0;
}
/*******************************************
 * VECTOR :: non-default constructor
 *******************************************/
template <class T>
vector<T>::vector(int numCapacity) 
{
	if (numCapacity<1)
	{
		array = NULL;
		numElements = 0;
		this->numCapacity = 0;
	}
	else
	{
		numElements = numCapacity;
		this->numCapacity = numCapacity;
		// attempt to allocate
		try
		{
			array = new T[numCapacity];
		}
		catch (std::bad_alloc)
		{
			throw ("ERROR: Unable to allocate a new buffer for vector");
		}
		
		
	}
		
}
/*******************************************
 * VECTOR :: copy constructor
 *******************************************/
template <class T>
vector<T>::vector(const vector <T>& rhs) 
{
	if (rhs.numCapacity < 1)
	{
		array = NULL;
		numElements = 0;
		numCapacity = 0;
		
	}
	else
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
			throw ("ERROR: Unable to allocate a new buffer for vector");
		}
		// copy the items over one at a time using the assignment operator
		for (int i = 0; i < numCapacity; i++)
		{
			array[i] = rhs.array[i];
		}
		
	}
}
/*******************************************
 * VECTOR :: destructor
 *******************************************/
template <class T>
vector<T>::~vector()
{
	if (numCapacity!=0)
	{
		delete[]array;
	}
}
/*******************************************
 * VECTOR :: assignment operator
 *******************************************/
template <class T>
vector<T> & vector<T>::operator=(const vector<T> & rhs)
{
	if (rhs.numCapacity < 1)
	{
		array = NULL;
		numElements = 0;
		numCapacity = 0;
		return *this;
	}
	else if (rhs.numElements<numCapacity)
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
			throw ("ERROR: Unable to allocate a new buffer for vector");
		}
		// copy the items over one at a time using the assignment operator
		for (int i = 0; i < numElements; i++)
		{
			array[i] = rhs.array[i];
		}
		return *this;

	}
	else if (rhs.numElements >= numCapacity)
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
			throw ("ERROR: Unable to allocate a new buffer for vector");
		}
		// copy the items over one at a time using the assignment operator
		for (int i = 0; i < numElements; i++)
		{
			array[i] = rhs.array[i];
		}
		return *this;
	}
	else { return *this; }
}
/*******************************************
 * VECTOR :: size
 *******************************************/
template <class T>
int vector<T>::size() const
{
	return numElements;
}
/*******************************************
 * VECTOR :: capacity
 *******************************************/
template <class T>
int vector<T>::capacity() const
{
	return numCapacity;
}
/*******************************************
 * VECTOR :: empty
 *******************************************/
template <class T>
bool vector<T>::empty() const
{
	if (numElements<1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*******************************************
 * VECTOR:: clear
 *******************************************/
template <class T>
void vector<T>::clear()
{
	numElements = 0;
	
}
/*******************************************
 * VECTOR :: operator (changeable)
 *******************************************/
template <class T>
T& vector<T>::operator [] (int index)
{
	if (!empty()&&index<numElements)
	{
		return array[index];
	}
	else
	{
		throw ("ERROR: Invalid index");
	}
}
/*******************************************
 * VECTOR :: operator (unchangeable)
 *******************************************/
template <class T>
const T& vector<T>::operator [] (int index) const
{
	if (!empty() && index < numElements)
	{
		return array[index];
	}
	else
	{
		throw ("ERROR: Invalid index");
	}
}
/*******************************************
 * VECTOR :: push_back
 *******************************************/
template <class T>
void vector<T>::push_back(const T& t)
{
	if (size() == capacity())
	{
		resize(capacity());
		array[numElements] = t;
		numElements++;
	}
	else
	{
		array[numElements] = t;
		numElements++;
	}
}
/*******************************************
 * VECTOR :: resize
 *******************************************/
template <class T>
void vector<T>::resize(int numCapacity)
{
	if (numCapacity<1)
	{
		this->numCapacity = 1;
		// attempt to allocate
		try
		{	
			T* temp=new T[this->numCapacity];
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
		this->numCapacity *= 2;
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
}



	
}; //namespace custom
#endif