/***********************************************************************
 * Header:
 *    set
 * Summary:
 *    This class contains the notion of a set: a bucket to hold
 *    data for the user.
 *
 *    This will contain the class definition of:
 *       set :: similar to std::set
 *       set :: iterator : an iterator through the set
 *       set :: const_iterator : a constant iterator through the set
 * Author
 *   Josh Spendlove
 *
 ************************************************************************/

#ifndef SET_H
#define SET_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
    {
    
    /************************************************
     * SET
     * A class that holds stuff
     ***********************************************/
    template <class T>
    class set
    {
    private:
        void resize(int cap);
        int findIndex(const T & t) const;
    public:
        // constructors and destructors
        set() throw (const char *);
        set(int num)                throw (const char *);
        set(const set & rhs)        throw (const char *);
        ~set() { delete [] data; }
        set & operator = (const set & rhs) throw (const char *);
        
        
        void insert(const T & t);
        
        set operator ||(const set & rhs);
        set operator &&(const set & rhs);
        set operator -(const set & rhs);
        
        // standard container interfaces
        int  size()     const { return numElements; }
        int  capacity() const { return numCapacity; }
        
        bool empty() const { return numElements == 0;}
        void clear();
        
        
        // the various iterator interfaces
        class iterator;
        class const_iterator;
        
        iterator find(const T & t);
        iterator erase(iterator it);
        iterator begin() { return iterator (data); }
        iterator end();
        
        
        
        const_iterator cbegin() const { return const_iterator (data); }
        const_iterator cend() const;
        // a debug utility to display the set
        // this gets compiled to nothing if NDEBUG is defined
        void display() const;
        
    private:
        T * data;           // dynamically allocated set of T
        int numElements;
        int numCapacity;
    };
    
    /**************************************************
     * SET ITERATOR
     * An iterator through set
     *************************************************/
    template <class T>
    class set <T> :: iterator
    {
    public:
        // constructors, destructors, and assignment operator
        iterator()      : p(NULL)      {              }
        iterator(T * p) : p(p)         {              }
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
        T & operator * ()       { return *p; }
        const T & operator * () const { return *p; }
        
        // prefix increment
        iterator & operator ++ ()
        {
            p++;
            return *this;
        }
        // prefix decrement
        iterator & operator -- ()
        {
            p--;
            return *this;
        }
        
        // postfix increment
        iterator operator ++ (int postfix)
        {
            iterator tmp(*this);
            p++;
            return tmp;
        }
        // postfix decrement
        iterator operator -- (int postfix)
        {
            iterator tmp(*this);
            p--;
            return tmp;
        }
        
    private:
        T * p;
    };
    
    
    /**************************************************
     * SET ITERATOR
     * An iterator through set
     *************************************************/
    template <class T>
    class set <T> :: const_iterator
    {
    public:
        // constructors, destructors, and assignment operator
        const_iterator()      : p(NULL)      {              }
        const_iterator(T * p) : p(p)         {              }
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
        T & operator * ()       { return *p; }
        const T & operator * () const { return *p; }
        
        // prefix increment
        const_iterator & operator ++ ()
        {
            p++;
            return *this;
        }
        // prefix decrement
        const_iterator & operator -- ()
        {
            p--;
            return *this;
        }
        
        // postfix increment
        const_iterator operator ++ (int postfix)
        {
            const_iterator tmp(*this);
            p++;
            return tmp;
        }
        
        // postfix decrement
        const_iterator operator -- (int postfix)
        {
            const_iterator tmp(*this);
            p--;
            return tmp;
        }
        
    private:
        T * p;
    };
    
    /********************************************
     * SET :: FIND
     * Returns the iterator for the item being
     * searched for.
     ********************************************/
    template <class T>
    typename set <T> :: iterator set <T> :: find(const T & t)
    {
        return iterator (data + findIndex(t));
    }
    
    
    /********************************************
     * SET :: END
     * Returns the iterator for the last item
     * in the set.
     ********************************************/
    template <class T>
    typename set <T> :: iterator set <T> :: end ()
    {
        return iterator (data + numElements);
    }
    
    
    /********************************************
     * SET :: CEND
     * Returns a constant iterator for the last item
     * in the set.
     ********************************************/
    template <class T>
    typename set <T> :: const_iterator set <T> :: cend() const
    {
        return const_iterator (data + numElements);
    }
    
    
    /*******************************************
     * SET :: ASSIGNMENT
     * Sets the value on the left side of the operator
     * equal to the value on the right.
     *******************************************/
    template <class T>
    set <T> & set <T> :: operator = (const set <T> & rhs) throw (const char *)
    {
        
        if (this == &rhs)
            return *this;
        if (rhs.numCapacity == 0)
            return *this;
        if (numCapacity != rhs.numCapacity)
        {
            if (numCapacity > 0)
                delete[] data;
            numCapacity = rhs.numCapacity;
            if (numCapacity > 0)
                data = new T[numCapacity];
        }
        numElements = 0;
        numCapacity = rhs.numCapacity;
        for (int i = 0; i < rhs.numElements; i++)
        {
            data[i] = rhs.data[i];
            numElements++;
        }
        
        return *this;
    }
    
    
    /*******************************************
     * SET :: COPY CONSTRUCTOR
     * Creates a copy of the passed set.
     *******************************************/
    template <class T>
    set <T> :: set(const set <T> & rhs)  throw (const char *)
    {
        assert(rhs.numElements >= 0);
        
        // do nothing if there is nothing to do
        if (rhs.numElements == 0)
        {
            numCapacity = 0;
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
        {
            data[i] = rhs.data[i];
        }
    }
    
    
    /*******************************************
     * SET :: DEFAULT CONSTRUCTOR
     * Creates the set and initilizes all variables to 0;
     *******************************************/
    template <class T>
    set <T> :: set() throw (const char *)
    {
        numElements = 0;
        numCapacity = 0;
        data = NULL;
        // attempt to allocate
        try
        {
            data = new T[numCapacity];
        }
        catch (std::bad_alloc)
        {
            throw "ERROR: Unable to allocate buffer";
        }
    }
    
    
    /**********************************************
     * SET : NON-DEFAULT CONSTRUCTOR
     * Preallocate the set to "capacity"
     **********************************************/
    template <class T>
    set <T> :: set(int num) throw (const char *)
    {
        assert(num >= 0);
        
        // do nothing if there is nothing to do.
        // since we can't grow an array, this is kinda pointless
        if (num == 0)
        {
            numCapacity = 0;
            numElements = 0;
            data = NULL;
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
        numElements = 0;
        numCapacity = num;
    }
    
    
    /********************************************
     * SET : CLEAR
     * clears the contents of the set
     *******************************************/
    template <class T>
    void set <T> :: clear()
    {
        numElements = 0;
    }
    
    
    /********************************************
     * SET : INSERT
     * Checks to see if the passed value is already
     * in the set. If not it inserts the passed value into the correct
     * position of the set.
     *******************************************/
    template <class T>
    void set <T> :: insert(const T & t)
    {
        int iInsert = findIndex(t);
        
        if (numElements + 1 >= numCapacity)
        {
            resize(numCapacity);
        }
        if (numElements == 0)
        {
            data[iInsert] = t;
            
            numElements++;
        }
        else if (data[iInsert] != t)
        {
            while ((data[iInsert - 1]) > t)
            {
                iInsert--;
            }
            
            for (int i = numElements; i > iInsert; i--)
            {
                data[i] = data[i - 1];
            }
            data[iInsert] = t;
			numElements++;
        }
    }
    
    
    /********************************************
     * SET : ERASE
     * Checks to see if the value of the passed iterator
     * exists in the set, if so, it deletes the item from
     * the set by moving each item behind it forward one.
     *******************************************/
    template <class T>
    typename set <T> :: iterator set <T> :: erase(iterator it)
    {
        T item = *it;
        int iErase = findIndex(item);
        
        if (data[iErase] == *it)
        {
            for (int i = iErase; i < numElements; i++)
            {
                data[i] = data[i + 1];
            }
            numElements--;
        }
        
        return it;
    }
    
    
    /********************************************
     * SET : UNION
     * Creates a new set with all of the contents
     * of both the lhs and rhs sets.
     *******************************************/
    template <class T>
    set <T> set <T> :: operator ||(const set & rhs)
    {
        set <T> temp;
        int iLhs = 0;
        int iRhs = 0;
        
        while (iLhs < numElements || iRhs < rhs.numElements)
        {
            if (iLhs == numElements)
            {
                temp.insert(rhs.data[iRhs++]);
            }
            else if (iRhs == rhs.numElements)
            {
                temp.insert(data[iLhs++]);
            }
            else if (data[iLhs] == rhs.data[iRhs])
            {
                temp.insert(data[iLhs]);
                iLhs++;
                iRhs++;
            }
            else if (data[iLhs] < (rhs.data[iRhs]))
            {
                temp.insert(data[iLhs++]);
            }
            else
            {
                temp.insert(rhs.data[iRhs++]);
            }
        }
        return temp;
    }
    
    
    /********************************************
     * SET : INTERSECTION
     * Creates a new set with all contents that
     * can be found in both the lhs and
     * rhs sets.
     *******************************************/
    template <class T>
    set <T> set <T> :: operator &&(const set & rhs)
    {
        set <T> temp;
        int iLhs = 0;
        int iRhs = 0;
        
        for (iLhs; iLhs < numElements; iLhs++)
        {
            if (rhs.findIndex(data[iLhs]) != rhs.numElements)
                temp.insert(data[iLhs]);
        }
        
        for (iRhs; iRhs < rhs.numElements; iRhs++)
        {
            if (findIndex(rhs.data[iRhs]) != numElements)
                temp.insert(rhs.data[iRhs]);
        }
        return temp;
    }
    
    
    /********************************************
     * SET : DIFFERENCE
     * Creates a new set with all contents of the
     * lhs set that are not found in the rhs set.
     *******************************************/
    template <class T>
    set <T> set <T> :: operator -(const set & rhs)
    {
        set <T> temp;
        
        for(int i = 0; i < numElements; i++)
        {
            if(rhs.findIndex(data[i]) == rhs.numElements)
            {
                temp.insert(data[i]);
            }
        }
        return temp;
    }
    
    
    /********************************************
     * SET :: FINDINDEX
     * Returns the position for the item being
     * searched for as an int.
     ********************************************/
    template <class T>
    int set <T> :: findIndex(const T & t) const
    {
        int iBegin = 0;
        int iEnd = numElements - 1;
        int iMiddle;
        while (iBegin <= iEnd)
        {
            iMiddle = (iBegin + iEnd) / 2;
            
            if (t == (data[iMiddle]))
            {
                return iMiddle;
            }
            else if (t < (data[iMiddle]))
            {
                iEnd = iMiddle - 1;
            }
            else
            {
                iBegin = iMiddle + 1;
            }
        }
        return numElements;
    }
    
    /********************************************
     * SET : RESIZE
     * Resizes the set to twice the capacity
     * of the passed variable.
     *******************************************/
    template <class T>
    void set <T> :: resize(int cap)
    {
        int tempCapacity = numCapacity;
        int tempSize = size();
        
        if (cap == 0)
        {
            numCapacity = 1;
            data = new T[numCapacity];
            return;
        }
        
        T * tempOld = new T[cap];
        int i;
        for (i = 0; i < tempSize; i++)
        {
            tempOld[i] = data[i];
        }
        numCapacity = cap * 2;
        data = new T[numCapacity];
        
        for (int j = 0; j < tempSize; j++)
        {
            data[j] = tempOld[j];
        }
        
        delete [] tempOld;
    }
    
    
    /********************************************
     * SET : DISPLAY
     * A debug utility to display the contents of the set
     *******************************************/
    template <class T>
    void set <T> :: display() const
    {
#ifndef NDEBUG
        std::cout << "set<T>::display()\n";
        std::cout << "\tnum = " << numElements << "\n";
        for (int i = 0; i < numElements; i++)
            std::cout << "\tdata[" << i << "] = " << data[i].index() << "\n";
#endif // NDEBUG
    }
    
    
    }; // namespace custom

#endif // SET_H



