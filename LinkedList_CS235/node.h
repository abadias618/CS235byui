/***********************************************************************
 * Header:
 *    Node	
 * Summary:
 *    contains a node class
 *
 *    This will contain the class definition of:
 *       node             : an object with 1 data member and two pointers
 *    Also it will have some free functions	
 * Author:
 *    Abdias Baldiviezo
 *	  Kevin Hisel
 ************************************************************************/
#ifndef NODE_H
#define NODE_H
#include<iostream>

using namespace std;
	/************************************************
	* NODE
	* A class that holds an element and points
	* to the next and previous node
	***********************************************/
	template <class T>
	class Node
	{
	public:
		//default constructor
		Node();
		//non-default constructor
		Node(const T& t);
		//data element
		T data;
		//previous pointer
		Node* pPrev;
		//next pointer
		Node* pNext;
	};// class node
	/********************************************
		* NODE :: default constructor
	********************************************/
	template <class T>
	Node<T> ::Node()
	{
		data = NULL;
		pPrev = NULL;
		pNext = NULL;
	};
	/********************************************
		* NODE :: non-default constructor
	********************************************/
	template <class T>
	Node<T> ::Node(const T& t)
	{
		data = t;
		pPrev = NULL;
		pNext = NULL;
	};

	/********************************************
	*  free functions
	********************************************/
	/********************************************
	*  COPY: copies a linked list taking a node<T>
	*	as a param, returns a node<T>.
	********************************************/
	template <class T>
	Node<T>* copy(/*const*/ Node<T>* pSource)
	{
		if (pSource->pNext == NULL || pSource == NULL)
		{
			return pSource;
		}
		else
		{
			//save the head of the node to return
			Node<T>* pDestination = new Node<T>(pSource->data);
			Node<T>* pSrc = pSource;
			Node<T>* pDes = pDestination;
			//iterates through the first list until the next pHead is NULL
			for (pSrc; pSrc->pNext != NULL; pSrc = pSrc->pNext)
			{
				//inserts the elements unto the second list
				pDes = insert(pDes, pSrc->pNext->data, true);
			}
			return pDestination;
		}
		

		
	};
	/********************************************
	*  OPERATOR << : displays the ll iterating through it
	********************************************/

	template <class T>
	std::ostream &operator << (std::ostream& out, Node<T>* & pHead)
	{
		if (pHead != NULL)
		{
			//iterates through the list until the next p is NULL
			for (Node<T>* p = pHead; p != NULL; p = p->pNext)
			{
				if (p->pNext!=NULL)
				{
					std::cout << p->data << ", ";
				}
				else
				{
					std::cout << p->data;
				}
				
				
			}
			return out;
		}
		else
		{
			
			return out;
		}
		return out;
	};
	/********************************************
	*  INSERT: inserts a node to a linked-list
	*	takes reference node<T> parameter, T value,
	*	and bool put-it-next as parameters; returns
	*	a node<T>
	********************************************/
	template <class T>
	Node<T>* insert(Node<T>* pSource, const T& t, bool after = false)
	{
		//create new node
		Node<T>* pNew = new Node<T>(t);
		//check if it'll be inserted before, and ifit exists
		if (pSource != NULL && after == false)
		{
			//point new node to prev and next nodes
			pNew->pNext = pSource;
			pNew->pPrev = pSource->pPrev;
			//point prev and next nodes to the new node
			pSource->pPrev = pNew;
			if (pNew->pPrev != NULL)
			{
				pNew->pPrev->pNext = pNew;
			}
		}
		//check if it'll be inserted after, and if it exists
		else if (pSource != NULL && after == true)
		{
			//point new node to prev and next nodes
			pNew->pNext = pSource->pNext;
			pNew->pPrev = pSource;
			//point prev and next nodes to the new node
			pSource->pNext = pNew;
			if (pNew->pNext != NULL)
			{
				pNew->pNext->pPrev = pNew;
			}
		}

		return pNew;
	};
	/********************************************
	*  INSERT<string>: inserts a node<string> to a linked-list
	*	takes reference node<string>* parameter, string value,
	*	and bool put-it-next as parameters; returns
	*	a node<string>
	********************************************/
	template <class T>
	Node<string>* insert(Node<string>* pSource, const string& t, bool after = false)
	{
		//create new node
		Node<string>* pNew = new Node<string>(t);
		//check if it'll be inserted before, and ifit exists
		if (pSource != NULL && after == false)
		{
			//point new node to prev and next nodes
			pNew->pNext = pSource;
			pNew->pPrev = pSource->pPrev;
			//point prev and next nodes to the new node
			pSource->pPrev = pNew;
			if (pNew->pPrev != NULL)
			{
				pNew->pPrev->pNext = pNew;
			}
		}
		//check if it'll be inserted after, and if it exists
		else if (pSource != NULL && after == true)
		{
			//point new node to prev and next nodes
			pNew->pNext = pSource->pNext;
			pNew->pPrev = pSource;
			//point prev and next nodes to the new node
			pSource->pNext = pNew;
			if (pNew->pNext != NULL)
			{
				pNew->pNext->pPrev = pNew;
			}
		}

		return pNew;
	};
	/********************************************
	*  FIND: finds a node taking the node<T> pHead
	*	and the T&t value of the node as parameters;
	*	returns a node<T>
	********************************************/
	template <class T>
	Node<T>* find(Node<T>* pHead, const T& t)
	{
		if (pHead==NULL || pHead->pNext==NULL&&pHead->data==t)
		{
			return pHead;
		}
		else
		{
			//iterates through the list until the next pointer is NULL
			for (Node<T>* p = pHead; p != NULL; p = p->pNext)
			{
				//searches if the data is in the list
				if (p->data == t)
				{
					//if value is found
					return p;
				}
			}
		}
		
		//if value is not found
		return NULL;
	};
	/********************************************
	*  REMOVE: removes a given node<T> as a param
	*	from a list, returns a pointer to the previous
	*	node if it exists, otherwise it returns a pointer
	*	to the next node.
	********************************************/
	template <class T>
	Node<T>* remove(const Node<T>* pRemove)
	{
		if (pRemove == NULL)
		{
			return NULL;
		}
		else if (pRemove->pPrev != NULL)
		{
			pRemove->pPrev->pNext = pRemove->pNext;
		}
		else if (pRemove->pNext != NULL)
		{
			pRemove->pNext->pPrev = pRemove->pPrev;
		}

		//return either the prev or next node
		Node<T>* pReturn;
		if (pRemove->pPrev != NULL)
		{
			pReturn = pRemove->pPrev;
		}
		else
		{
			pReturn = pRemove->pNext;
		}
		delete pRemove;
		return pReturn;
	};
	/********************************************
	*  freeData: clears all the nodes in the ll,
	*	takes the head of the ll as a param
	********************************************/
	template <class T>
	void freeData(Node<T>*& pHead)
	{
		if (pHead != NULL)
		{
			//pull next
			Node<T>* pDelete = pHead;
			pHead = pHead->pNext;
			//delete
			remove(pDelete);
			//recursive call
			freeData(pHead);
		}
		return;
	};



#endif // !NODE_H
