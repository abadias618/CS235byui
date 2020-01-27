/***********************************************************************
 * Header:
 *    List
 * Summary:
 *    contains a list template that will grant access to the list of nodes 
 *	  through an iterator
 *    This will contain the class definition of:
 *       list             : a list of nodes
 *       list :: iterator : an iterator through the list of nodes
 * Author
 *    Abdias Baldiviezo & Kevin Hisel
 ************************************************************************/
#ifndef LIST_H
#define LIST_H
namespace custom 
{
template <class T>
class list
{
public:
	//default constructor
	list();
	//copy constructor
	list(const list& rhs);
	//destructor
	~list();
	//assgn operator
	list& operator=(const list& rhs);
	//introduce & eliminate elements
	void push_back(const T& t);
	void push_front(const T& t);
	void pop_back();
	void pop_front();
	// getters
	T& back();
	T& front();
	T back()const;
	T front()const;
	//standard container interfaces
	int size()const;
	bool empty()const;
	void clear();



	// the various iterator interfaces
	class iterator;
	iterator begin()const;
	iterator end()const;
	iterator insert(const iterator& it, const T& t);
	iterator find(const T& t);
	iterator erase(const iterator& it);

	//reverse iterator
	class reverse_iterator;
	reverse_iterator rbegin();
	reverse_iterator rend();

	//constant iterator
	class const_iterator;
	const_iterator cbegin()const;
	const_iterator cend()const;

	//const reverse iterator
	class const_reverse_iterator;
	const_reverse_iterator crbegin()const;
	const_reverse_iterator crend()const;

private:
	class Node {
	public:
		//default constructor
		Node() {
			data = NULL;
			pPrev = NULL;
			pNext = NULL;
		};
		//non-default constructor
		Node(const T& t) {
			data = t;
			pPrev = NULL;
			pNext = NULL;
		};
		//data element
		T data;
		//previous pointer
		Node* pPrev;
		//next pointer
		Node* pNext;
	};// class node;

	int numElements;
	Node* pHead;
	Node* pTail;

};

/**************************************************
 * LIST ITERATOR
 * An iterator through the list
 *************************************************/
template <class T>
class list <T> ::iterator
{
public:
	// constructors, destructors, and assignment operator
	iterator() : p(NULL) {};
	iterator(Node* p) : p(p) {
	};
	iterator(const iterator& rhs) {
		if (rhs!=NULL)
		{
			p = rhs.p;
		}
		else
		{
			p->data = T();
			p->pNext = NULL;
			p->pPrev = NULL;
		}
		
	};
	iterator& operator = (const iterator& rhs)
	{
		if (rhs!=NULL)
		{
			p = rhs.p;
		}
		else
		{
			p = NULL;
		}
		

		return *this;
	}
	// friend function to access p
	friend iterator list<T>::insert(const iterator& it, const T& t);
	//also erase access' p
	friend iterator list<T>::erase(const iterator& it);

	// equals, not equals operator
	bool operator != (const iterator& rhs) const
	{
		if (rhs.p != nullptr)
		{
			return p->data != rhs.p->data;
		}
		else
		{
			return p!=nullptr;
		}
		
	}
	bool operator == (const iterator& rhs) const
	{
		if (rhs.p != nullptr)
		{
			return p->data == rhs.p->data;
		}
		else
		{
			return p == nullptr;
		}
	}

	// dereference operator
	T& operator * () { return p->data; }
	const T& operator * () const { return p->data; }

	// prefix increment
	iterator& operator ++ ()
	{
		if (p!=NULL)
		{
			p = p->pNext;
		}
		else
		{
			p = NULL;
		}
		

		return *this;
	}

	// postfix increment
	iterator operator ++ (int postfix)
	{
		iterator tmp(*this);
		tmp = tmp.p->pNext;
		return tmp;
	}

	// prefix decrement
	iterator& operator -- ()
	{
		if (p!= NULL)
		{
			p = p->pPrev;
		}
		else
		{
			p = NULL;
		}
		return *this;
	}
	// postfix decrement
	iterator operator -- (int prefix)
	{
		iterator tmp(*this);
		if (tmp.p->pPrev != NULL)
		{
			tmp = tmp.p->pPrev;
		}
		return tmp;
	}

private:
	Node* p;
};
/**************************************************
 * LIST CONSTANT ITERATOR
 * An iterator through the list that is constant
 *************************************************/
template <class T>
class list <T> ::const_iterator
{
public:
	// constructors, destructors, and assignment operator
	const_iterator() : p(NULL) {};
	const_iterator(Node* p) : p(p) {
	};
	const_iterator(const const_iterator& rhs) {
		if (rhs != NULL)
		{
			p = rhs.p;
		}
		else
		{
			p->data = T();
			p->pNext = NULL;
			p->pPrev = NULL;
		}

	};
	iterator& operator = (const const_iterator& rhs)
	{
		if (rhs != NULL)
		{
			p = rhs.p;
		}
		else
		{
			p = NULL;
		}


		return *this;
	}
	

	// equals, not equals operator
	bool operator != (const const_iterator& rhs) const
	{
		if (rhs.p != nullptr)
		{
			return p->data != rhs.p->data;
		}
		else
		{
			return p != nullptr;
		}

	}
	bool operator == (const const_iterator& rhs) const
	{
		if (rhs.p != nullptr)
		{
			return p->data == rhs.p->data;
		}
		else
		{
			return p == nullptr;
		}
	}

	// dereference operator
	T& operator * () { return p->data; }
	const T& operator * () const { return p->data; }

	// prefix increment
	const_iterator& operator ++ ()
	{
		if (p != NULL)
		{
			p = p->pNext;
		}
		else
		{
			p = NULL;
		}
		return *this;
	}

	// postfix increment
	const_iterator operator ++ (int postfix)
	{
		const_iterator tmp(*this);
		tmp = tmp.p->pNext;
		return tmp;
	}

	// prefix decrement
	const_iterator& operator -- ()
	{
		if (p->pPrev != NULL)
		{
			p = p->pPrev;
		}
		return *this;
	}
	// postfix decrement
	const_iterator operator -- (int prefix)
	{
		const_iterator tmp(*this);
		if (tmp.p->pPrev != NULL)
		{
			tmp = tmp.p->pPrev;
		}
		return tmp;
	}

private:
	Node* p;
};
/**************************************************
 * LIST REVERSE ITERATOR
 * An iterator through the vector
 *************************************************/
template <class T>
class list <T> ::reverse_iterator
{
public:
	// constructors, destructors, and assignment operator
	reverse_iterator() : p(NULL) {};
	reverse_iterator(Node* p) : p(p) {};
	//uses the node copy function
	reverse_iterator(const reverse_iterator& rhs) {
		if (rhs != NULL)
		{
			p = rhs.p;
		}
		else
		{
			p->data = T();
			p->pNext = NULL;
			p->pPrev = NULL;
		}
	};
	reverse_iterator& operator = (const reverse_iterator& rhs)
	{
		if (rhs != NULL)
		{
			p = rhs.p;
		}
		else
		{
			p = NULL;
		}
		return *this;
	}
	
	// equals, not equals operator
	bool operator != (const reverse_iterator& rhs) const
	{
		if (rhs.p != nullptr)
		{
			return p->data != rhs.p->data;
		}
		else
		{
			return p!= nullptr;
		}
	}
	bool operator == (const reverse_iterator& rhs) const
	{
		if (rhs.p != nullptr)
		{
			return p->data == rhs.p->data;
		}
		else
		{
			return p == nullptr;
		}
	}

	// dereference operator
	T& operator * () { return p->data; }
	const T& operator * () const { return p->data; }

	// prefix increment
	reverse_iterator& operator ++ ()
	{
		
		if (p != NULL)
		{
			p = p->pPrev;
		}
		else
		{
			p = NULL;
		}
		return *this;
	}

	// postfix increment
	reverse_iterator operator ++ (int postfix)
	{
		reverse_iterator tmp(*this);
		tmp = tmp.p->pPrev;
		return tmp;
	}

	// prefix increment
	reverse_iterator& operator -- ()
	{
		if (p != NULL)
		{
			p = p->pNext;
		}
		else
		{
			p = NULL;
		}
		return *this;
	}
	// postfix decrement
	reverse_iterator operator -- (int prefix)
	{
		reverse_iterator tmp(*this);
		if (tmp.p->pNext != NULL)
		{
			tmp = tmp.p->pNext;
		}
		return tmp;
	}

private:
	Node* p;
};

/**************************************************
 * LIST CONSTANT REVERSE ITERATOR
 * An iterator through the vector
 *************************************************/
template <class T>
class list <T> ::const_reverse_iterator
{
public:
	// constructors, destructors, and assignment operator
	const_reverse_iterator() : p(NULL) {};
	const_reverse_iterator(Node* p) : p(p) {};
	//uses the node copy function
	const_reverse_iterator(const const_reverse_iterator& rhs) {
		if (rhs != NULL)
		{
			p = rhs.p;
		}
		else
		{
			p->data = T();
			p->pNext = NULL;
			p->pPrev = NULL;
		}
	};
	const_reverse_iterator& operator = (const const_reverse_iterator& rhs)
	{
		if (rhs != NULL)
		{
			p = rhs.p;
		}
		else
		{
			p = NULL;
		}
		return *this;
	}

	// equals, not equals operator
	bool operator != (const_reverse_iterator& rhs) const
	{
		if (rhs.p != nullptr)
		{
			return p->data != rhs.p->data;
		}
		else
		{
			return p != nullptr;
		}
	}
	bool operator == (const const_reverse_iterator& rhs) const
	{
		if (rhs.p == nullptr)
		{
			return p->data != rhs.p->data;
		}
		else
		{
			return p == nullptr;
		}
	}

	// dereference operator
	T& operator * () { return p->data; }
	const T& operator * () const { return p->data; }

	// prefix increment
	const_reverse_iterator& operator ++ ()
	{
		if (p != NULL)
		{
			p = p->pPrev;
		}
		else
		{
			p = NULL;
		}
		return *this;
	}

	// postfix increment
	const_reverse_iterator operator ++ (int postfix)
	{
		const_reverse_iterator tmp(*this);
		tmp = tmp.p->pPrev;
		return tmp;
	}

	// prefix increment
	const_reverse_iterator& operator -- ()
	{
		if (p != NULL)
		{
			p = p->pNext;
		}
		else
		{
			p = NULL;
		}
		return *this;
	}
	// postfix decrement
	const_reverse_iterator operator -- (int prefix)
	{
		const_reverse_iterator tmp(*this);
		if (tmp.p->pNext != NULL)
		{
			tmp = tmp.p->pNext;
		}
		return tmp;
	}

private:
	Node* p;
};







/**************************************************
 * LIST :: default constructor
 * sets the pointers to NULL, creates an empty list 
 *************************************************/
template <class T>
list<T>::list() 
{
	numElements = 0;
	pHead = NULL;
	pTail = NULL;
};
/**************************************************
 * LIST :: destructor
 * delete the list
 *************************************************/
template <class T>
list<T>::~list()
{
	clear();
};
/**************************************************
 * LIST :: copy constructor
 * initiate the list with another list
 *************************************************/
template <class T>
list<T>::list(const list<T>& rhs)
{
	numElements = 0;
	pHead = NULL;
	pTail = NULL;
	if (rhs.pHead != NULL)
	{
		
		if (pHead!=NULL)
		{
			clear();
		}
		
		for (list<T>::iterator it = rhs.begin(); it != rhs.end(); ++it)
		{
			push_back(*it);
		}
		/*pHead = rhs.pHead;
		pTail = rhs.pTail;*/
		
	}
};
/**************************************************
 * LIST :: assignment operator =
 * deletes all elements and then populates with rhs nodes
 *************************************************/
template <class T>
list<T>& list<T>::operator =(const list<T>& rhs)
{
	
	if (rhs.pHead!=NULL)
	{
		if (pHead != NULL)
		{
			clear();
		}
		for (list<T>::iterator it = rhs.begin(); it != rhs.end(); ++it)
		{
			push_back(*it);
		}
		//pHead = rhs.pHead;
		//pTail = rhs.pTail;
		return *this;
	}
	else
	{
		return *this;
	}
};
/**************************************************
 * LIST :: size()
 * Return: true if the numElements is 0, false if not
 *************************************************/
template <class T>
int list<T>::size()const
{
	return numElements;
};
/**************************************************
 * LIST :: empty()
 * Return: true if the numElements is 0, false if not
 *************************************************/
template <class T>
bool list<T>::empty()const
{
	if (numElements<1)
	{
		return true;
	}
	else
	{
		return false;
	}
};
/**************************************************
 * LIST :: size()
 * Return: true if the numElements is 0, false if not
 *************************************************/
template <class T>
void list<T>::clear()
{
	if (pHead!=NULL && pTail!=NULL)
	{
		for (list<T>::iterator it = begin(); it != end();)
		{
			if (it!=NULL)
			{
				it=erase(it);
			}
			else
			{
				++it;
			}
			
		}
		numElements = 0;
		pHead = NULL;
		pTail = NULL;

	}
	
};

/**************************************************
 * LIST :: front(changeable)
 * returns the data from the pHead Node
 *************************************************/
template <class T>
T& list<T>::front()
{
	if (!empty())
	{
		return pHead->data;
	}
	else
	{
		throw "ERROR: unable to access data from an empty list";
	}
};
/**************************************************
 * LIST :: front(unchangeable)
 * returns the data from the pHead Node
 *************************************************/
template <class T>
T list<T>::front()const
{
	if (!empty())
	{
		return pHead->data;
	}
	else
	{
		throw "ERROR: unable to access data from an empty list";
	}
};
/**************************************************
 * LIST :: back(changeable)
 * returns the data from the pTail Node
 *************************************************/
template <class T>
T& list<T>::back()
{
	if (!empty())
	{
		return pTail->data;
	}
	else
	{
		throw "ERROR: unable to access data from an empty list";
	}
};
/**************************************************
 * LIST :: back(unchangeable)
 * returns the data from the pTail Node
 *************************************************/
template <class T>
T list<T>::back()const
{
	if (!empty())
	{
		return pTail->data;
	}
	else
	{
		throw "ERROR: unable to access data from an empty list";
	}
};
/**************************************************
 * LIST :: push_back
 * Param: const element type T
 * Pushes an element to the end of the list
 *************************************************/
template <class T>
void list<T>::push_back(const T& t)
{
	//create new node
	Node* pNew = new Node(t);
	if (pTail != NULL)
	{
		//point new node to prev and next nodes
		pNew->pNext = pTail->pNext;
		pNew->pPrev = pTail;
		//point prev and next nodes to the new node
		pTail->pNext = pNew;
		pTail = pNew;
		numElements++;
	}
	else
	{
		insert(iterator(pNew), t);
	}
	

};
/**************************************************
 * LIST :: push_front
 * Param: const element type T
 * Pushes an element to the beggining of the list
 *************************************************/
template <class T>
void list<T>::push_front(const T& t)
{
	//create new node
	Node* pNew = new Node(t);

	if (pHead != NULL)
	{
		//point new node to prev and next nodes
		pNew->pNext = pHead;
		pNew->pPrev = pHead->pPrev;
		//point prev and next nodes to the new node
		pHead->pPrev = pNew;
		pHead = pNew;
		numElements++;
	}
	else
	{
		insert(iterator(pNew),t);
	}

};
/**************************************************
 * LIST :: pop_back
 * eliminates an element from the back
 *************************************************/
template <class T>
void list<T>::pop_back()
{
	if (pTail!=NULL)
	{
		Node* tmp = pTail->pPrev;
		pTail->pPrev->pNext = NULL;
		pTail = tmp;
		numElements--;
	}
	

};
/**************************************************
 * LIST :: pop_front
 * eliminates an element from the back
 *************************************************/
template <class T>
void list<T>::pop_front()
{
	if (pHead!=NULL)
	{
		Node* tmp=pHead->pNext;
		pHead->pNext->pPrev = NULL;
		pHead = tmp;
		numElements--;
	}

};
/**************************************************
 * LIST :: insert()
 * Param: takes an element of type T and an Iterator
 * Return: returns a pointer to a list
 *************************************************/
template <class T>
typename list<T> ::iterator list<T>::insert(const list<T>::iterator& it, const T& t)
{
	//if they insert a null pointer add to the end
	if (it==NULL)
	{
		Node* pNew = new Node(t);
		pNew->pPrev = pTail;
		pNew->pNext = NULL;
		//point tail to pNew
		pTail->pNext = pNew;
		numElements++;
		pTail = pNew;
		return iterator(pNew);
	}
	//create new node
	Node* pNew = new Node(t);
	if (pHead == NULL && pTail == NULL)
	{
		pHead = pNew;
		pTail = pNew;
		numElements++;
		return iterator(pNew);
	}
	//point new node to prev and next nodes
	pNew->pNext = it.p;
	pNew->pPrev = it.p->pPrev;
	//point prev and next nodes to the new node
	it.p->pPrev = pNew;
	if (pNew->pPrev != NULL)
	{
		pNew->pPrev->pNext = pNew;
	}
	//special cases front and back of the list
	if (pNew->pPrev==NULL)
	{
		pHead = pNew;
	}
	else if (pNew->pNext==NULL)
	{
		pTail = pNew;
	}
	numElements++;
	

	return iterator(pNew);
};
/**************************************************
 * LIST :: find()
 * Param: takes an element of type T
 * Return: returns an iterator to the element with value T if found
 *************************************************/
template <class T>
typename list<T> ::iterator list<T>::find(const T& t)
{
	for (list<T>::iterator  it = it.begin(); it != it.end(); ++it)
	{
		if (t==*it)
		{
			return it;
		}
		else
		{
			return it.end();
		}
	}
	
};

/**************************************************
 * LIST :: erase()
 * Param: takes an iterator
 * Return: returns an iterator pointing to the element 
 *************************************************/
template <class T>
typename list<T> ::iterator list<T>::erase(const iterator& it)
{
	if (it.p!=NULL)
	{
		if (it.p->pPrev == NULL && it.p->pNext == NULL)
		{	
			
			return iterator(NULL);
		}
		else if (it.p->pPrev == NULL)
		{
			pHead = it.p->pNext;
			it.p->pNext->pPrev = NULL;
			//delete it.p;
			return iterator(pHead);
		}
		else if (it.p->pNext == NULL)
		{
			pTail = it.p->pPrev;
			it.p->pPrev->pNext = NULL;
			//delete it.p;
			return iterator(pTail);
		}
		else
		{
			Node* tmp = it.p->pNext;
			//point next node to previous
			it.p->pNext->pPrev = it.p->pPrev;
			//point prev node to next
			it.p->pPrev->pNext = it.p->pNext;
			//delete it.p;
			return  iterator(tmp);
		}
	}
	else
	{
		return iterator(NULL);
	}
	
	
};

/********************************************
 * LIST :: ITERATOR :: begin
 ********************************************/
template <class T>
typename list<T> ::iterator list <T> ::begin()const
{
	return iterator(pHead);
};
/********************************************
 * LIST :: ITERATOR :: end
 ********************************************/
template <class T>
typename list<T> ::iterator list <T> ::end()const
{
	return iterator(NULL);
};


/********************************************
 * LIST :: CONST_ITERATOR :: cbegin
 ********************************************/
template <class T>
typename list<T> ::const_iterator list <T> ::cbegin() const
{
	return const_iterator(pHead);
};

/********************************************
 * LIST :: CONST_ITERATOR :: cend
 ********************************************/
template <class T>
typename list<T> ::const_iterator list <T> ::cend() const
{
	return const_iterator(pHead);
};



/********************************************
 * LIST :: REVERSE ITERATOR :: rbegin
 ********************************************/
template <class T>
typename list<T> ::reverse_iterator list <T> ::rbegin()
{
	return reverse_iterator(pTail);
};
/********************************************
 * LIST :: REVERSE ITERATOR :: rend
 ********************************************/
template <class T>
typename list<T> ::reverse_iterator list <T> ::rend()
{
	return reverse_iterator(NULL);
};


/********************************************
 * LIST :: CONST_REVERSE_ITERATOR :: crbegin
 ********************************************/
template <class T>
typename list<T> ::const_reverse_iterator list <T> ::crbegin() const
{
	return const_reverse_iterator(pHead);
};

/********************************************
 * LIST :: CONST_REVERSE_ITERATOR :: crend
 ********************************************/
template <class T>
typename list<T> ::const_reverse_iterator list <T> ::crend() const
{
	return const_reverse_iterator(pHead);
};

};
#endif // !LIST_H
