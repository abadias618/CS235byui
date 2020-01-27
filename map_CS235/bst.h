/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother <your instructor name here>, CS 235
 * Author:
 *    Abdias Baldiviezo & Kevin Hisel
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H

namespace custom
{
/**************************************************
* CLASS BST
* Contains a binary search tree template class
* nested in the BST there is the BNode class
* and an iterator for the tree
*************************************************/
template <class T>
class BST
{
public:
	BST();
	BST(const BST& rhs);
	~BST();
	BST& operator =(const BST& rhs);
	void clear();
	bool empty();
	int size();
	//base interfaces
	void insert(const T& t);
	//iterator
	class iterator;
	iterator begin();
	iterator end();
	iterator find(const T& t);
	void erase(iterator& it);
	//reverse_iterator
	class reverse_iterator;
	iterator rbegin();
	iterator rend();
	/**************************************************
	* CLASS BNODE
	* Has the notion of a node adapted to form part 
	* of a BST
	*************************************************/
	class BNode
	{
	public:
		T data;
		BNode* pLeft;
		BNode* pRight;
		BNode* pParent;
		bool isRed;

		// default constructor
		BNode()
		{
			data = T();
			pRight = NULL;
			pLeft = NULL;
			pParent = NULL;
			isRed = true;
		};
		//non-default constructor
		BNode(const T& t)
		{
			data = t;
			pRight = NULL;
			pLeft = NULL;
			pParent = NULL;
			isRed = true;
		};
		//copy constructor
		BNode(const BNode& rhs)
		{
			data = rhs.data;
			pRight = rhs.pRight;
			pLeft = rhs.pLeft;
			pParent = rhs.pParent;
			isRed = rhs.isRed;
		};
		//assignment operator
		BNode& operator = (const BNode& rhs)
		{
			data = rhs.data;
			pRight = rhs.pRight;
			pLeft = rhs.pLeft;
			pParent = rhs.pParent;
			isRed = rhs.isRed;
			return *this;
		};
		/*bool verifyRB();
		bool verifyBST();*/
		/**************************************************
		* BNode :: BALANCE
		* Balances the red & black tree
		*************************************************/
		void balance(BNode* pNode)
		{
			//do necessary the necessary rotations for the B/R tree
			//case 1 it's the root
			if (!pNode->pParent && !pNode->pLeft && !pNode->pRight)
			{
				pNode->isRed = false;
				return;
			}
			//case 3 parent and aunt are red, grandparent is black
			if (pNode->pParent && pNode->pParent->isRed
				&& pAunt(pNode) && pAunt(pNode)->isRed
				&& !pGranny(pNode)->isRed)
			{
				//if the grand grandfather is red
				if (pGranny(pNode)->pParent && pGranny(pNode)->pParent->isRed)
				{
					pNode->isRed = false;
				}
				//if the grand grandfather is black
				else if (pGranny(pNode)->pParent && !pGranny(pNode)->pParent->isRed)
				{
					pGranny(pNode)->isRed = true;
					pNode->pParent->isRed = false;
					pAunt(pNode)->isRed = false;
				}
				//case its the root
				else
				{
					pGranny(pNode)->isRed = false;
					pNode->pParent->isRed = false;
					pAunt(pNode)->isRed = false;
				}
				return;
			}
			//case 2 parent is not black
			if (pNode->pParent && pNode->pParent->isRed)
			{
				//make it black
				pNode->pParent->isRed = false;
				//if it has an aunt also make it black
				if (pAunt(pNode) && pAunt(pNode)->isRed)
				{
					pAunt(pNode)->isRed = false;
				}
				
			}

			//case 4 parent is red aunt is black or non existent 
			//case a
		
			if (pNode->pParent && pNode->pParent->isRed 
				&& pGranny(pNode) && !pGranny(pNode)->isRed 
				&& pSibling(pNode) && !pSibling(pNode)->isRed 
				&& pAunt(pNode) && !pAunt(pNode)->isRed
				&& pNode->pParent->pLeft == pNode && pGranny(pNode)->pLeft == pNode->pParent)
			{
				pNode->addRight(pNode->pParent, pGranny(pNode));
				pGranny(pNode)->addLeft(pGranny(pNode),pSibling(pNode));
				pGranny(pNode)->isRed = true;
				pNode->pParent->isRed = false;
			}
			else if (pNode->pParent && pNode->pParent->pLeft == pNode 
				&& pGranny(pNode) && pGranny(pNode)->pLeft == pNode->pParent 
				&& !pNode->pParent->pRight && pGranny(pNode)->pParent)
			{
				///rotate clockwise
				pNode->pParent->pRight = pGranny(pNode);
				if (pGranny(pNode)->pParent->pLeft == pGranny(pNode))
				{
					pGranny(pNode)->addLeft(pGranny(pNode)->pParent, pNode->pParent);
					
				}
				else if (pGranny(pNode)->pParent->pRight == pGranny(pNode))
				{
					pGranny(pNode)->addRight(pGranny(pNode)->pParent, pNode->pParent);
				}
				pNode->pParent->pRight->pParent = pNode->pParent;
				pNode->pParent->pRight->pLeft = NULL;

				//color respectively
				pNode->pParent->isRed = false;
				pNode->pParent->pRight->isRed = true;
				pNode->isRed = true;
				
			}
			//case b
			if (pNode->pParent && pNode->pParent->isRed 
				&& pGranny(pNode) && !pGranny(pNode)->isRed
				&& pSibling(pNode) && !pSibling(pNode)->isRed 
				&& pAunt(pNode) && !pAunt(pNode)->isRed
				&& pNode->pParent->pRight == pNode && pGranny(pNode)->pRight == pNode->pParent)
			{
				pNode->addLeft(pNode->pParent, pGranny(pNode));
				pGranny(pNode)->addRight(pGranny(pNode),pSibling(pNode));
				pGranny(pNode)->isRed = true;
				pNode->pParent->isRed = false;
			}
			else if (pNode->pParent && pNode->pParent->pRight == pNode
				&& pGranny(pNode) && pGranny(pNode)->pRight == pNode->pParent
				&& !pNode->pParent->pLeft && pGranny(pNode)->pParent)
			{
				///rotate counter-clockwise
				pNode->pParent->pLeft = pGranny(pNode);
				if (pGranny(pNode)->pParent->pLeft == pGranny(pNode))
				{
					pGranny(pNode)->addLeft(pGranny(pNode)->pParent, pNode->pParent);

				}
				else if (pGranny(pNode)->pParent->pRight == pGranny(pNode))
				{
					pGranny(pNode)->addRight(pGranny(pNode)->pParent, pNode->pParent);
				}
				pNode->pParent->pLeft->pParent = pNode->pParent;
				pNode->pParent->pLeft->pRight = NULL;
				//color respectively
				pNode->pParent->isRed = false;
				pNode->pParent->pLeft->isRed = true;
				pNode->isRed = true;

			}
			//case c
			if (pNode->pParent && pNode->pParent->isRed
				&& pGranny(pNode) && !pGranny(pNode)->isRed
				&& pSibling(pNode) && !pSibling(pNode)->isRed 
				&& pAunt(pNode) && !pAunt(pNode)->isRed
				&& pNode->pParent->pRight == pNode && pGranny(pNode)->pLeft == pNode->pParent)
			{
				pGranny(pNode)->pLeft = pNode->pRight;
				pNode->pParent->pRight = pNode->pLeft;
				if (pGranny(pNode)->pParent == NULL)
				{
					pNode->pParent = NULL;
				}
				else if (pGranny(pNode)->pParent->pLeft == pGranny(pNode))
				{
					pGranny(pNode)->pParent->pLeft = pNode;
				}
				else
				{
					pGranny(pNode)->pParent->pRight = pNode;
				}
				pNode->pRight = pGranny(pNode);
				pNode->pLeft = pNode->pParent;
				pGranny(pNode)->isRed = true;
				pNode->isRed = false;
			}
			else if (pNode->pParent && pNode->pParent->pRight == pNode
				&& pGranny(pNode) && pGranny(pNode)->pLeft == pNode->pParent
				&& !pNode->pParent->pLeft && pGranny(pNode)->pParent)
			{
				///rotate counter-clockwise
				pNode->pLeft = pNode->pParent;
				pNode->pRight = pGranny(pNode);
				if (pGranny(pNode)->pParent->pLeft == pGranny(pNode))
				{
					pGranny(pNode)->addLeft(pGranny(pNode)->pParent, pNode);

				}
				else if (pGranny(pNode)->pParent->pRight == pGranny(pNode))
				{
					pGranny(pNode)->addRight(pGranny(pNode)->pParent, pNode);
				}
				pNode->pLeft->pParent = pNode;
				pNode->pRight->pParent = pNode;
				pNode->pRight->pLeft = NULL;
				pNode->pLeft->pRight = NULL;
				//color respectively
				pNode->isRed = false;
				pNode->pLeft->isRed = true;
				pNode->pRight->isRed = true;

			}
			//case d
			if (pNode->pParent && pNode->pParent->isRed 
				&& pGranny(pNode) && !pGranny(pNode)->isRed
				&& pSibling(pNode) && !pSibling(pNode)->isRed 
				&& pAunt(pNode) && !pAunt(pNode)->isRed
				&& pNode->pParent->pLeft == pNode && pGranny(pNode)->pRight == pNode->pParent)
			{
				pGranny(pNode)->pRight = pNode->pLeft;
				pNode->pParent->pLeft = pNode->pRight;
				if (pGranny(pNode)->pParent == NULL)
				{
					pNode->pParent = NULL;
				}
				else if (pGranny(pNode)->pParent->pRight == pGranny(pNode))
				{
					pGranny(pNode)->pParent->pRight = pNode;
				}
				else
				{
					pGranny(pNode)->pParent->pLeft = pNode;
				}
				pNode->pLeft = pGranny(pNode);
				pNode->pRight = pNode->pParent;
				pGranny(pNode)->isRed = true;
				pNode->isRed = false;
			}
			else if (pNode->pParent && pNode->pParent->pLeft == pNode
				&& pGranny(pNode) && pGranny(pNode)->pRight == pNode->pParent
				&& !pNode->pParent->pRight && pGranny(pNode)->pParent)
			{
				///rotate counter-clockwise
				pNode->pRight = pNode->pParent;
				pNode->pLeft = pGranny(pNode);
				if (pGranny(pNode)->pParent->pLeft == pGranny(pNode))
				{
					pGranny(pNode)->addLeft(pGranny(pNode)->pParent, pNode);

				}
				else if (pGranny(pNode)->pParent->pRight == pGranny(pNode))
				{
					pGranny(pNode)->addRight(pGranny(pNode)->pParent, pNode);
				}
				pNode->pRight->pParent = pNode;
				pNode->pLeft->pParent = pNode;
				pNode->pRight->pLeft = NULL;
				pNode->pLeft->pRight = NULL;
				//color respectively
				pNode->isRed = false;
				pNode->pLeft->isRed = true;
				pNode->pRight->isRed = true;

			}
		}
		/**************************************************
		* ADDLEFT
		* PARAM: takes a reference node and a node to add as a left child
		*************************************************/
		void addLeft(BNode* pNode, BNode* pAdd)
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
		void addRight(BNode* pNode, BNode* pAdd)
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
		* pSibling
		* returns the sibling of a node
		*************************************************/
		BNode* pSibling(BNode* pNode) 
		{
			if (!pNode->pParent)
			{
				return NULL;
			}
			if (pNode->pParent->pLeft==pNode)
			{
				return pNode->pParent->pRight;
			}
			else if (pNode->pParent->pRight == pNode)
			{
				return pNode->pParent->pLeft;
			}
		}
		/**************************************************
		* pAunt
		* returns the aunt of a node
		*************************************************/
		BNode* pAunt(BNode* pNode)
		{
			if (!pNode->pParent || !pNode->pParent->pParent)
			{
				return NULL;
			}
			if (pNode->pParent == pNode->pParent->pParent->pLeft)
			{
				return pNode->pParent->pParent->pRight;
			}
			else if (pNode->pParent == pNode->pParent->pParent->pRight)
			{
				return pNode->pParent->pParent->pLeft;
			}
		}
		/**************************************************
		* pGranny
		* returns the grandparent of a node
		*************************************************/
		BNode* pGranny(BNode* pNode)
		{
			if (!pNode->pParent->pParent)
			{
				return NULL;
			}
			else
			{
				return pNode->pParent->pParent;
			}
		}
	};
	//access root
	BNode* getRoot();
private:
	BNode* root;
	int numElements;
	void deleteNode(BNode* & pNode);
	void deleteBinaryTree(BNode* & pNode);
	static BNode* copyBinaryTree(BNode* pSrc);
	int sizeRecursive(BNode* pRoot);
	
};
template <class T>
typename BST<T>::BNode* BST<T>::getRoot()
{
	return root;
}

/**************************************************
 * BST ITERATOR
 * An iterator through the BST
 *************************************************/
template <class T>
class BST <T> ::iterator
{
public:
	// constructors, destructors, and assignment operator
	iterator() : p(NULL) {};
	iterator(BNode* p) : p(p) {
	};
	iterator(const iterator& rhs) {
		if (NULL != rhs.p)
		{
			//p = copyBinaryTree(rhs.p);
			p = rhs.p;
		}
		else
		{
			//if the iterator is null just set everything to null
			p = NULL;
		}

	}
	iterator& operator = (const iterator& rhs)
	{
		if (rhs.p != NULL)
		{
			//p = copyBinaryTree(rhs.p);
			p = rhs.p;
		}
		else
		{
			p = NULL;
		}


		return *this;
	}
	// friend function to access p
	//friend iterator list<T>::insert(const iterator& it, const T& t);
	//also erase access' p
	//friend iterator list<T>::erase(const iterator& it);

	// equals, not equals operator
	bool operator != (const iterator& rhs) const
	{
		if (NULL != rhs.p)
		{
			return p->data != rhs.p->data;
		}
		else
		{
			return p != NULL;
		}

	}
	bool operator == (const iterator& rhs) const
	{
		if (NULL != rhs.p)
		{
			return p->data == rhs.p->data;
		}
		else
		{
			return p == NULL;
		}
	}

	// dereference operator
	//only return constant
	T& operator * () { return p->data; }
	const T& operator * () const { return p->data; }

	// prefix increment
	iterator& operator ++ ()
	{
		// do nothing if we have nothing
		if (NULL == p)
			return *this;

		// if there is a right node, take it
		if (NULL != p->pRight)
		{
			// go right
			p = p->pRight;

			// jig left - there might be more left-most children
			while (p->pLeft)
				p = p->pLeft;
			return *this;
		}

		// there are no right children, the left are done
		assert(NULL == p->pRight);
		BNode* pSave = p;

		// go up
		p = p->pParent;

		// if the parent is the NULL, we are done!
		if (NULL == p)
			return *this;

		// if we are the left-child, got to the parent.
		if (pSave == p->pLeft)
			return *this;

		// we are the right-child, go up as long as we are the right child!
		while (NULL != p && pSave == p->pRight)
		{
			pSave = p;
			p = p->pParent;
		}

		return *this;
	}

	// postfix increment
	iterator operator ++ (int postfix)
	{
		BNode* tmp = p;
		// do nothing if we have nothing
		if (NULL == p)
			return iterator(tmp);

		// if there is a right node, take it
		if (NULL != p->pRight)
		{
			// go right
			p = p->pRight;

			// jig left - there might be more left-most children
			while (p->pLeft)
				p = p->pLeft;
			return iterator(tmp);
		}

		// there are no right children, the left are done
		assert(NULL == p->pRight);
		BNode* pSave = p;

		// go up
		p = p->pParent;

		// if the parent is the NULL, we are done!
		if (NULL == p)
			return iterator(tmp);

		// if we are the left-child, got to the parent.
		if (pSave == p->pLeft)
			return iterator(tmp);

		// we are the right-child, go up as long as we are the right child!
		while (NULL != p && pSave == p->pRight)
		{
			pSave = p;
			p = p->pParent;
		}


		return iterator(tmp);
	}

	// prefix decrement
	iterator& operator -- ()
	{
		// do nothing if we have nothing
		if (NULL == p)
			return *this;

		// if there is a left node, take it
		if (NULL != p->pLeft)
		{
			// go left
			p = p->pLeft;

			// jig right - there might be more right-most children
			while (p->pRight)
				p = p->pRight;
			return *this;
		}

		// there are no left children, the right are done
		assert(NULL == p->pLeft);
		BNode* pSave = p;

		// go up
		p = p->pParent;

		// if the parent is the NULL, we are done!
		if (NULL == p)
			return *this;

		// if we are the right-child, got to the parent.
		if (pSave == p->pRight)
			return *this;

		// we are the left-child, go up as long as we are the left child!
		while (NULL != p && pSave == p->pLeft)
		{
			pSave = p;
			p = p->pParent;
		}

		return *this;
	}
	// postfix decrement
	iterator operator -- (int prefix)
	{
		BNode* tmp=prefix;
		// do nothing if we have nothing
		if (NULL == p)
			return iterator(tmp);

		// if there is a left node, take it
		if (NULL != p->pLeft)
		{
			// go left
			p = p->pLeft;

			// jig right - there might be more right-most children
			while (p->pRight)
				p = p->pRight;
			return iterator(tmp);
		}

		// there are no left children, the right are done
		assert(NULL == p->pLeft);
		BNode* pSave = p;

		// go up
		p = p->pParent;

		// if the parent is the NULL, we are done!
		if (NULL == p)
			return iterator(tmp);

		// if we are the right-child, got to the parent.
		if (pSave == p->pRight)
			return iterator(tmp);

		// we are the left-child, go up as long as we are the left child!
		while (NULL != p && pSave == p->pLeft)
		{
			pSave = p;
			p = p->pParent;
		}
		return iterator(tmp);
	}
	friend void BST<T> ::erase(BST<T> ::iterator& it);
	friend void BST<T>::insert(const T& t);

private:
	BNode* p;
};
//


/**************************************************
 * BST ITERATOR :: begin
 *     returns the first element in the tree 
 * 
 *************************************************/
template <class T>
typename BST<T> :: iterator  BST<T> :: begin()
{
	BNode* i = root;
	if (i)
	{
		while (i->pLeft != NULL)
		{
			i = i->pLeft;
		}
	}
	
	return iterator(i);
}
/**************************************************
 * BST ITERATOR :: end
 *     returns a null iterator
 *
 *************************************************/
template <class T>
typename BST<T> ::iterator  BST<T> ::end()
{
	return iterator(NULL);
}
/**************************************************
 * BST ITERATOR :: rbegin
 *     returns the first element in the tree
 *
 *************************************************/
template <class T>
typename BST<T> ::iterator  BST<T> ::rbegin()
{
	BNode* i = root;
	if (i)
	{
		while (i->pRight != NULL)
		{
			i = i->pRight;
		}
	}
	
	return iterator(i);
	
}
/**************************************************
 * BST ITERATOR :: rend
 *     returns a null iterator
 *
 *************************************************/
template <class T>
typename BST<T> ::iterator  BST<T> ::rend()
{
	return iterator(NULL);	
}


/**************************************************
 * BST :: default constructor
 *     
 * creates an empty tree 
 *************************************************/
template <class T>
BST<T>::BST()
{
	root = NULL;
	numElements = 0;
}
/**************************************************
 * BST :: copy constructor
 *
 * creates a tree out of a parameter tree
 *************************************************/
template <class T>
BST<T>::BST(const BST<T>& rhs)
{
	root = copyBinaryTree(rhs.root);
	numElements = rhs.numElements;
}
/**************************************************
 * BST :: destructor
 *
 * deletes the tree
 *************************************************/
template <class T>
BST<T>::~BST()
{
	deleteBinaryTree(root);
}
/**************************************************
 * BST :: assignment operator
 *
 * copies the tree into a new variable
 *************************************************/
template <class T>
BST<T> & BST<T>::operator=(const BST<T> & rhs)
{
	root = copyBinaryTree(rhs.root);
	numElements = rhs.numElements;
	return *this;
}
/**************************************************
 * BST :: size
 *
 * RETURN: size of the BST
 *************************************************/
template <class T>
int BST<T>::size() 
{
	return sizeRecursive(root);
}
/**************************************************
 * BST :: clear
 *
 * deletes all the nodes in the tree
 *************************************************/
template <class T>
void BST<T>::clear()
{
	deleteBinaryTree(root);
	numElements = 0;
}
/**************************************************
 * BST :: empty
 *
 * RETURN: true if empty
 *************************************************/
template <class T>
bool BST<T>::empty()
{
	return size() == 0;
}
/**************************************************
 * BST :: insert
 * PARAM: takes a "t" value to insert
 * 
 *************************************************/
template <class T>
void BST<T>::insert(const T & t)
{
	//encapsulate the value into a Bnode
	BNode* pNode= new BNode(t);
	BNode* key = new BNode();
	//if its the root
	if (size()==0)
	{
		root = pNode;
		numElements++;
		pNode->balance(pNode);
		return;
	}
	//search where to insert the node
	for (iterator it = begin(); it != end(); ++it)
	{
		if (*it<pNode->data)
		{
			key = it.p;
			continue;
		}
		else if (*it>pNode->data)
		{
			key = it.p;
			break;
		}
		//TODO case if equals to the last element
		else if (*it == pNode->data)
		{
			key = ++it.p;
			break;
		}
	}
	
	//case 1 if the element was bigger tha all the nodes
	if (key->data < pNode->data)
	{
		//insert at the end & furthest right
		key->addRight(key, pNode);
	}
	else
	{
		//insert to the left of the key
		if (!key->pLeft && !key->pRight)
		{
			key->addLeft(key, pNode);
		}
		//insert to the right of the left element of the key
		else if (key->pLeft && key->pLeft->pRight)
		{

			key = key->pLeft;
			while (key->pRight)
			{
				key = key->pRight;
			}
			pNode->addRight(key, pNode);
			
		}
		else if (key->pLeft && !key->pLeft->pRight)
		{
			pNode->addRight(key->pLeft, pNode);
		}
		else if (!key->pLeft)
		{
			pNode->addLeft(key,pNode);
		}
	}
	numElements++;
	pNode->balance(pNode);


}
/**************************************************
 * BST ::ITERATOR :: find
 * PARAM: takes a "t" value to find
 * RETURN: returns the iterator to the value found
 *************************************************/
template <class T>
typename BST<T> :: iterator BST<T> ::find(const T& t)
{
	for (iterator it = begin(); it != end(); ++it)
	{
		if (*it==t)
		{
			return it;
		}
	}
	return end();
}
/**************************************************
 * BST ::ITERATOR :: erase
 * PARAM: takes a iterator to erase
 *************************************************/
template <class T>
void BST<T> :: erase(BST<T> :: iterator& it)
{
	//case 1 no children
	if (!it.p->pRight && !it.p->pLeft)
	{
		if (it.p->pParent && it.p->pParent->pRight == it.p)
		{
			it.p->pParent->pRight = NULL;
		}
		else if (it.p->pParent  && it.p->pParent->pLeft == it.p)
		{
			it.p->pParent->pLeft = NULL;
		}
		delete it.p;
		return;
	}
	//case 2 one child
	//see if its missing the right child
	if (!it.p->pRight  && it.p->pLeft )
	{
		it.p->pLeft->pParent = it.p->pParent;
		if (it.p->pParent && it.p->pParent->pRight == it.p)
		{
			it.p->pParent->pRight = it.p->pLeft;
		}
		if (it.p->pParent && it.p->pParent->pLeft == it.p)
		{
			it.p->pParent->pLeft = it.p->pLeft;
		}
		delete it.p;
		return;
	}
	//see if its missing the left child
	else if (!it.p->pLeft && it.p->pRight)
	{
		it.p->pRight->pParent = it.p->pParent;
		if (it.p->pParent && it.p->pParent->pRight == it.p)
		{
			it.p->pParent->pRight = it.p->pRight;
		}
		if (it.p->pParent && it.p->pParent->pLeft == it.p)
		{
			it.p->pParent->pLeft = it.p->pRight;
		}
		delete it.p;
		return;
	}
	//case 3 two children, no grandchildren
	//if its not the root
	if (it.p->pParent && it.p->pLeft && !it.p->pLeft->pLeft && !it.p->pLeft->pRight 
		&& it.p->pRight && !it.p->pRight->pLeft && !it.p->pRight->pRight)
	{
		//point the left node to the right node as parent
		it.p->pLeft->pParent = it.p->pRight;
		//point the right node to the parent of it
		it.p->pRight->pParent = it.p->pParent;
		//point the parent of it the right node either to the left or right of it
		if (it.p->pParent->pLeft == it.p)
		{
			it.p->pParent->pLeft = it.p->pRight;
		}
		else
		{
			it.p->pParent->pRight = it.p->pRight;
		}
		//point the right to the left as a left child
		it.p->pRight->pLeft = it.p->pLeft;
		
		delete it.p;
		return;
	}
	// if its the root and has NO grandchildren
	else if (!it.p->pParent && it.p->pLeft && !it.p->pLeft->pLeft && !it.p->pLeft->pRight
		&& it.p->pRight && !it.p->pRight->pLeft && !it.p->pRight->pRight)
	{
		//point the left node to the right node as parent
		it.p->pLeft->pParent = it.p->pRight;
		//point the right node to the parent of it
		it.p->pRight->pParent = NULL;
		//point the right to the left as a left child
		it.p->pRight->pLeft = it.p->pLeft;
		root = it.p->pRight;
		delete it.p;
		return;
	}
	// if its not the root and has grandchildren the left but not on the right
	else if (it.p->pParent && it.p->pLeft && it.p->pRight
		&& (it.p->pLeft->pLeft || it.p->pLeft->pRight) 
		&& !it.p->pRight->pLeft)
	{
		//point the parent to the the new node
		it.p->pLeft->pParent = it.p->pRight;
		//point the parent of it the right node either to the left or right of it
		if (it.p->pParent->pLeft == it.p)
		{
			it.p->pParent->pLeft = it.p->pRight;
		}
		else
		{
			it.p->pParent->pRight = it.p->pRight;
		}
		//point new node to its realtives
		it.p->pRight->pLeft = it.p->pLeft;
		it.p->pRight->pParent = it.p->pParent;
		delete it.p;
		return;
	}
	// if its not the root and has grandchildren on the right but not on the left
	else if (it.p->pParent && it.p->pRight && it.p->pLeft
		&& (it.p->pRight->pLeft || it.p->pRight->pRight)
		&& !it.p->pLeft->pRight)
	{
		//point the parent to the the new node
		it.p->pRight->pParent = it.p->pLeft;
		//point the parent of it the right node either to the left or right of it
		if (it.p->pParent->pLeft == it.p)
		{
			it.p->pParent->pLeft = it.p->pLeft;
		}
		else
		{
			it.p->pParent->pRight = it.p->pLeft;
		}
		//point new node to its realtives
		it.p->pLeft->pRight = it.p->pRight;
		it.p->pLeft->pParent = it.p->pParent;
		delete it.p;
		return;
	}
	//case 4 if it has grandchildren
	else if (/*it.p->pRight->pLeft && */it.p->pRight->pLeft->pRight 
		&& !it.p->pRight->pLeft->pLeft)
	{
		//special case if its the root
		if (!it.p->pParent)
		{
			//point the left child to it.p->pRight->pLeft
			it.p->pLeft->pParent = it.p->pRight->pLeft;
			//point the right child to it.p->pRight->pLeft
			it.p->pRight->pParent = it.p->pRight->pLeft;
			//point it.p->pRight->pLeft right child to its new parent
			it.p->pRight->pLeft->pRight->pParent = it.p->pRight;
			//point it.p->pRight->pLeft to the new parent and left child
			it.p->pRight->pLeft->pLeft = it.p->pLeft;
			it.p->pRight->pLeft->pParent = NULL;
			it.p->pRight->pLeft = it.p->pRight->pLeft->pRight;
			it.p->pLeft->pParent->pRight = it.p->pRight;

			root = it.p->pLeft->pParent;
			delete it.p;
			return;
		}

		//check if its the left or right child of the parent
		if (it.p->pParent->pLeft == it.p)
		{
			it.p->pParent->pLeft = it.p->pRight->pLeft;
		}
		else if (it.p->pParent->pRight == it.p)
		{
			it.p->pParent->pRight = it.p->pRight->pLeft;
		}
		//point the left child to it.p->pRight->pLeft
		it.p->pLeft->pParent = it.p->pRight->pLeft;
		//point the right child to it.p->pRight->pLeft
		it.p->pRight->pParent = it.p->pRight->pLeft;
		//point it.p->pRight->pLeft right child to its new parent
		it.p->pRight->pLeft->pRight->pParent = it.p->pRight;
		//point it.p->pRight->pLeft to the new parent and left child
		it.p->pRight->pLeft->pLeft = it.p->pLeft;
		it.p->pRight->pLeft->pParent = it.p->pParent;
		it.p->pRight->pLeft = it.p->pRight->pLeft->pRight;
		it.p->pLeft->pParent->pRight = it.p->pRight;


		delete it.p;
		return;
		
		
	}
	else if (it.p->pRight->pLeft )
	{
		BNode* i = it.p->pRight;
		while (i->pLeft != NULL)
		{
			i = i->pLeft;
		}
		//special case if its the root and i has no children
		if (!it.p->pParent && !i->pRight)
		{
			//point realatives to new node
			it.p->pLeft->pParent = i;
			it.p->pRight->pParent = i;
			//point i's parent to null
			i->pParent->pLeft = NULL;
			//point the new node in place to its relatives
			i->pParent = NULL;
			i->pLeft = it.p->pLeft;
			i->pRight = it.p->pRight;

			root = i;
			delete it.p;
			return;
		}
		//if its the root and i has a right child
		else if (!it.p->pParent && i->pRight)
		{
			//point realatives to new node
			it.p->pLeft->pParent = i;
			it.p->pRight->pParent = i;
			//point i's parent to the right child of i
			i->pParent->pLeft = i->pRight;
			i->pRight->pParent = i->pParent;
			//point the new node in place to its relatives
			i->pParent = NULL;
			i->pLeft = it.p->pLeft;
			i->pRight = it.p->pRight;

			root = i;
			delete it.p;
			return;
		}
		//
		
		//check if its the left or right child of the parent
		if (it.p->pParent->pLeft == it.p)
		{
			it.p->pParent->pLeft = i;
		}
		else if (it.p->pParent->pRight == it.p)
		{
			it.p->pParent->pRight = i;
		}
		//point realatives to new node
		it.p->pLeft->pParent = i;
		it.p->pRight->pParent = i;
		//point i's parent to null
		i->pParent->pLeft = NULL;
		//point the new node in place to its relatives
		i->pParent = it.p->pParent;
		i->pLeft = it.p->pLeft;
		i->pRight = it.p->pRight;
		delete it.p;
		return;
	}

}
   

/**************************************************
 * BST :: delete node
 * PARAM: takes a pointer to a BNode by reference
 *************************************************/
template <class T>
void BST<T>::deleteNode(BNode* & pNode)
{
	iterator it = find(pNode);
	erase(it);

}
/**************************************************
 * BST :: delete tree
 * PARAM: takes a pointer to a BNode by reference
 *************************************************/
template <class T>
void BST<T>::deleteBinaryTree(BNode* & pNode)
{
	if (!pNode)
	{
		return;
	}

	deleteBinaryTree(pNode->pLeft);
	deleteBinaryTree(pNode->pRight);
	delete pNode;
	pNode = NULL;

}
/**************************************************
 * BST :: copy Binary Tree
 * PARAM: takes a pointer to a BNode
 * RETURN: returns a pointer to the root of the new tree
 *************************************************/
template <class T>
typename BST<T>::BNode* BST<T>::copyBinaryTree(BNode* pSrc)
{
	if (pSrc == NULL)
	{
		return pSrc;
	}
	BNode* destination = new BNode(pSrc->data);
	destination->pLeft = copyBinaryTree(pSrc->pLeft);

	if (destination->pLeft != NULL)
	{
		destination->pLeft->pParent = destination;
	}
	destination->pRight = copyBinaryTree(pSrc->pRight);
	if (destination->pRight != NULL)
	{
		destination->pRight->pParent = destination;
	}
	return destination;

}
/**************************************************
 * BST :: sizeRecursive
 *
 * RETURN: size of the BST
 *************************************************/
template <class T>
int BST<T>::sizeRecursive(BNode* pRoot)
{
	if (!pRoot)
	{
		return 0;
	}
	else
	{
		return sizeRecursive(pRoot->pLeft) + 1 + sizeRecursive(pRoot->pRight);
	}
}

} // namespace custom

#endif // BST_H
