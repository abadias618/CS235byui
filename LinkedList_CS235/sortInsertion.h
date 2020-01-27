/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Abdias Baldiviezo
 *	  Kevin Hisel
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"
/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 PARAM: T array[] (the array) , int num (the size of the array)
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{

	//copy everthing to a list
	Node<T>* listHead=new Node<T>(array[0]);
	Node<T>* listHeadCopy = listHead;
	for (int i = 1; i < num; i++)
	{
		listHead = insert(listHead, array[i], true);
	}
	//determine the key
	Node<T>* key = listHeadCopy->pNext;
	//to use the list
	Node<T>* head = listHeadCopy;
	Node<T>* prevKey = head;
	//sort the array of floats
	while (true)
	{

		while (prevKey != NULL && prevKey->data > key->data)
		{
			//switch data between key and prevKey
			T temp = key->data;
			key->data = prevKey->data;
			prevKey->data = temp;
			//move to the previous element
			key = prevKey;
			prevKey = prevKey->pPrev;
		}
		prevKey = key;
		key = key->pNext;
		if (key == NULL)
		{
			//when we reach the end of the list with the key
			//we exit the loop
			break;
		}

	}

	//copy everything back to the array
	
	int arrayindex = 0;
	for (/*head of the list*/ head; head != NULL; head = head->pNext)
	{
		array[arrayindex] = head->data;
		arrayindex++;
	}
}


#endif // INSERTION_SORT_H

