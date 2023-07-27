/*
 * @lc app=leetcode id=15 lang=c
 *
 * [15] 3Sum
 */

// @lc code=start

/**
 * Return copy the array to a new array
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int * copyArray(int * ar, int items) {
	int * newAr = malloc(sizeof(int) * items);
	if(newAr != NULL) {
		for(int i=0;i<items;i++) {
			newAr[i] = ar[i];
		}
	}

	return newAr;
}


void printTriplet(int * ar) {
	printf("[%d,%d,%d] ", ar[0],ar[1],ar[2]);
}


void printList(int ** list, int size) {
	printf("size %d [ ", size);
	for(int i=0;i<size;i++) {
		printTriplet(list[i]);
	}
	printf("]\n");
}


bool tripletInList(int * ar, int ** list, int listSize) {
    if(ar && list) {
		for(int i=0;i<listSize;i++) {
			int * test = list[i];

			if(ar[0] == test[0] && ar[1] == test[1] && ar[2] == test[2]) {
				return true;
			}
		}

		return false;
	}

	return false;
}

// Add a triplet to the list without assuming that the old list has been
// allocated with malloc. Responsibility rests with caller
int ** addToNewList(int * ar, int ** list, int listSize) {
	int ** newList = malloc(sizeof(int*) * (listSize + 1));
	if(newList == NULL) {
		printf("Memory allocation failure\n");
		return NULL;
	}

	if(listSize > 0) {
		// Copy the items into the new list
		for(int i=0;i<listSize;i++) {
			newList[i] = list[i];
		}
	}

	// Add in the new array
	newList[listSize] = ar;

	return newList;
}

// Would use bubble sort

/*
procedure bubbleSort(A : list of sortable items)
    n := length(A)
    repeat
        swapped := false
        for i := 1 to n-1 inclusive do
            -- if this pair is out of order
            if A[i-1] > A[i] then
                -- swap them and remember something changed
                swap(A[i-1], A[i])
                swapped := true
            end if
        end for
    until not swapped
end procedure
*/
void sortTriplet(int * ar) {
	bool end=false;
	while(!end) {
		bool swapped=false;
		for(int i=1;i<3;i++) {
			if(ar[i-1] > ar[i]) {
				int tmp = ar[i];
				ar[i] = ar[i-1];
				ar[i-1] = tmp;
				swapped=true;
			}
		}

		if(!swapped) {
			end=true;
		}
	}
}

bool bigger(int * one, int * two, int idx) {
	if(one[idx] > two[idx]) {
		return true;
	}

	return false;
}


void sortTripletList(int ** list, int listSize) {
	bool end=false;
	while(!end) {
		bool swapped=false;
		for(int i=1;i<listSize;i++) {
			if(bigger(list[i-1], list[i], 0)) {
				int * tmp = list[i];
				list[i] = list[i-1];
				list[i-1] = tmp;
				swapped=true;
			}
		}

		if(!swapped) {
			end=true;
		}
	}

	end=false;
	int cur=0;
	int idx=1;
	int stop=listSize;
	while(!end) {
		bool swapped=false;
		int * ar = list[cur];
		int v = ar[idx];
		for(int i=1;i<stop;i++) {
			if(v == list[i-1][idx] && bigger(list[i-1], list[i], 0)) {
				int * tmp = list[i];
				list[i] = list[i-1];
				list[i-1] = tmp;
				swapped=true;
			}
			else if(v != list[i-1][idx]) {
				stop=i;
			}
		}

		if(!swapped) {
			idx++;

			if(idx==3) {
				end=true;
			}
		}
	}
}


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
	// int newLen = ((numsSize) / 3)  + (numsSize % 3 ? 1: 0);
	int ** found = malloc(sizeof(int*) * numsSize);
	printf("New size [len %d]\n", numsSize);
	if(found == NULL) {
		printf("Memory allocation failure\n");
		abort();
	}

	int max = numsSize;
	int foundLen = 0;
	int count=-1;

	// For each integer find two more integers that sum to zero.
	for(int i=0;i<numsSize;i++) {
		for(int j=0;j<numsSize;j++) {
			for(int k=0;k<numsSize;k++) {
				if(i != j && i != k && j != k && nums[i] + nums[j] + nums[k] == 0) {
					count++;
				}
			}
		}
	}



	for(int i=0;i<numsSize;i++) {
		for(int j=0;j<numsSize;j++) {
			for(int k=0;k<numsSize;k++) {
				if(i != j && i != k && j != k && nums[i] + nums[j] + nums[k] == 0)
				{
					int * ar = malloc(sizeof(int) * 3);
					if(ar == NULL) {
						printf("Memory allocation failure\n");
						abort();
					}

					ar[0] = nums[i];
					ar[1] = nums[j];
					ar[2] = nums[k];

					sortTriplet(ar);

					if(! tripletInList(ar,found,foundLen)) {
						if(foundLen + 1 >= max) {
							int ** newFound = addToNewList(ar,found,foundLen);
							if(newFound == NULL) {
								printf("Memory allocation failure\n");
								abort();
							}

							if(found) {
								free(found);
							}

							found = newFound;
							max = foundLen+1;
						}
						else {
							found[foundLen] = ar;
						}
						foundLen++;
						// printList(found,foundLen);

					}
				}
			}
		}
	}

	sortTripletList(found, foundLen);

	*returnSize = foundLen;

	if(foundLen) {
		int * cols = malloc(sizeof(int) * foundLen);
		if(cols == NULL) {
			printf("Memory allocation failure\n");
			abort();
		}

		for(int i=0;i<foundLen;i++) {
			cols[i] = 3;
		}

		*returnColumnSizes = cols;
	}


	// free(work);
	return found;
}

