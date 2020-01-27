/***********************************************************************
 * Header:
 *    Set
 * Summary:
 *    This class contains the notion of an set
 *
 *    This will contain the class definition of:
 *       set             : similar to std::set
 *       set :: iterator :  nested class an iterator through the set
 * Author
 *    Abdias Baldiviezo
 *    Kevin Hisel
 ************************************************************************/
#ifndef SET_H
#define SET_H
namespace custom 
{
template <class T>
class set 
{
public:
	//constructors & destructors
	set();
	set(int numCapacity);
	set(const set & rhs);
	~set(){ /*delete [] array;*/ };

	//assignment
	set & operator=(const set& rhs);
	//union
	set  operator || (const set& rhs);
	//intersection
	set  operator &&(const set& rhs);
	//difference
	set  operator - (const set& rhs);


	//standar container interfaces
	int size()const;
	bool empty()const;
	void clear();

	void insert(const T & t);
	
	//iterators
	class iterator;
	iterator begin()const;
	iterator end()const;
	iterator find(const T & t);
	iterator erase(iterator & it);
	iterator erase(const T & value);
	//const_iterator
	class const_iterator;
	const_iterator find(const T& t) const;
	const_iterator cbegin()const;
	const_iterator cend()const;
private:
	T* array;
	int numCapacity;
	int numElements;
	int findIndex(const T & t)const;
	void resize(int numCapacity);

};
/**************************************************
 * SET ITERATOR
 * An iterator through the SET
 *************************************************/
template <class T>
class set<T>::iterator 
{
public:
	// constructors, destructors, and assignment operator
	iterator() : p(NULL) {              }
	iterator(T* p) : p(p) {              }
	iterator(const iterator& rhs) { *this = rhs; }
	iterator& operator = (const iterator& rhs)
	{
		this->p = rhs.p;
		return *this;
	}

	// equals, not equals operator
	bool operator != (const iterator& rhs) const { return rhs.p != this->p; }
	bool operator == (const iterator& rhs) const { return rhs.p == this->p; }

	// dereference operator
	T& operator * () { return *p; }
	const T& operator * () const { return *p; }
	
	//adition and substraction
	iterator& operator + (int value) { p = p + value; return *this; }
	iterator& operator - (int value) { p = p - value; return *this; }
	
	// prefix increment
	iterator& operator ++ ()
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
	T* p;
};

/**************************************************
 * VECTOR CONST_ITERATOR
 * An iterator through the vector that is constant
 *************************************************/
template <class T>
class set<T>::const_iterator
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
	const T& operator * () const { return *p; }
	//adition and substraction
	const_iterator& operator + (int value) { p = p + value; return *this; }
	const_iterator& operator - (int value) { p = p - value; return *this; }
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
 * SET :: ITERATOR :: begin
 ********************************************/
template <class T>
typename set<T> ::iterator set<T> ::begin()const
{
	return iterator(array);
}
/********************************************
 * SET :: ITERATOR :: end
 ********************************************/
template <class T>
typename set<T> ::iterator set<T> ::end()const
{
	return iterator(array + numElements);
}
/********************************************
 * SET :: ITERATOR :: cbegin
 ********************************************/
template <class T>
typename set<T> ::const_iterator set<T> ::cbegin() const
{
	return const_iterator(array);
}
/********************************************
 * SET :: ITERATOR :: cend
 ********************************************/
template <class T>
typename set<T> :: const_iterator set<T> ::cend() const
{
	return const_iterator(array + numElements);
}

/*******************************************
 * SET :: default constructor
 *******************************************/
template <class T>
set <T> ::set()
{
	array = NULL;
	numCapacity = 0;
	numElements = 0;

}
/*******************************************
 * SET :: non-default constructor
 *******************************************/
template <class T>
set <T> ::set(int numCapacity)
{
	if (numCapacity < 1)
	{
		array = NULL;
		this->numCapacity = 0;
		numElements = 0;
	}
	else
	{
		// attempt to allocate
		try
		{
			array = new T[numCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for Set";
		}
		this->numCapacity = numCapacity;
		numElements = 0;
	}
}
/*******************************************
 * SET :: copy constructor
 *******************************************/
template <class T>
set <T> :: set(const set<T> & rhs) 
{
	if (rhs.numCapacity<1)
	{
		numCapacity = 0;
		numElements = 0;
		array = NULL;

	}
	else
	{
		// attempt to allocate
		try
		{
			array = new T[rhs.numCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for Set";
		}
		//copy things over
		for (int i = 0; i < rhs.numElements; i++)
		{
			array[i] = rhs.array[i];
		}
		numElements = rhs.numElements;
		numCapacity = rhs.numCapacity;
	}

}
/*******************************************
 * SET :: assignment operator
 *******************************************/
template <class T>
set<T>& set<T>::operator=(const set<T>& rhs) 
{
	if (numCapacity<rhs.numCapacity)
	{
		resize(rhs.numCapacity);
	}
	//copy things over
	for (int i = 0; i < rhs.numElements; i++) 
	{
		array[i] = rhs.array[i];
	}
		
	numElements = rhs.numElements;
	numCapacity = rhs.numCapacity;

	return *this;

	
}
/*******************************************
 * SET :: union operator
 *******************************************/
template <class T>
set<T> set<T>::operator || (const set<T>& rhs)
{
	set<T> returnSet;
	for (int i = 0; i < size(); i++)
	{
		returnSet.insert(array[i]);
	}
	for (int i = 0; i < rhs.size(); i++)
	{
		returnSet.insert(rhs.array[i]);

	}

	return returnSet;

}
/*******************************************
 * SET :: intersection operator
 *******************************************/
template <class T>
set<T> set<T>::operator && (const set<T>& rhs)
{
	set <T> returnSet;
	for (int i = 0; i < numElements; i++)
	{
		const_iterator nul = rhs.cend();
		const_iterator it = rhs.find(array[i]);
		
		if (*it > 0)
		{
			returnSet.insert(array[i]);
		}
	}
	return returnSet;
}
/*******************************************
 * SET :: difference operator
 *******************************************/
template <class T>
set<T> set<T>::operator - (const set<T>& rhs)
{
	set<T> returnSet;
	for (int i = 0; i < numElements; i++)
	{
		const_iterator it = rhs.find(array[i]);
		if (it == rhs.cend())
		{
			returnSet.insert(array[i]);
		}
	}
	return returnSet;
}
/*******************************************
 * SET :: find
 *******************************************/
template <class T>
typename set<T>::iterator set<T>::find (const T& t)
{
	int i = findIndex(t);
	if (i==-1)
	{
		return (end());
	}
	return (array+i);
}
/*******************************************
 * SET :: find (constant)
 *******************************************/
template <class T>
typename set<T>::const_iterator set<T>::find(const T& t)const
{
	int i = findIndex(t);
	if (i==-1)
	{
		return (cend());
	}
	return (cbegin() + i);
}

/*******************************************
 * SET :: size
 *******************************************/
template <class T>
int set<T>::size()const 
{
	return numElements;
}

/*******************************************
 * SET :: empty
 *******************************************/
template <class T>
bool set<T>::empty()const
{
	if (size()<1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*******************************************
 * SET :: clear
 *******************************************/
template <class T>
void set<T>::clear()
{
	numElements = 0;
	numCapacity = 0;
	array = NULL;
}
/*******************************************
 * SET :: erase 
 * find iterator
 *******************************************/
template <class T>
typename set<T>::iterator set<T>::erase(set<T>::iterator & it)
{
	int i = findIndex(*it);
	if (i==-1)
	{
		return(end());
	}
	int v = i;
	//make a new array
	T* temp = new T[numCapacity];
	for (int j = 0, k = 0; j < numElements-1; j++,k++)
	{
		if (j==i)
		{
			temp[j] = array[k+1];
			k++;
			continue;
		}
		temp[j] = array[k];
	}
	this->array = temp;
	numElements--;
	return (array + v);

}
/*******************************************
 * SET :: erase
 * find iterator
 *******************************************/
template <class T>
typename set<T>::iterator set<T>::erase(const T & value)
{
	int i = findIndex(value);
	if (i == -1)
	{
		return(end());
	}
	int v = i;
	//make a new array
	T* temp = new T[numCapacity];
	for (int j = 0, k = 0; j < numElements - 1; j++, k++)
	{
		if (j == i)
		{
			temp[j] = array[k + 1];
			k++;
			continue;
		}
		temp[j] = array[k];
	}
	this->array = temp;
	numElements--;
	return iterator(array+v);
}
/*******************************************
 * SET :: insert
 *******************************************/
template <class T>
void set<T>::insert(const T & t)
{
	int index = findIndex(t);
	if (index==-1 && !empty())
	{
		//resize if needed
		if (size()==numCapacity)
		{
			resize(numCapacity * 2);
		}
		//find where to insert
		int indexToInsert = 0;
		for (int i = 0; i < numElements; i++)
		{
			if (array[i]<=t)
			{
				indexToInsert = i;
			}
			else if (array[i]>t)
			{
				indexToInsert = i - 1;
				break;
			}
		}
		//insert at the begining
		index= 0;
		//move all the array one slot to the right
		for (int j = numElements-1; j > indexToInsert; j--)
		{
			array[j+1] = array[j];
		}
		//finally insert
		array[indexToInsert+1] = t;
		numElements++;
	}
	else if (index==-1 && empty())
	{
		resize(1);
		array[0] = t;
		numElements++;
	}


}
/**************************************************
* SET:: findIndex
* loops through the array to find the index of the element
*************************************************/
template <class T>
int set<T>::findIndex(const T & t)const 
{
	for (int i = 0; i < numElements; i++)
	{
		if (t == array[i])
		{
			return i;
		}
	}
	return -1;
}

/*******************************************
 * SET :: resize
 *******************************************/
template <class T>
void set<T>::resize(int numCapacity)
{
	if (numCapacity<1)
	{
		try
		{
			T* temp = new T[1];
			delete[] array;
			this->numCapacity = 1;
			this->array = temp;
		}
		catch (std::bad_alloc)
		{
			throw "Error: Unable to allocate new buffer for set";
		}
	}
	else
	{
		try
		{
			T* temp = new T[numCapacity];
			for (int i = 0; i < numElements; i++)
			{
				temp[i] = array[i];
			}
			delete[] array;
			this->numCapacity = numCapacity;
			this->array = temp;
		}
		catch (std::bad_alloc)
		{
			throw "Error: Unable to allocate new buffer for set";
		}
	}
}
	


};
#endif // !SET_H
