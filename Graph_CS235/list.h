/***********************************************************************
 * Header:
 *    LIST
 * Summary:
 *    This class contains the notion of a list: a bucket to hold
 *    data for the user.
 *
 *    This will contain the class definition of:
 *       list :: similar to std::list
 *       list :: iterator : an iterator through the list
 *       list :: const_iterator : a constant iterator through the list
 *       list :: reverse_iterator : an iterator through the list in reverse.
 *       list :: const_reverse_iterator : a constant iterator through the list in reverse.
 * Author
 *   Josh Spendlove and David Slone
 *
 ************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <cassert>  // because I am paranoid
#include <cstddef>
#include <new>
// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
    {
    
    /************************************************
     * LIST
     * A class that holds stuff
     ***********************************************/
    template <class T>
    class list
    {
    private:
        
    public:
        // constructors and destructors
        list() throw (const char *);
        list(const list & rhs)        throw (const char *);
        ~list() { ; }
        list & operator = (const list & rhs) throw (const char *);
        
        // standard container interfaces
        int  size()     const { return numElements; }
        
        bool empty() const { return numElements == 0;}
        void clear();
        
        void push_back(const T & t);
        void push_front(const T & t);
        void pop_front();
        void pop_back();
        
        T & front();
        T & back();
        T & back() const;
        T & front() const;
        
        
        class Node;
        class iterator;
        class const_iterator;
        class reverse_iterator;
        class const_reverse_iterator;
        
        iterator find(const T & t);
        iterator erase(iterator & it);
        iterator insert(iterator & it, const T & t);
        iterator begin() { return iterator (pHead); }
        iterator end();
        const_iterator cbegin() const { return const_iterator (pHead); }
        const_iterator cend() const;
        reverse_iterator rbegin() { return reverse_iterator (pTail); }
        reverse_iterator rend();
        const_reverse_iterator crbegin() const { return const_reverse_iterator (pTail); }
        const_reverse_iterator crend() const;
        // this gets compiled to nothing if NDEBUG is defined
        void display() const;
        
    private:
        int numElements;
        Node * pHead;
        Node * pTail;
    };
    
    /**************************************************
     *NODE
     * An implementation of a node for use within the List class
     *************************************************/
    template <class T>
    class list <T> :: Node
    {
    public:
        Node() : pNext(NULL), pPrev(NULL) { }
        Node(const T & t) : data(t), pNext(NULL), pPrev(NULL) { }
        T data;
        Node * pNext;
        Node * pPrev;
    };
    /**************************************************
     * LIST ITERATOR
     * An iterator through list
     *************************************************/
    template <class T>
    class list <T> :: iterator
    {
    public:
        // constructors, destructors, and assignment operator
        iterator()      : p(NULL)      {              }
        iterator(Node * p) : p(p)         {              }
        iterator(const iterator & rhs) { *this = rhs; }
        iterator & operator = (const iterator & rhs)
        {
            this->p = rhs.p;
            return *this;
        }
        
        friend iterator list<T> :: insert(iterator & it, const T & t);
        friend iterator list<T> :: erase(iterator & it);
        // equals, not equals operator
        bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
        bool operator == (const iterator & rhs) const { return rhs.p == this->p; }
        
        // dereference operator
        T & operator * ()       { return p->data; }
        const T & operator * () const { return p->data; }
        
        // prefix increment
        iterator & operator ++ ()
        {
            p = p->pNext;
            return *this;
        }
        // prefix decrement
        iterator & operator -- ()
        {
            p = p->pPrev;
            return *this;
        }
        
        // postfix increment
        iterator operator ++ (int postfix)
        {
            iterator tmp(p);
            p = p->pNext;
            return tmp;
        }
        // postfix decrement
        iterator operator -- (int postfix)
        {
            iterator tmp(p);
            p = p->pPrev;
            return tmp;
        }
        
    private:
        Node * p;
    };
    
    /**************************************************
     * LIST REVERSE_ITERATOR
     * An iterator through list that goes in reverse.
     *************************************************/
    template <class T>
    class list <T> :: reverse_iterator
    {
    public:
        // constructors, destructors, and assignment operator
        reverse_iterator()      : p(NULL)      {              }
        reverse_iterator(Node * p) : p(p)         {              }
        reverse_iterator(const reverse_iterator & rhs) { *this = rhs; }
        reverse_iterator & operator = (const reverse_iterator & rhs)
        {
            this->p = rhs.p;
            return *this;
        }
        
        // equals, not equals operator
        bool operator != (const reverse_iterator & rhs) const { return rhs.p != this->p; }
        bool operator == (const reverse_iterator & rhs) const { return rhs.p == this->p; }
        
        // dereference operator
        T & operator * ()       { return p->data; }
        const T & operator * () const { return p->data; }
        
        // prefix increment
        reverse_iterator & operator ++ ()
        {
            p = p->pPrev;
            return *this;
        }
        // prefix decrement
        reverse_iterator & operator -- ()
        {
            p = p->pNext;
            return *this;
        }
        
        // postfix increment
        reverse_iterator operator ++ (int postfix)
        {
            reverse_iterator tmp(p);
            p = p->pPrev;
            return tmp;
        }
        
        // postfix decrement
        reverse_iterator operator -- (int postfix)
        {
            reverse_iterator tmp(p);
            p = p->pNext;
            return tmp;
        }
        
    private:
        Node * p;
    };
    
    
    /**************************************************
     * LIST CONST_ITERATOR
     * An iterator through list
     *************************************************/
    template <class T>
    class list <T> :: const_iterator
    {
    public:
        // constructors, destructors, and assignment operator
        const_iterator()      : p(NULL)      {              }
        const_iterator(Node * p) : p(p)         {              }
        const_iterator(const const_iterator & rhs) { *this = rhs; }
        const_iterator & operator = (const const_iterator & rhs)
        {
            this->p = rhs.p;
            return *this;
        }
        
        
        // equals, not equals operator
        bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
        bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }
        
        // dereference operator
        T & operator * ()       { return p->data; }
        const T & operator * () const { return p->data; }
        
        // prefix increment
        const_iterator & operator ++ ()
        {
            p = p->pNext;
            return *this;
        }
        // prefix decrement
        const_iterator & operator -- ()
        {
            p = p->pPrev;
            return *this;
        }
        
        // postfix increment
        const_iterator operator ++ (int postfix)
        {
            const_iterator tmp(p);
            p = p->pNext;
            return tmp;
        }
        // postfix decrement
        const_iterator operator -- (int postfix)
        {
            const_iterator tmp(p);
            p = p->pPrev;
            return tmp;
        }
        
    private:
        Node * p;
    };
    
    
    /**************************************************
     * LIST CONST_REVERSE_ITERATOR
     * An iterator through list that goes in reverse.
     *************************************************/
    template <class T>
    class list <T> :: const_reverse_iterator
    {
    public:
        // constructors, destructors, and assignment operator
        const_reverse_iterator()      : p(NULL)      {              }
        const_reverse_iterator(Node * p) : p(p)         {              }
        const_reverse_iterator(const const_reverse_iterator & rhs) { *this = rhs; }
        const_reverse_iterator & operator = (const const_reverse_iterator & rhs)
        {
            this->p = rhs.p;
            return *this;
        }
        
        
        // equals, not equals operator
        bool operator != (const const_reverse_iterator & rhs) const { return rhs.p != this->p; }
        bool operator == (const const_reverse_iterator & rhs) const { return rhs.p == this->p; }
        
        // dereference operator
        T & operator * ()       { return p->data; }
        const T & operator * () const { return p->data; }
        
        // prefix increment
        const_reverse_iterator & operator ++ ()
        {
            p = p->pPrev;
            return *this;
        }
        // prefix decrement
        const_reverse_iterator & operator -- ()
        {
            p = p->pNext;
            return *this;
        }
        
        // postfix increment
        const_reverse_iterator operator ++ (int postfix)
        {
            const_reverse_iterator tmp(p);
            p = p->pPrev;
            return tmp;
        }
        
        // postfix decrement
        const_reverse_iterator operator -- (int postfix)
        {
            const_reverse_iterator tmp(p);
            p = p->pNext;
            return tmp;
        }
        
    private:
        Node * p;
    };
    
    /********************************************
     * LIST :: END
     * Returns the iterator for the last item
     * in the list.
     ********************************************/
    template <class T>
    typename list <T> :: iterator list <T> :: end ()
    {
        return iterator (NULL);
    }
    
    /********************************************
     * LIST :: REND
     * Returns an iterator for the list item
     * in the list moving backward
     ********************************************/
    template <class T>
    typename list <T> :: reverse_iterator list <T> :: rend ()
    {
        return reverse_iterator (NULL);
    }
    
    /********************************************
     * LIST :: CREND
     * Returns a constant iterator for the list item
     * in the list moving backward
     ********************************************/
    template <class T>
    typename list <T> :: const_reverse_iterator list <T> :: crend () const
    {
        return const_reverse_iterator (NULL);
    }
    
    
    /********************************************
     * LIST :: CEND
     * Returns a constant iterator for the last item
     * in the list.
     ********************************************/
    template <class T>
    typename list <T> :: const_iterator list <T> :: cend() const
    {
        return const_iterator (NULL);
    }
    
    
    /*******************************************
     * LIST :: ASSIGNMENT
     * Sets the value on the left side of the operator
     * equal to the value on the right.
     *******************************************/
    template <class T>
    list <T> & list <T> :: operator = (const list <T> & rhs) throw (const char *)
    {
        
        if (this == &rhs)
            return *this;
        numElements = 0;
        
        if (rhs.numElements == 0)
        {
            pHead = new Node();
            pTail = pHead;
            return *this;
        }
        
        for (Node * p = rhs.pHead; p; p = p->pNext)
        {
            push_back(p->data);
        }
        
        return *this;
    }
    
    
    /*******************************************
     * LIST :: COPY CONSTRUCTOR
     * Creates a copy of the passed list.
     *******************************************/
    template <class T>
    list <T> :: list(const list <T> & rhs)  throw (const char *)
    {
        assert(rhs.numElements >= 0);
        numElements = 0;
        // do nothing if there is nothing to do
        if (rhs.numElements == 0)
        {
            
            pHead = new Node();
            pTail = pHead;
            return;
        }
        
        // attempt to allocate
        try
        {
            pHead = new Node();
            pTail = pHead;
        }
        catch (std::bad_alloc)
        {
            throw "ERROR: Unable to allocate buffer";
        }
        
        // copy the items over one at a time using the assignment operator
        for (Node * p = rhs.pHead; p; p = p->pNext)
        {
            push_back(p->data);
        }
    }
    
    /********************************************
    * LIST : DEFAULT CONSTRUCTOR
    * creates a new List.
    *******************************************/
    template <class T>
    list <T> :: list()  throw (const char *)
    {
        numElements = 0;
        pHead = NULL;
        pTail = pHead;
        return;
    }
    
    /********************************************
     * LIST : PUSH_BACK
     * Adds an item to the back of the
     * list.
     *******************************************/
    template <class T>
    void list <T> :: push_back(const T & t)
    {
        if (!pHead)
        {
            pHead = new Node();
        }
        if (numElements == 0)
        {
            pHead->data = t;
            pTail = pHead;
        }
        else
        {
            Node * newTail = new Node(t);
            pTail->pNext = newTail;
            newTail->pPrev = pTail;
            pTail = newTail;
        }
        numElements++;
    }
    
    
    /********************************************
     * LIST : PUSH_FRONT
     * Adds an item to the front of the
     * list.
     *******************************************/
    template <class T>
    void list <T> :: push_front(const T & t)
    {
        if (!pHead)
        {
            pHead = new Node();
        }
        if (numElements == 0)
        {
            pHead->data = t;
            pTail = pHead;
        }
        
        else
        {
            Node * newHead = new Node(t);
            pHead->pPrev = newHead;
            newHead->pNext = pHead;
            pHead = newHead;
        }
        numElements++;
    }
    
    /********************************************
     * LIST : POP_FRONT
     * Removes an item from the front of the
     * list.
     *******************************************/
    template <class T>
    void list <T> :: pop_front()
    {
		if (pHead->pNext != NULL)
		{
			pHead = pHead->pNext;
			numElements--;
		}
            

    }
    
    /********************************************
     * LIST : POP_BACK
     * Removes an item from the back of the
     * list.
     *******************************************/
    template <class T>
    void list <T> :: pop_back()
    {
        if (pTail->pPrev != NULL)
            pTail = pTail->pPrev;
    }
   
    /********************************************
     * LIST : BACK
     * Returns the last item in the list.
     *******************************************/
    template <class T>
    T & list <T> :: back()
    {
        return pTail->data;
    }
    
    /********************************************
     * LIST : FRONT
     * Returns the first item in the list.
     *******************************************/
    template <class T>
    T & list <T> :: front()
    {
        return pHead->data;
    }
    
    /********************************************
     * LIST : BACK
     * Returns the last item in the list.
     *******************************************/
    template <class T>
    T & list <T> :: back() const
    {
        return pTail->data;
    }
    
    /********************************************
     * LIST : FRONT
     * Returns the first item in the list.
     *******************************************/
    template <class T>
    T & list <T> :: front() const
    {
        return pHead->data;
    }
    
    
    /********************************************
     * LIST : CLEAR
     * clears the contents of the list
     *******************************************/
    template <class T>
    void list <T> :: clear()
    {
        numElements = 0;
        pHead = NULL;
        pTail = pHead;
    }
    
    
    /********************************************
     * LIST : INSERT
     * Inserts the passed T variable before
     * the item referenced by the iterator.
     *******************************************/
    template <class T>
    typename list <T> :: iterator list <T> :: insert(iterator & it, const T & t)
    {
        Node * pCurrent = it.p;
        Node * pNode = new Node(t);
        
        if (pCurrent == pHead)
        {
            pNode->pNext = pHead;
            pHead = pNode;
        }
        else if (pCurrent != pHead && pCurrent != NULL)
        {
            pNode->pNext = pCurrent;
            pNode->pPrev = pCurrent->pPrev;
            pCurrent->pPrev = pNode;
            
            if (pNode->pPrev)
            {
                pNode->pPrev->pNext = pNode;
            }
        }
        else if (pCurrent == NULL && numElements > 0)
        {
            pNode->pPrev = pTail;
            pTail->pNext = pNode;
            pTail = pNode;
            
        }
        else
        {
            pHead = pNode;
            pTail = pHead;
        }
        ++numElements;
        return iterator (pNode);
    }
    
    /********************************************
     * LIST : FIND
     * Searches the List for item passed as
     * a parameter. If found, an iterator to
     * this item is returned. If not, and iterator
     * to the end is returned.
     *******************************************/
    template <class T>
    typename list <T> :: iterator list <T> :: find(const T & t)
    {
        for (Node * p = pHead; p; p = p->pNext)
        {
            if(p->data == t)
                return iterator (p);
        }
        return iterator (NULL);
    }
    
    /********************************************
     * LIST : ERASE
     * Removes the passed iterator from
     * the list, and links the items around it
     * together.
     *******************************************/
    template <class T>
    typename list <T> :: iterator list <T> :: erase(iterator & it)
    {
        Node * pRemove = it.p;
        
        if (pRemove == pTail)
        {
            pTail = pTail->pPrev;
            pTail->pPrev->pNext = pTail;
            pTail->pNext = NULL;
            
            delete pRemove;
            --numElements;
            return iterator (pTail);
        }
        else
        {
            if (pRemove->pPrev != NULL)
            {
                pRemove->pPrev->pNext = pRemove->pNext;
            }
            if (pRemove->pNext != NULL)
            {
                pRemove->pNext->pPrev = pRemove->pPrev;
            }
        }
        
        Node * pReturn;
        if (pRemove->pPrev != NULL)
        {
            pReturn = pRemove->pPrev;
        }
        else
        {
            pReturn = pRemove->pNext;
            pHead = pReturn;
        }
        --numElements;
        delete pRemove;
        return iterator (pReturn);
    }
    
    
    /********************************************
     * LIST : DISPLAY
     * A debug utility to display the contents of the list
     *******************************************/
    template <class T>
    void list <T> :: display() const
    {
#ifndef NDEBUG
        std::cout << "list<T>::display()\n";
        std::cout << "\tnum = " << numElements << "\n";
        for (Node * p = pTail; p; p = p->pPrev)
            std::cout << p->data << "\n";
#endif // NDEBUG
    }
    
    }; // namespace custom

#endif // LIST_H



