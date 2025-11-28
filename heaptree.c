

//implementation of heap tree operations

#include <stdio.h>

#define MAX 100

int heap[MAX];
int size = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void insert(int value) {
    heap[size] = value;
    int i = size;
    size++;

   
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}


int deleteMin() {
    if (size == 0) {
        printf("Heap is empty!\n");
        return -1;
    }

    int root = heap[0];
    heap[0] = heap[size - 1];
    size--;

 
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < size && heap[left] < heap[smallest])
            smallest = left;
        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return root;
}


void display() {
    if (size == 0) {
        printf("Heap is empty!\n");
        return;
    }

    printf("Heap elements: ");
    for (int i = 0; i < size; i++)
        printf("%d ", heap[i]);
    printf("\n");
}


int main() {
    int choice, value;

    while (1) {
        printf("\n--- MIN HEAP MENU ---\n");
        printf("1. Insert value\n");
        printf("2. Delete min\n");
        printf("3. Display heap\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(value);
                break;

            case 2:
                value = deleteMin();
                if (value != -1)
                    printf("Deleted min: %d\n", value);
                break;

            case 3:
                display();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}

