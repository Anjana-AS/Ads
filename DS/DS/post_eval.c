
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXTOKENS 1000
#define STACKSIZE 1000
#define LINEBUF 2000

typedef struct {
    double data[STACKSIZE];
    int top;
} DStack;

void init(DStack *s) { s->top = -1; }
int empty(DStack *s) { return s->top == -1; }
int push(DStack *s, double v) {
    if (s->top >= STACKSIZE - 1) return 0;
    s->data[++(s->top)] = v;
    return 1;
}
int pop(DStack *s, double *out) {
    if (empty(s)) return 0;
    *out = s->data[(s->top)--];
    return 1;
}

int isOperatorToken(const char *tok) {
    return (strlen(tok) == 1) && (tok[0] == '+' || tok[0] == '-' ||
                                  tok[0] == '*' || tok[0] == '/' || tok[0] == '^');
}

int main() {
    char line[LINEBUF];
    printf("Enter postfix expression (tokens separated by spaces):\n");
    if (!fgets(line, sizeof(line), stdin)) return 0;
    line[strcspn(line, "\n")] = '\0';

    char *tokens[MAXTOKENS];
    int tcount = 0;
    char *tok = strtok(line, " ");
    while (tok && tcount < MAXTOKENS) {
        tokens[tcount++] = tok;
        tok = strtok(NULL, " ");
    }

    DStack st;
    init(&st);
    for (int i = 0; i < tcount; ++i) {
        char *cur = tokens[i];

        char *endptr;
        double val = strtod(cur, &endptr);
        if (endptr != cur && *endptr == '\0') {
            if (!push(&st, val)) {
                fprintf(stderr, "Error: stack overflow\n");
                return 1;
            }
            continue;
        }

        if (isOperatorToken(cur)) {
            double b, a;
            if (!pop(&st, &b) || !pop(&st, &a)) {
                fprintf(stderr, "Error: insufficient operands for operator '%s'\n", cur);
                return 1;
            }
            double res = 0.0;
            char op = cur[0];
            switch (op) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/':
                    if (b == 0.0) {
                        fprintf(stderr, "Error: division by zero\n");
                        return 1;
                    }
                    res = a / b; break;
                case '^': res = pow(a, b); break;
                default:
                    fprintf(stderr, "Error: unsupported operator '%c'\n", op);
                    return 1;
            }
            if (!push(&st, res)) {
                fprintf(stderr, "Error: stack overflow\n");
                return 1;
            }
        } else {
            fprintf(stderr, "Error: invalid token '%s'\n", cur);
            return 1;
        }
    }

    double final;
    if (!pop(&st, &final)) {
        fprintf(stderr, "Error: empty expression or no result\n");
        return 1;
    }
    if (!empty(&st)) {
        fprintf(stderr, "Warning: extra operands left on stack (expression may be invalid)\n");
    }

    printf("Result = %.10g\n", final); 
    return 0;
}

