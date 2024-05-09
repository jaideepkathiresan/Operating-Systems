/**
 * C program to search element in array
 */

#include <stdio.h>

#define MAX_SIZE 100  // Maximum array size

int main()
{
    int arr[MAX_SIZE];
    int size, i, toSearch, found;

    /* Input size of array */
    printf("Enter size of array: ");
    scanf("%d", &size);

    /* Input elements of array */
    printf("Enter elements in array: ");
    for(i=0; i<size; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("\nEnter element to search: ");
    scanf("%d", &toSearch);

    /* Assume that element does not exists in array */
    found = 0; 
    
    for(i=0; i<size; i++)
    {
        /* 
         * If element is found in array then raise found flag
         * and terminate from loop.
         */
        if(arr[i] == toSearch)
        {
            found = 1;
            break;
        }
    }

    /*
     * If element is not found in array
     */
    if(found == 1)
    {
        printf("\n%d is found at position %d", toSearch, i + 1);
    }
    else
    {
        printf("\n%d is not found in the array", toSearch);
    }

    return 0;
}
/*
// C Program to implement binary search using iteration
#include <stdio.h>

// A iterative binary search function. It returns location
// of x in given array arr[l..r] if present, otherwise -1
int binarySearch(int arr[], int l, int r, int x)
{
	// the loop will run till there are elements in the
	// subarray as l > r means that there are no elements to
	// consider in the given subarray
	while (l <= r) {

		// calculating mid point
		int m = l + (r - l) / 2;

		// Check if x is present at mid
		if (arr[m] == x) {
			return m;
		}

		// If x greater than ,, ignore left half
		if (arr[m] < x) {
			l = m + 1;
		}

		// If x is smaller than m, ignore right half
		else {
			r = m - 1;
		}
	}

	// if we reach here, then element was not present
	return -1;
}

// driver code
int main(void)
{
	// creating a sorted array
	int arr[] = { 2, 3, 4, 10, 40 };
	int size = sizeof(arr) / sizeof(arr[0]);
	// element to be searched
	int x = 24;

	// calling binary search
	int result = binarySearch(arr, 0, size - 1, x);

	if (result == -1) {
		printf("Element is not present in array");
	}
	else {
		printf("Element is present at index %d", result);
	}

	return 0;
}
*/