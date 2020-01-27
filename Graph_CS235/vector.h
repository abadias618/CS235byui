/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This class contains the notion of a vector: a bucket to hold
 *    data for the user.
 *
 *    This will contain the class definition of:
 *       vector             : similar to std::vector
 *       vector :: iterator : an iterator through the vector
 * Author
 *    Br. Helfrich
 *
 * Modified by: Josh Spendlove
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

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
     * VECTOR
     * A class that holds stuff
     ***********************************************/
    template <class T>
    class vector
    {
    private:
        void resize(int cap);
    public:
        // constructors and destructors
        vector();
        vector(int num);
        vector(const vector & rhs);
		~vector() { ; } //if(data != NULL) delete [] data;   }
        vector & operator = (const vector & rhs);
        
        // the push_back method to add data to the vector
        void push_back(const T & t);
        
        // standard container interfaces
        int  size()     const { return numElements;                 }
        int  capacity() const { return numCapacity;                 }
        
        bool empty() const { return numElements == 0;}
        void clear();
        void deleteItem(int);
        
        // vector-specific interfaces
        // what would happen if I passed -1 or something greater than num?
        T & operator [] (int index)
        {
            return data[index];
        }
        const T & operator [] (int index) const
        {
            return data[index];
        }
        
        // the various iterator interfaces
        class iterator;
        class const_iterator;
        
        iterator begin()      { return iterator (data); }
        iterator end();
        
        
        
        const_iterator cbegin() const { return const_iterator (data); }
        const_iterator cend() const;
        // a debug utility to display the vector
        // this gets compiled to nothing if NDEBUG is defined
        void display() const;
        
    private:
        T * data;           // dynamically allocated vector of T
        int numElements;
        int numCapacity;
    };
    
    /**************************************************
     * VECTOR ITERATOR
     * An iterator through vector
     *************************************************/
    template <class T>
    class vector <T> :: iterator
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
     * VECTOR ITERATOR
     * An iterator through vector
     *************************************************/
    template <class T>
    class vector <T> :: const_iterator
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
     * VECTOR :: END
     * Note that you have to use "typename" before
     * the return value type
     ********************************************/
    template <class T>
    typename vector <T> :: iterator vector <T> :: end ()
    {
        return iterator (data + numElements);
    }
    
    
    template <class T>
    typename vector <T> :: const_iterator vector <T> :: cend() const
    {
        return const_iterator (data + numElements);
    }
    /*******************************************
     * VECTOR :: Assignment
     *******************************************/
    template <class T>
    vector <T> & vector <T> :: operator = (const vector <T> & rhs)
    {
        numElements = 0;
        for (int i = 0; i < rhs.numElements; i++)
            push_back(rhs.data[i]);
        numElements = rhs.numElements;
        return *this;
    }
    
    /*******************************************
     *
     VECTOR :: COPY CONSTRUCTOR
     *******************************************/
    template <class T>
    vector <T> :: vector(const vector <T> & rhs)
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
            this->data[i] = rhs.data[i];
    }
    
    
    /*******************************************
     *
     VECTOR :: DEFAULT CONSTRUCTOR
     *******************************************/
    template <class T>
    vector <T> :: vector()
    {
        numElements = 0;
        numCapacity = 0;
        this->data = NULL;
        // attempt to allocate
        try
        {
            data = new T[numCapacity];
        }
        catch (std::bad_alloc)
        {
            std::cout << "ERROR";
            throw "ERROR: Unable to allocate buffer";
        }
    }
    /**********************************************
     * VECTOR : NON-DEFAULT CONSTRUCTOR
     * Preallocate the vector to "capacity"
     **********************************************/
    template <class T>
    vector <T> :: vector(int num)
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
     * VECTOR : clear
     * clears the contents of the vector
     *******************************************/
    template <class T>
    void vector <T> :: clear()
    {
        numElements = 0;
    }
    
    template <class T>
    void vector <T> :: deleteItem(int index)
    {
        if (index <  numElements)
        {
            for (int i = index; i < numElements; i++)
            {
                data[i] = data[i + 1];
            }
            numElements--;
        }
    }
    
    /********************************************
     * VECTOR : push_back
     * Adds data to the end of the vector
     *******************************************/
    template <class T>
    void vector <T> :: push_back(const T & t)
    {
        if(numCapacity == 0 || numElements + 1 > numCapacity)
        {
            resize(numCapacity);
        }
        
        data[numElements++] = t;
    }
    
    /********************************************
     * VECTOR : resize
     * Resizes the vector to twice the capacity
     *******************************************/
    template <class T>
    void vector <T> :: resize(int cap)
    {
        if (cap == 0)
            numCapacity = 1;
        else
            numCapacity = cap * 2;
        T * temp = new T[numCapacity];
        temp = data;
        
        data = new T[numCapacity];
        
        for (int i = 0; i < numElements ; i++)
            data[i] = temp[i];
        
        delete [] temp;
        //   temp = NULL;
    }
    /********************************************
     * VECTOR : DISPLAY
     * A debug utility to display the contents of the vector
     *******************************************/
    template <class T>
    void vector <T> :: display() const
    {
#ifndef NDEBUG
        std::cerr << "vector<T>::display()\n";
        std::cerr << "\tnum = " << numElements << "\n";
        for (int i = 0; i < numElements; i++)
            std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
    }
    
    
    }; // namespace custom

#endif // VECTOR_H

