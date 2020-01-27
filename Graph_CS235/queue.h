#ifndef QUEUE_H
#define QUEUE_H

namespace custom 
{
template <class T>
class queue
{
public:
	//default constructor
	queue();
	//non- default constructor
	queue(int numCapacity);
	//copy constructor
	queue(const queue& rhs);
	//destructor
	~queue();
	//assignment operator
	queue& operator = (queue& rhs);
	//size
	int size();
	//clear
	void clear();
	//empty
	bool empty();
	//push
	void push(T t);
	//pop
	void pop();
	//front
	T & front();
	//back
	T & back();

private:
	//dinamically allocated array
	T* array;
	//to wrap the queue
	int numPush;
	//to wrap the queue
	int numPop;

	int numCapacity;
	//resize the dinamically allocated array
	void resize(int numCapacity);
	// returns the index of the head 
	int iHead();
	// returns the index of the tail 
	int iTail();

};

/*****************************
* QUEUE ::DEFAULT CONSTRUCTOR

******************************/
template <class T>
queue <T> ::queue()
{
	numCapacity = 0;
	numPush = 0;
	numPop = 0;
	array = NULL;

}
/******************************
QUEUE ::NON-DEFAULT CONSTRUCTOR
*******************************/
template <class T>
queue <T> ::queue(int numCapacity)
{
	this->numCapacity = 0;
	if (numCapacity>0)
	{
		//attempt to allocate
		try
		{
			array = new T[numCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for queue";
		}
		numPush = 0;
		numPop = 0;
		this->numCapacity = numCapacity;
	}
	else
	{
		this->numCapacity = 0;
		numPush = 0;
		numPop = 0;
		array = NULL;
	}
	
	
}
/***********************
QUEUE ::COPY CONSTRUCTOR
************************/
template <class T>
queue <T> ::queue(const queue <T>& rhs)
{
	if (rhs.numCapacity == 0) {
		numCapacity = 0;
		numPop = 0;
		numPush = 0;
		array = NULL;
		return;
	}
	//attempt to allocate
	try
	{
		array = new T[rhs.numCapacity];
		numCapacity = rhs.numCapacity;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a new buffer for queue";
	}
	//copy the data fields

	numPush = 0;
	numPop = 0;
	
	
	for (int i = rhs.numPop; i < rhs.numPush; i++)
	{
		push(rhs.array[i % rhs.numCapacity]);
	}
	
}
/*****************
QUEUE ::DESTRUCTOR
******************/
template <class T>
queue <T> ::~queue() 
{ 
	delete[] array; 
}

/**************************
QUEUE ::ASSIGNMENT OPERATOR
***************************/
template <class T>
queue <T> & queue <T> :: operator = (queue <T> & rhs)
{
	if (numCapacity < rhs.size()) {
		resize(rhs.size());
	}
	
	numPush = 0;
	numPop = 0;
	numCapacity = 0;
	for (int i = rhs.numPop; i < rhs.numPush; i++)
	{
		push(rhs.array[i % rhs.numCapacity]);
	}
	
	return *this;
}
/***********
QUEUE ::SIZE
************/
template <class T>
int queue <T> ::size ()
{
	return numPush - numPop;
}
/************
QUEUE ::CLEAR
*************/
template <class T>
void queue <T> ::clear()
{
	numCapacity = 0;
	numPush = 0;
	numPop = 0;
	
}
/************
QUEUE ::EMPTY
*************/
template <class T>
bool queue <T> ::empty() {
	if (size() == 0) 
	{ 
		return true; 
	}
	else
	{
		return false;
	}
}
/************
QUEUE ::PUSH
*************/
template <class T>
void queue <T> ::push(T t)
{
	if (size() == numCapacity)
	{
		resize(numCapacity * 2);
	}
	numPush++;
	array[iTail()] = t;
	
}
/************
QUEUE ::POP
*************/
template <class T>
void queue <T> ::pop()
{
	if (!empty())
	{
		numPop++;
	}
}
/************
QUEUE ::FRONT
*************/
template <class T>
T & queue <T> ::front()
{
	if (empty())
	{
		throw "ERROR: attempting to access an element in an empty queue";
	}
	else
	{
		return array[iHead()];
	}
}
/************
QUEUE ::BACK
*************/
template <class T>
T & queue <T> ::back()
{
	if (empty())
	{
		throw "ERROR: attempting to access an element in an empty queue";
	}
	else
	{
		return array[iTail()];
	}
}
/************
QUEUE ::iHEAD
*************/
template <class T>
int queue <T> ::iHead()
{
	return numPop % numCapacity;
}
/************
QUEUE ::iTAIL
*************/
template <class T>
int queue <T> ::iTail()
{
	return (numPush - 1) % numCapacity;

}
/*************
QUEUE ::RESIZE
**************/
template <class T>
void queue <T> ::resize(int numCapacity)
{
	if (numCapacity < 1)
	{
		// attempt to allocate
		try
		{
			T* temp = new T[1];
			int j = 0;
			for (int i = numPop; i < numPush; i++)
			{
				temp[j] = array[i % this->numCapacity];
				j++;
			}
			delete [] array;
			this->numCapacity = 1;
			this->numPop = 0;
			this->numPush = j;
			this->array = temp;
			
		}
		catch (std::bad_alloc)
		{
			throw ("ERROR: Unable to allocate a new buffer for queue resuze");
		}
	}
	else
	{
		// attempt to allocate
		try
		{
			T* temp = new T[numCapacity];
			int j = 0;
			for (int i = numPop; i < numPush; i++)
			{
				temp[j] = array[i % this->numCapacity];
				j++;
			}
			delete[] array;
			this->numCapacity = numCapacity;
			this->numPop = 0;
			this->numPush = j;
			this->array = temp;
		}
		catch (std::bad_alloc)
		{
			throw ("ERROR: Unable to allocate a new buffer for queue resize");
		}

	}
	
}

};//namespace custom

#endif // QUEUE_H
