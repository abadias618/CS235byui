/***********************************************************************
 * Module:
 *    Week 11, Sort Insertion
 *    Brother Helfrich, CS 235
 * Author:
 *    Abdias Baldiviezo
 * Summary:
 *    This program will implement the Insertion Sort
 ************************************************************************/

#ifndef SORT_INSERTION_H
#define SORT_INSERTION_H

#include <cassert>
/*****************************************************
* BINARY SEARCH
* Returns the location of iInsert
****************************************************/
template <class T>
int binarySearch(T array[], T search, int iBegin, int iEnd)
{
	int iMiddle = (iBegin + iEnd) / 2;
	if (iBegin > iEnd)
	{
		return iBegin;
	}
	if (array[iMiddle] == search)
	{
		return iMiddle;
	}
	if (search > array[iMiddle])
	{
		return binarySearch(array, search, iMiddle + 1, iEnd);
	}
	else
	{
		return binarySearch(array, search, iBegin, iMiddle - 1);
	}
}
/*****************************************************
 * SORT INSERTION
 * Perform the insertion sort
 ****************************************************/
template <class T>
void sortInsertion(T array[], int num)
{
	//iterates n times where n=num
	for (int iPivot = num-1; iPivot >= 0; iPivot--)
	{
		T valuePivot = array[iPivot];
		int iInsert = binarySearch(array, valuePivot, iPivot + 1, num - 1);
		//to put it in the bounds of the array
		iInsert--;
		int iShift = iPivot;
		//iterates as until you reach insert
		for (iShift ;iShift < iInsert; iShift++)
		{
			//shift the needed elements left
			array[iShift] = array[iShift + 1];
		}
		array[iShift] = valuePivot;
	}
}

#endif // SORT_INSERTION_H
