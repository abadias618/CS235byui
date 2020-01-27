/***********************************************************************
 * Module:
 *    Week 11, Sort Bubble
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

/*****************************************************
 * SORT BUBBLE
 * Perform the bubble sort
 * created my own version
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{
	bool swaping;
	do {
		swaping = false;
		for (int i = 0; i < num - 1; i++) {
			T var1 = array[i];
			T transition;
			if (var1 > array[i + 1] && i < num) {
				transition = var1;
				array[i] = array[i + 1];
				array[i + 1] = transition;
				swaping = true;
			}
			else continue;
		}
	} while (swaping == true);
}

#endif // SORT_BUBBLE_H
