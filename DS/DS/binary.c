#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* createTree() {
    int value;
    printf("Enter data (-1 for no node): ");
    scanf("%d", &value);

    if (value == -1) {
        return NULL;
    }

    struct Node* newNode = createNode(value);

    printf("Enter left child of %d:\n", value);
    newNode->left = createTree();

    printf("Enter right child of %d:\n", value);
    newNode->right = createTree();

    return newNode;
}

void preorder(struct Node* root) {
    if (root == NULL) return;

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct Node* root) {
    if (root == NULL) return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void postorder(struct Node* root) {
    if (root == NULL) return;

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main() {
    struct Node* root = NULL;

    printf("Create the binary tree:\n");
    root = createTree();

    printf("\nPreorder Traversal: ");
    preorder(root);

    printf("\nInorder Traversal : ");
    inorder(root);

    printf("\nPostorder Traversal: ");
    postorder(root);

    printf("\n");

    return 0;
}

