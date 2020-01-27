/***********************************************************************
 * Component:
 *    Assignment 12, Hash
 *    Brother Kirby, CS 235
 * Author:
 *    Josh Spendlove
 * Summary:
 *    Create a Template Hash Table
 ************************************************************************/

#ifndef HASH_H
#define HASH_H

#include "list.h"

namespace custom
{

	/**************************************************
	 *  HASH
	 * My implementation of the Hash class
	 *************************************************/
	template <class T>
	class Hash
	{
	public:
		Hash(const Hash& rhs);
		Hash(int);
		~Hash() { ; }
		Hash& operator = (const Hash& rhs);

		int size() { return numElements; }
		int capacity() const { return numBuckets; }
		bool empty() { return numElements == 0; }
		void clear();
		void erase(const T&);
		void insert(const T&);
		bool find(const T&);
		virtual int hash(const T&) const = 0;


	private:  // functions
		list<T>* table;
		int numElements;
		int numBuckets;

	};


	/**************************************************
	 *  Hash :: Hash
	 * Non-Default Constructor - Sets up the variables.
	 *************************************************/
	template <class T>
	Hash <T> ::Hash(int size)
	{
		numBuckets = size;
		numElements = 0;
		try
		{
			table = new list<T>[numBuckets];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate memory for the hash";
		}

	}

	/**************************************************
	 *  Hash :: Hash
	 * Copy Constructor - Copies the variables from
	 * one Hash to a new one.
	 *************************************************/
	template <class T>
	Hash <T> ::Hash(const Hash& rhs)
	{
		numBuckets = rhs.numBuckets;
		numElements = rhs.numElements;

		try
		{
			table = new list<T>[numBuckets];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate memory for the hash";
		}

		for (int i = 0; i < numBuckets; i++)
		{
			for (typename list<T> ::iterator it = rhs.table[i].begin(); it != rhs.table[i].end(); it++)
			{
				table[i].push_back(*it);
			}
		}
	}
	/**************************************************
	*  Hash :: ~Hash
	* Destructor: frees up space by deleting the table
	*************************************************/
	template <class T>
	Hash<T> ::~Hash() 
	{ 
		delete [] table; 
	}
	/**************************************************
	 *  Hash :: ASSIGNMENT OPERATOR
	 * Sets the variables of "this" equal to those of rhs.
	 *************************************************/
	template <class T>
	Hash <T>& Hash <T> :: operator = (const Hash& rhs)
	{
		numBuckets = rhs.numBuckets;
		numElements = rhs.numElements;

		try
		{
			table = new list<T>[numBuckets];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate memory for the hash";
		}

		for (int i = 0; i < numBuckets; i++)
		{
			for (typename list<T> ::iterator it = rhs.table[i].begin(); it != rhs.table[i].end(); it++)
			{
				table[i].push_back(*it);
			}
		}
		return *this;
	}


	/**************************************************
	 *  Hash :: INSERT
	 * Inserts a new node into the binary tree.
	 *************************************************/
	template <class T>
	void Hash <T> ::insert(const T& item)
	{
		int index = hash(item);
		table[index].push_back(item);
		numElements++;
	}


	/**************************************************
	 *  Hash :: CLEAR
	 * Clears the Hash table;
	 *************************************************/
	template <class T>
	void Hash <T> ::clear()
	{
		for (int i = 0; i < numBuckets; i++)
			table[i].clear();
		numElements = 0;
	}



	/**************************************************
	 *  Hash :: FIND
	 * Returns true if the Hash table contains
	 * the passed element.
	 *************************************************/
	template <class T>
	bool Hash <T> ::find(const T& item)
	{
		int index = hash(item);
		typename list<T> ::iterator it = table[index].find(item);
		if (it == NULL)
			return false;
		return true;
	}

	/**************************************************
	 *  Hash :: ERASE
	 * Erases an element from the Hash Table
	 * if it exists.
	 *************************************************/
	template <class T>
	void Hash <T> ::erase(const T& item)
	{
		int index = hash(item);
		typename list<T> ::iterator it = table[index].find(item);

		if (it != NULL)
		{
			table[index].erase(it);
			numElements--;
		}
	}


} // namespace custom

#endif // HASH_H
