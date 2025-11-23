#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000


typedef struct {
    char items[MAX];
    int top;
} CharStack;

void initStack(CharStack *s) { s->top = -1; }
int isEmpty(CharStack *s) { return s->top == -1; }
int isFull(CharStack *s) { return s->top == MAX-1; }
void push(CharStack *s, char c) { if (!isFull(s)) s->items[++(s->top)] = c; }
char pop(CharStack *s) { return isEmpty(s) ? '\0' : s->items[(s->top)--]; }
char peek(CharStack *s) { return isEmpty(s) ? '\0' : s->items[s->top]; }

int isOperator(char c) {
    return (c=='+' || c=='-' || c=='*' || c=='/' || c=='^');
}

int precedence(char op) {
    switch(op) {
        case '^': return 3;
        case '*': case '/': return 2;
        case '+': case '-': return 1;
        default: return 0;
    }
}


int isRightAssociative(char op) {
    if (op == '^') return 1;
    return 0;
}


void infixToPostfix(const char *infix, char *postfix) {
    CharStack st;
    initStack(&st);
    int i = 0, k = 0;
    int n = strlen(infix);

    while (i < n) {
        char ch = infix[i];


        if (isspace((unsigned char)ch)) { i++; continue; }


        if (isdigit((unsigned char)ch)) {
            while (i < n && isdigit((unsigned char)infix[i])) {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' '; 
            continue;
        }


        if (isalpha((unsigned char)ch)) {

            while (i < n && isalpha((unsigned char)infix[i])) {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';
            continue;
        }


        if (ch == '(') {
            push(&st, ch);
        }

        else if (ch == ')') {
            while (!isEmpty(&st) && peek(&st) != '(') {
                postfix[k++] = pop(&st);
                postfix[k++] = ' ';
            }
            if (!isEmpty(&st) && peek(&st) == '(') pop(&st); // discard '('
            else {

                fprintf(stderr, "Error: mismatched parentheses\n");
                postfix[0] = '\0';
                return;
            }
        }

        else if (isOperator(ch)) {
            while (!isEmpty(&st) && isOperator(peek(&st))) {
                char topOp = peek(&st);
                int precTop = precedence(topOp);
                int precCurr = precedence(ch);

                if ( (precTop > precCurr) ||
                     (precTop == precCurr && !isRightAssociative(ch)) ) {

                    postfix[k++] = pop(&st);
                    postfix[k++] = ' ';
                } else break;
            }
            push(&st, ch);
        } else {

            fprintf(stderr, "Warning: ignoring unknown character '%c'\n", ch);
        }

        i++;
    }


    while (!isEmpty(&st)) {
        char t = pop(&st);
        if (t == '(' || t == ')') {
            fprintf(stderr, "Error: mismatched parentheses\n");
            postfix[0] = '\0';
            return;
        }
        postfix[k++] = t;
        postfix[k++] = ' ';
    }

    if (k > 0 && postfix[k-1] == ' ') k--; // remove trailing space
    postfix[k] = '\0';
}

int main() {
    char infix[1000];
    char postfix[2000];

    printf("Enter an infix expression:\n");
    if (!fgets(infix, sizeof(infix), stdin)) return 0;

    infix[strcspn(infix, "\n")] = '\0';

    infixToPostfix(infix, postfix);

    if (postfix[0] != '\0') {
        printf("Postfix expression:\n%s\n", postfix);
    } else {
        printf("Conversion failed due to error.\n");
    }

    return 0;
}

