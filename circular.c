

/*implemenatation of circular queue using array*/


#include <stdio.h>
#include <stdlib.h>

int *queue;
int front = -1, rear = -1;
int SIZE;  

int isFull() {
    return (rear + 1) % SIZE == front;
}

int isEmpty() {
    return front == -1;
}

void enqueue(int value) {
    if (isFull()) {
        printf("Circular Queue overflow ! Cannot insert\n");
    } else {
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        queue[rear] = value;
        printf("%d enqueued to circular queue\n", value);
    }
}

void dequeue() {
    if (isEmpty()) {
        printf("Circular Queue underflow\n");
    } else {
        printf("%d dequeued from circular queue\n", queue[front]);
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
    }
}

void display() {
    if (isEmpty()) {
        printf("Circular Queue is empty\n");
    } else {
        printf("Circular Queue elements: ");
        int i = front;
        while (1) {
            printf("%d ", queue[i]);
            if (i == rear)
                break;
            i = (i + 1) % SIZE;
        }
        printf("\n");
    }
}

int main() {
    int choice, value;

    printf("Enter the size of the circular queue: ");
    scanf("%d", &SIZE);

 
    queue = (int*) malloc(SIZE * sizeof(int));
    if (queue == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    while (1) {
        printf("\nCircular Queue Operations Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                free(queue);  
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

