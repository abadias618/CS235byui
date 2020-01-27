/***********************************************************************
* Header:
*    BNode
* Summary:
*    contains nodes that will be structured as a binary tree
*    This will contain the class definition of:
*       bnode             : nodes that have left & right children, and a parent
* Author
*    Abdias Baldiviezo & Kevin Hisel
************************************************************************/

#ifndef BNODE_H
#define BNODE_H

template <class T>
class BNode
{
public:
	T data;
	BNode* pLeft;
	BNode* pRight;
	BNode* pParent;

	// default constructor
	BNode();
	//non-default constructor
	BNode(const T& t);
	//copy constructor
	BNode(const BNode& rhs);
	//assignment operator
	BNode& operator = (const BNode& rhs);
	//insertion operator
	//std::ostream& operator << (std::ostream& out, BNode* & rhs);
};
/**************************************************
* BNODE :: default constructor
* sets everthing to NULL
*************************************************/
template<class T>
BNode<T>::BNode()
{
	data = T();
	pRight = NULL;
	pLeft = NULL;
	pParent = NULL;

};
/**************************************************
	* BNODE :: non-default constructor
	* sets the data given to "t" and sets everthing to NULL
	*************************************************/
template <class T>
BNode<T>::BNode(const T& t)
{
	data = t;
	pRight = NULL;
	pLeft = NULL;
	pParent = NULL;
};
/**************************************************
* BNODE :: copy constructor
* copies all data fields into the new node
*************************************************/
template <class T>
BNode<T>::BNode(const BNode& rhs)
{
	data = rhs.data;
	pRight = rhs.pRight;
	pLeft = rhs.pLeft;
	pParent = rhs.pParent;
};
/**************************************************
* BNODE :: assignment operator
* copies data fields to the lhs node
*************************************************/
template <class T>
BNode<T>& BNode<T>::operator = (const BNode& rhs)
{

	data = rhs.data;
	pRight = rhs.pRight;
	pLeft = rhs.pLeft;
	pParent = rhs.pParent;
	return *this;
};
/**************************************************
* BNODE :: insertion operator
* displays the nodes
*************************************************/
template <class T>
std::ostream& operator << (std::ostream& out, BNode<T>* & rhs) 
{
	if (rhs == NULL)
	{
		return out;
	}
	
	operator<<(out,rhs->pLeft);
	std::cout << rhs->data << " ";
	operator<<(out,rhs->pRight);
	

	return out;
};
/********************************************
*  free functions
********************************************/
/**************************************************
* ADDLEFT
* PARAM: takes a reference node and a node to add as a left child
*************************************************/
template< class T>
void addLeft(BNode <T>* pNode, BNode <T>* pAdd)
{
	try
	{
		if (pAdd != NULL)
		{
			pAdd->pParent = pNode;
		}
		pNode->pLeft = pAdd;
	}
	catch (std::bad_alloc)
	{
		throw ("ERROR: Unable to allocate a node");
	}
	return;
};
/**************************************************
	* ADDRIGHT
	* PARAM: takes a reference node and a node to add as a right child
	*************************************************/
template< class T>
void addRight(BNode <T>* pNode, BNode <T>* pAdd)
{
	try
	{
		if (pAdd != NULL)
		{
			pAdd->pParent = pNode;
		}
		pNode->pRight = pAdd;
	}
	catch (std::bad_alloc)
	{
		throw ("ERROR: Unable to allocate a node");
	}
	return;
};
/**************************************************
* ADDLEFT(value)
* PARAM: takes a reference node and a value to add
*		  to a new node created as a left child
*************************************************/
template< class T>
void addLeft(BNode <T>* pNode, const T& t)
{
	try
	{
		BNode<T>* pAdd = new BNode<T>(t);
		pAdd->pParent = pNode;
		pNode->pLeft = pAdd;
	}
	catch (std::bad_alloc)
	{
		throw ("ERROR: Unable to allocate a node");
	}
	return;
	
};
/**************************************************
	* ADDRIGHT(value)
	* PARAM: takes a reference node and a value to add
	*		  to a new node created as a right child
	*************************************************/
template< class T>
void addRight(BNode <T>* pNode, const T& t)
{
	try
	{
		BNode<T>* pAdd = new BNode<T>(t);
		pAdd->pParent = pNode;
		pNode->pRight = pAdd;
	}
	catch (std::bad_alloc)
	{
		throw ("ERROR: Unable to allocate a node");
	}
	return;
	
};
/**************************************************
	* SIZEBTREE
	* PARAM: takes a reference node to behave as a root
	* RETURN: returns and integer representing the size
	*************************************************/
template<class T>
int sizeBTree(const BNode<T>* pRoot)
{
	if (pRoot == NULL)
	{
		return 0;
	}
	else
	{
		return sizeBTree(pRoot->pLeft) + 1 + sizeBTree(pRoot->pRight);
	}
};
/**************************************************
	* DELETEBTREE
	* PARAM: takes a reference node from which the deletion will happen
	*************************************************/
template<class T>
void deleteBTree(BNode <T> * & pNode)
{
	if (!pNode)
	{
		return;
	}
	
	deleteBTree(pNode->pLeft);
	deleteBTree(pNode->pRight);
	delete pNode;
	pNode = NULL;

	
};
/**************************************************
* COPYBTREE
* PARAM: takes a reference node to behave as a root and copy from there on
* RETURN: the new BNode representing the root
*************************************************/
template<class T>
BNode<T>* copyBTree(BNode <T>* pSrc)
{
	if (pSrc == NULL)
	{
		return pSrc;
	}
	BNode<T>* destination = new BNode<T>(pSrc->data);
	destination->pLeft = copyBTree(pSrc->pLeft);

	if (destination->pLeft != NULL)
	{
		destination->pLeft->pParent = destination;
	}
	destination->pRight = copyBTree(pSrc->pRight);
	if (destination->pRight != NULL)
	{
		destination->pRight->pParent = destination;
	}
	return destination;
};


#endif // !BNODE_H

