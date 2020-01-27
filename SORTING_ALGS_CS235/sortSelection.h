/***********************************************************************
 * Module:
 *    Week 11, Sort Select
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Selection Sort
 ************************************************************************/

#ifndef SORT_SELECTION_H
#define SORT_SELECTION_H

/*****************************************************
 * SORT SELECTION
 * Perform the selection sort
 ****************************************************/
template <class T>
void sortSelection(T array[], int num)
{
	int j = 0;
	T transition;
	int index = 0;
	int c = 0;
	int counter;
	while (j < num - 1) {
		bool condition = false;
		for (int k = c; k < num; k++) {
			counter = 0;
			for (int i = c; i < num; i++) {
				if (array[k] < array[i] || array[k]== array[i]) { counter++; }
			}
			if (counter == num - j) {
				condition = true;
				index = k;
				break;
			}
		}

		if (condition == true) {
			transition = array[j];
			array[j] = array[index];
			array[index] = transition;
			c++;
		}
		j++;
	}
}


#endif // SORT_SELECTION_H
