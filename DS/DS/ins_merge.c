#include <stdio.h>
#include <stdlib.h>

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r, int temp[]) {
    int i = l, j = m + 1, k = l;

    while (i <= m && j <= r) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];

    for (i = l; i <= r; i++)
        arr[i] = temp[i];
}

void mergeSortRec(int arr[], int l, int r, int temp[]) {
    if (l >= r) return;

    int m = (l + r) / 2;
    mergeSortRec(arr, l, m, temp);
    mergeSortRec(arr, m + 1, r, temp);
    merge(arr, l, m, r, temp);
}

void mergeSort(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    mergeSortRec(arr, 0, n - 1, temp);
    free(temp);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n, choice;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nChoose sorting algorithm:\n");
    printf("1. Insertion Sort\n");
    printf("2. Merge Sort\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        insertionSort(arr, n);
        printf("\nSorted using Insertion Sort:\n");
    }
    else if (choice == 2) {
        mergeSort(arr, n);
        printf("\nSorted using Merge Sort:\n");
    }
    else {
        printf("Invalid choice.\n");
        return 0;
    }

    printArray(arr, n);
    return 0;
}

