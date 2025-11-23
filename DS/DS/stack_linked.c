#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *top = NULL;   // top of stack

struct Node* createNode(int value) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void push(int value) {
    struct Node *newNode = createNode(value);
    newNode->next = top;   // new node points to previous top
    top = newNode;         // update top
    printf("%d pushed to stack\n", value);
}

void pop() {
    if (top == NULL) {
        printf("Stack underflow! (Stack is empty)\n");
        return;
    }
    struct Node *temp = top;
    printf("%d popped from stack\n", temp->data);
    top = top->next;
    free(temp);
}

void peek() {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Top element = %d\n", top->data);
}

void display() {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return;
    }
    struct Node *temp = top;
    printf("Stack elements (top to bottom): ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    int choice, value;

    while (1) {
        printf("\n--- Stack Using Linked List ---\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek (Top Element)\n");
        printf("4. Display Stack\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(value);
                break;

            case 2:
                pop();
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

