/***********************************************************************
 * Module:
 *    Week 11, Sort Heap
 *    Brother Helfrich, CS 235
 * Author:
 *    Abdias Baldiviezo
 * Summary:
 *    This program will implement the Heap Sort
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H
/*****************************************************
* HEAP CLASS
* used to build a heap and facilitate its sorting
****************************************************/
template <class T>
class Heap
{
public:
	//constructor
	Heap(T array[], int num);
	/*T getMax();
	void deleteMax();*/
	void sort();
private:
	T * array;
	int num;
	void percolateDown(int index);
	void swap(int i1, int i2);
};
/*****************************************************
 * HEAP :: SWAP
 *swaps 2 numbers
 ****************************************************/
template <class T>
void Heap<T> :: swap(int i1, int i2)
{
	T temp = array[i1];
	array[i1] = array[i2];
	array[i2] = temp;
}
/*****************************************************
 * HEAP :: PERCOLATE DOWN
 * Perform the heap sort
 ****************************************************/
template <class T>
void Heap<T> :: percolateDown(int index)
{
	int indexLeft = index * 2;
	int indexRight = indexLeft + 1;
	//if its bigger than the sibling and the parent then swap
	if (indexRight <= num
		&& array[indexRight] > array[indexLeft]
		&& array[indexRight] > array[index])
	{
		swap(index, indexRight);
		percolateDown(indexRight);
	}
	//if its bigger than the sibling and the parent then swap
	else if (indexLeft <= num 
			&& array[indexLeft] > array[index])
	{
		swap(index, indexLeft);
		percolateDown(indexLeft);
	}
}
/*****************************************************
 * HEAP non-default constructor
 * 
 ****************************************************/
template <class T>
Heap<T> :: Heap(T array[], int num)
{
	this->array = array;
	//num-1 for the first iteration of the percolateDown
	this->num = num-1;
	for (int index = num/2 ; index >= 0 ; index--)
	{
		percolateDown(index);
	}
}
/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template <class T>
void Heap<T> :: sort()
{
	while (num>0)
	{
		swap(0,num);
		num--;
		percolateDown(0);
	}
}
/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template <class T>
void sortHeap(T array[], int num)
{
	Heap<T> h(array, num);
	h.sort();
}


#endif // SORT_HEAP_H
