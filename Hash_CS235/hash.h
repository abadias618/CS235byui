/***********************************************************************
* Program:
*    Hash
* Author:
*    Abdias Baldiviezo
*	 Josh Spendlove
* Summary:
*    Will contain the class definition for the template Hash class,
*    will also contain classes for hashing different data types
*    
************************************************************************/
#ifndef HASH_H
#define HASH_H
/*****************************************
 * CLASS HASH
 * will contain the notion oh a hash ADT 
 * with an array as a container
 ****************************************/
template <class T>
class Hash
{
public:
	//constructors
	Hash(int numBuckets);
	Hash(const Hash & rhs);
	Hash& operator = (const Hash & rhs);
	~Hash();
	//interfaces
	void clear();
	int size()const;
	int capacity()const;
	bool empty()const;
	//access
	bool find(const T & t);
	void insert(const T & t);
	//doesn't do anything
	int hash(T& t) = 0;

private:
	//container
	T table[*];
	int numElements;
	int numBuckets;
};
/*****************************************
 * HASH :: non-default constructor
 * initiates the data fields
 ****************************************/
template <class T>
Hash<T>::Hash(int numBuckets)
{
	this->numBuckets = numBuckets;
	this->numElements = 0;
	this->table = new list[numBuckets];
}
/*****************************************
 * HASH :: copy constructor
 * initiates the hash copying everything from another hash
 ****************************************/
template <class T>
Hash<T>& Hash<T>::operator=(const Hash<T> & rhs)
{

}
/*****************************************
 * HASH :: copy constructor
 * initiates the hash copying everything from another hash
 ****************************************/
template <class T>
Hash<T>::Hash(const Hash<T>& rhs)
{

}
/*****************************************
* HASH :: destructor
* deletes the hash
****************************************/
template <class T>
Hash<T>::~Hash()
{
}
/*****************************************
* HASH :: clear
* All the elements added through the insert() 
* are removed and size() will return 0
****************************************/
template <class T>
void Hash<T>::clear()
{
	
}
/*****************************************
* HASH :: size
* Returns the number of elements in the Hash
****************************************/
template <class T>
int Hash<T>::size()const
{
	return;
}
/*****************************************
* HASH :: capacity
* Returns the number of buckets in the Hash.
****************************************/
template <class T>
int Hash<T>::capacity()const
{
	return;
}
/*****************************************
* HASH :: empty
* Determines whether the current Hash is empty
****************************************/
template <class T>
bool Hash<T>::empty()const
{
	return;
}
/*****************************************
* HASH :: find
* PARAM: The parameter is the value to be found. 
* RETURN: true if the value is found, false otherwise.
****************************************/
template <class T>
bool Hash<T>::find(const T & t)
{
	return;
}
/*****************************************
* HASH :: insert
* Places a new instance of a value in the Hash.
* PARAM:  The parameter is the elements to be inserted
****************************************/
template <class T>
void Hash<T>::insert(const T & t)
{
	return;
}
/*****************************************
* HASH :: hash
* This is a pure virtual function  and 
* PARAM:  taking an element as a parameter
* RETURN: returning an index into the underlying array.
****************************************/
template <class T>
int Hash<T>::hash(T & t)
{
	return;
}
/*****************************************
* CLASS I HASH
* A simple hash of integers
****************************************/
class IHash :public Hash<int>
{
public:
	IHash(int numBuckets) : Hash<int>(numBuckets) {};
	IHash(const IHash& rhs) : Hash <int>(rhs) {};
	// hash function for integers is simply to take the modulous    
	int hash(const int & value) const    
	{       
		int index = abs(value) % capacity();       
		assert(index >= 0 && index < capacity());       
		return index;    
	} 
	~IHash();

private:

};
#endif // !HASH_H


