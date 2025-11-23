#include <stdio.h>

int arr[100];
int n;

void display()
{
    int i;
    if (n == 0) {
        printf("Heap is empty\n");
        return;
    }
    for (i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }
}

void insert(int num, int loc)
{
    int par;
    while (loc > 0) {
        par = (loc - 1) / 2;
        if (num <= arr[par]) {
            arr[loc] = num;
            return;
        }
        arr[loc] = arr[par];
        loc = par;
    }
    arr[0] = num;
}

void del(int num)
{
    int i, left, right, temp;
    
    for (i = 0; i < n; i++) {
        if (arr[i] == num)
            break;
    }
    if (i == n) {
        printf("Element %d not found in heap\n", num);
        return;
    }

    
    arr[i] = arr[n - 1];
    n = n - 1;

    if (i > 0) {
        int par = (i - 1) / 2;
        if (arr[i] > arr[par]) {
            int cur = i;
            int val = arr[cur];
            while (cur > 0) {
                par = (cur - 1) / 2;
                if (val <= arr[par]) break;
                arr[cur] = arr[par];
                cur = par;
            }
            arr[cur] = val;
            return;
        }
    }

    left = 2 * i + 1;
    right = 2 * i + 2;
    while (left < n) {
        int larger = left;
        if (right < n && arr[right] > arr[left])
            larger = right;

        if (arr[i] >= arr[larger])
            return;

        temp = arr[i];
      arr[i] = arr[larger];
        arr[larger] = temp;

        i = larger;
        left = 2 * i + 1;
        right = 2 * i + 2;
    }
}

int main()
{
    int choice, num;
    n = 0;
    while (1) {
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            /* invalid input, clear and continue */
            while (getchar() != '\n');
            printf("Invalid input\n");
            continue;
        }
        switch (choice) {
            case 1:
                printf("Enter the number to be inserted: ");
                if (scanf("%d", &num) != 1) { while (getchar() != '\n'); printf("Invalid input\n"); break; }
                if (n >= 100) {
                    printf("Heap full\n");
                    break;
                }
                insert(num, n);
                n = n + 1;
                break;
            case 2:
                printf("Enter number to be deleted: ");
                if (scanf("%d", &num) != 1) { while (getchar() != '\n'); printf("Invalid input\n"); break; }
                del(num);
                break;
            case 3:
                display();
                break;
            case 4:
                return 0;
            default:
                printf("Wrong choice\n");
        }
    }
    return 0;
}

