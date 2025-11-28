

/*implemenatation of sequential search and binary search*/


#include <stdio.h>


int seqsearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}


int binsearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}


void sortAscending(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, key, choice;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }


    sortAscending(arr, n);

    printf("\nArray sorted in ascending order:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("\nEnter element to search: ");
    scanf("%d", &key);

    printf("\nChoose search method:\n");
    printf("1. Sequential Search\n");
    printf("2. Binary Search\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int index = -1;

    if (choice == 1) {
        index = seqsearch(arr, n, key);
        if (index != -1)
            printf("Sequential Search: %d found at index %d\n", key, index);
        else
            printf("Sequential Search: %d not found\n", key);
    }
    else if (choice == 2) {
        index = binsearch(arr, n, key);
        if (index != -1)
            printf("Binary Search: %d found at index %d\n", key, index);
        else
            printf("Binary Search: %d not found\n", key);
    }
    else {
        printf("Invalid choice!\n");
    }

    return 0;
}

