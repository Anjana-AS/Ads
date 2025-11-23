#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *head = NULL;


struct Node* createNode(int value) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}


void insertAtBeginning(int value) {
    struct Node *newNode = createNode(value);

    if (head == NULL) {
        head = newNode;
        newNode->next = head;   
        return;
    }

    struct Node *temp = head;
    while (temp->next != head)
        temp = temp->next;

    newNode->next = head;
    temp->next = newNode;
    head = newNode;
}


void insertAtEnd(int value) {
    struct Node *newNode = createNode(value);

    if (head == NULL) {
        head = newNode;
        newNode->next = head;
        return;
    }

    struct Node *temp = head;
    while (temp->next != head)
        temp = temp->next;

    temp->next = newNode;
    newNode->next = head;
}


void deleteBeginning() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    struct Node *temp = head;

    if (head->next == head) {  
        head = NULL;
        free(temp);
        return;
    }

    struct Node *last = head;
    while (last->next != head)
        last = last->next;

    head = head->next;
    last->next = head;
    free(temp);
}

void deleteEnd() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    struct Node *temp = head, *prev = NULL;

    if (head->next == head) {
        head = NULL;
        free(temp);
        return;
    }

    while (temp->next != head) {
        prev = temp;
        temp = temp->next;
    }

    prev->next = head;
    free(temp);
}

void display() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    struct Node *temp = head;
    printf("Circular Linked List: ");

    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("(back to head)\n");
}

int main() {
    int choice, value;

    while (1) {
        printf("\n--- Circular Linked List Menu ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Delete from Beginning\n");
        printf("4. Delete from End\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insertAtBeginning(value);
                break;

            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                insertAtEnd(value);
                break;

            case 3:
                deleteBeginning();
                break;

            case 4:
                deleteEnd();
                break;

            case 5:
                display();
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

