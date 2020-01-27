/***********************************************************************
 * Header:
 *    Deque
 * Summary:
 *    This class contains a template for the deque data structure
 *
 *    This will contain the class definition of:
 *       deque             : similar to std::deque
 * Author
 *    Abdias Baldiviezo
 *	  Kevin Hisel
 ************************************************************************/
#ifndef DEQUE_H
#define DEQUE_H
namespace custom 
{
/************************************************
* DEQUE
* A que that can be accessed by front and back
***********************************************/
	template <class T>
	class deque 
	{
	public:
		//constructors and destructors
		deque();
		deque(int numCapacity);
		deque(const deque & rhs);
		~deque() { delete[] array; }
		deque& operator = (const deque& rhs);
		//standard container interfaces
		int size() const;
		bool empty() const;
		void clear();
		void push_back(const T& t);
		void push_front(const T& t);
		void pop_back();
		void pop_front();
		T&  front();
		T&  back();
		const T& front()const;
		const T& back()const;
	private:
		T* array;
		int iFront;
		int iBack;
		int numCapacity;
		void resize(int numCapacity);
		int iFrontNormalize() const;
		int iBackNormalize() const;
		int normalize(int i) const;

	};
	/*******************************************************
	 * DEQUE :: normalize -function to normalize negative iFront or iBack
	 *******************************************************/
	template <class T>
	int deque<T> ::normalize(int i) const {
		if (i < 0)
		{
			while (i < 0)
			{
				i += numCapacity;
			}
			return i /*% numCapacity*/;
		}
		else if (i > numCapacity)
		{
			while (i > 0)
			{
				i -= numCapacity;
			}
			return i /*% numCapacity*/;
		}
		else if (i == 0)
		{
			return 0;
		}
		return i ;
		
	}
	/**************************************************
	 * DEQUE :: default constructor
	 *************************************************/
	template <class T>
	deque<T> ::deque() {
		array = NULL;
		numCapacity = 0;
		iFront = 0;
		iBack = -1;
	}
	/**************************************************
	 * DEQUE :: non-default constructor
	 *************************************************/
	template <class T>
	deque<T> ::deque(int numCapacity) {
		if (numCapacity <1) {
			iFront = 0;
			iBack = -1;
			this->numCapacity = 0;
			array = NULL;
		}
		else
		{
			// attempt to allocate
			try
			{
				array = new T[numCapacity];
			}
			catch (std::bad_alloc)
			{
				throw "ERROR: Unable to allocate a new buffer for deque";
			}
			this->numCapacity = numCapacity;
			iFront = 0;
			iBack = -1;
		}
		
	}
	/**************************************************
	 * DEQUE :: copy constructor
	 *************************************************/
	template <class T>
	deque<T> ::deque(const deque <T> & rhs) {
		if (rhs.numCapacity<1) {
			iFront = 0;
			iBack = -1;
			numCapacity = 0;
			array = NULL;
			return;
		}
		// attempt to allocate
		try
		{
			array = new T[rhs.numCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: unable to allocate a new buffer for deque";
		}
		
		
		////copy things over
		//for (int i = 0; i < rhs.size(); i++)
		//{
		//	//push_back(rhs.array[normalize(j)]);
		//	array[i] = rhs.array[i];
		//	//j++;
		//}
		//copy things over
		numCapacity = rhs.numCapacity;
		iFront = 0;
		iBack = -1;
		for (int i = rhs.iFront; i <= rhs.iBack; i++)
		{
			push_back(rhs.array[normalize(i)]);
		}
		
	}
	/**************************************************
	 * DEQUE :: assignment operator
	 *************************************************/
	template <class T>
	deque<T> & deque<T>::operator=(const deque<T>& rhs) {
		clear();
		if (numCapacity < rhs.size())
		{
			resize(rhs.size());
		}
		
		numCapacity = rhs.numCapacity;
		iFront = 0;
		iBack = -1;
		//copy things over
		for (int i = rhs.iFront; i <= rhs.iBack; i++)
		{	
			push_back(rhs.array[normalize(i)]);
		}

		//iFront = rhs.iFront;
		//iBack = rhs.iBack;
		//numCapacity = rhs.numCapacity;
		return *this;
	}
	/**************************************************
	 * DEQUE :: size
	 *************************************************/
	template <class T>
	int deque<T> ::size() const {
		return iBack - iFront + 1;
	}
	/**************************************************
	 * DEQUE :: clear
	 *************************************************/
	template <class T>
	void deque<T> ::clear()  {
		iFront = 0;
		iBack = -1;
	}
	/**************************************************
	 * DEQUE :: empty
	 *************************************************/
	template <class T>
	bool deque<T> ::empty() const{
		if (size()<1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	/**************************************************
	 * DEQUE :: push_back
	 *************************************************/
	template <class T>
	void deque<T> ::push_back(const T & t) {
		if (size()==numCapacity)
		{
			resize(numCapacity*2);
		}
		iBack++;
		array[iBackNormalize()]=t;
	}
	/**************************************************
	 * DEQUE :: push_front
	 *************************************************/
	template <class T>
	void deque<T> ::push_front(const T& t) {
		if (size() == numCapacity)
		{
			resize(numCapacity*2);
		}
		iFront--;
		array[iFrontNormalize()] = t;
	}
	/**************************************************
	 * DEQUE :: pop_front
	 *************************************************/
	template <class T>
	void deque<T> ::pop_front() {
		if (!empty())
		{
			iFront++;
		}
	}
	/**************************************************
	 * DEQUE :: pop_back
	 *************************************************/
	template <class T>
	void deque<T> ::pop_back() {
		if (!empty())
		{
			iBack--;
		}
	}
	/**************************************************
	 * DEQUE :: front(changeable)
	 *************************************************/
	template <class T>
	T&  deque<T> ::front() {
		if (empty())
		{
			throw "ERROR: unable to access data from an empty deque";
		}
		else
		{
			return  array[iFrontNormalize()];
		}
	}
	/**************************************************
	 * DEQUE :: back(changeable)
	 *************************************************/
	template <class T>
	T& deque<T> ::back() {
		if (empty())
		{
			throw "ERROR: unable to access data from an empty deque";
		}
		else
		{
			return array[iBackNormalize()];
		}
	}

	/**************************************************
	 * DEQUE :: front(unchangeable)
	 *************************************************/
	
	template <class T>
	const T & deque<T> ::front() const {
		if (empty())
		{
			throw "ERROR: unable to access data from an empty deque";
		}
		else
		{
			return array[iFrontNormalize()];
		}
	}
	/**************************************************
	 * DEQUE :: back (unchangeable)
	 *************************************************/
	template <class T>
	const T & deque<T> ::back() const{
		if (empty())
		{
			throw "ERROR: unable to access data from an empty deque";
		}
		else
		{
			return array[iBackNormalize()];
		}
	}
	/**************************************************
	 * DEQUE :: resize
	 *************************************************/
	template <class T>
	void deque<T> ::resize(int numCapacity) {
		if (numCapacity < 1)
		{
			// attempt to allocate
			try
			{
				T* temp = new T[numCapacity];
				int j = 0;
				delete[] array;
				this->numCapacity = 1;
				this->iFront = 0;
				this->iBack = j-1;
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
				//copy things over
				int k = 0;
				for (int i = iFront; i <= iBack; i++)
				{
					temp[k]=array[normalize(i)];
					k++;
				}
				delete[] array;
				this->numCapacity = numCapacity;
				this->iFront = 0;
				this->iBack = k-1;
				this->array = temp;
			}
			catch (std::bad_alloc)
			{
				throw ("ERROR: Unable to allocate a new buffer for queue resize");
			}
		}
	}

	/**************************************************
	 * DEQUE :: iFrontNormalize
	 *************************************************/
	template <class T>
	int deque<T> ::iFrontNormalize() const {
		return normalize(iFront);
	}
	/**************************************************
	 * DEQUE :: iBackNormalize
	 *************************************************/
	template <class T>
	int deque<T> ::iBackNormalize() const{
		return normalize(iBack);
	}
		
	
}

#endif // DEQUE_H
