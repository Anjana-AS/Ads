#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *front = NULL;
struct Node *rear = NULL;

struct Node* createNode(int value) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void enqueue(int value) {
    struct Node *newNode = createNode(value);

    if (rear == NULL) {      
        front = rear = newNode;
        printf("%d inserted into queue\n", value);
        return;
    }

    rear->next = newNode;    
    rear = newNode;          
    printf("%d inserted into queue\n", value);
}

void dequeue() {
    if (front == NULL) {
        printf("Queue underflow! (Queue is empty)\n");
        return;
    }

    struct Node *temp = front;
    printf("%d removed from queue\n", temp->data);

    front = front->next;

    if (front == NULL)       
        rear = NULL;         
    free(temp);
}

void peek() {
    if (front == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Front element = %d\n", front->data);
}

void display() {
    if (front == NULL) {
        printf("Queue is empty!\n");
        return;
    }

    struct Node *temp = front;
    printf("Queue elements (front to rear): ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    int choice, value;

    while (1) {
        printf("\n--- Queue Using Linked List ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek (Front Element)\n");
        printf("4. Display Queue\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                enqueue(value);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                peek();
                break;

            case 4:
                display();
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

