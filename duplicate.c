#include <stdio.h>

// Function to perform binary search
int binarySearch(int arr[], int low, int high, int key, int *positions, int *posIndex) {
    if (high >= low) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key) {
            positions[(*posIndex)++] = mid;
            return mid;
        }
        if (arr[mid] > key)
            return binarySearch(arr, low, mid - 1, key, positions, posIndex);
        return binarySearch(arr, mid + 1, high, key, positions, posIndex);
    }
    return -1;
}

// Function to find duplicate elements and their positions
void findDuplicates(int arr[], int n) {
    int positions[n]; // Array to store positions of duplicates
    int posIndex = 0; // Index to track positions array

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            int key = arr[i];
            binarySearch(arr, 0, n - 1, key, positions, &posIndex);
        }
    }

    if (posIndex > 0) {
        printf("Duplicate elements found at positions: ");
        for (int i = 0; i < posIndex; i++) {
            printf("%d ", positions[i]);
        }
        printf("\n");
    } else {
        printf("No duplicate elements found.\n");
    }
}

int main() {
    int arr[] = {1, 2, 2, 3, 4, 4, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    findDuplicates(arr, n);

    return 0;
}
