
//graph and graph traversals

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct AdjNode {
    int dest;
    struct AdjNode *next;
} AdjNode;

typedef struct Graph {
    int V;          
    bool directed;  
    AdjNode **head; 
} Graph;

AdjNode* newAdjNode(int dest) {
    AdjNode *node = (AdjNode*)malloc(sizeof(AdjNode));
    node->dest = dest;
    node->next = NULL;
    return node;
}

Graph* createGraph(int V, bool directed) {
    Graph *g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    g->directed = directed;
    g->head = (AdjNode**)malloc(V * sizeof(AdjNode*));
    for (int i = 0; i < V; ++i) g->head[i] = NULL;
    return g;
}

void addEdge(Graph *g, int src, int dest) {
    AdjNode *node = newAdjNode(dest);
    node->next = g->head[src];
    g->head[src] = node;


    if (!g->directed) {
        AdjNode *node2 = newAdjNode(src);
        node2->next = g->head[dest];
        g->head[dest] = node2;
    }
}


void printGraph(Graph *g) {
    printf("Graph adjacency lists:\n");
    for (int v = 0; v < g->V; ++v) {
        printf("%d:", v);
        AdjNode *p = g->head[v];
        while (p) {
            printf(" -> %d", p->dest);
            p = p->next;
        }
        printf("\n");
    }
}


void BFS(Graph *g, int start) {
    if (start < 0 || start >= g->V) {
        printf("Invalid start vertex\n");
        return;
    }
    bool *visited = (bool*)calloc(g->V, sizeof(bool));
    int *queue = (int*)malloc(g->V * sizeof(int));
    int front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    printf("BFS traversal starting from %d: ", start);
    while (front < rear) {
        int u = queue[front++];
        printf("%d ", u);

        for (AdjNode *p = g->head[u]; p; p = p->next) {
            int v = p->dest;
            if (!visited[v]) {
                visited[v] = true;
                queue[rear++] = v;
            }
        }
    }
    printf("\n");
    free(visited);
    free(queue);
}

void DFSUtil(Graph *g, int u, bool visited[]) {
    visited[u] = true;
    printf("%d ", u);
    for (AdjNode *p = g->head[u]; p; p = p->next) {
        if (!visited[p->dest])
            DFSUtil(g, p->dest, visited);
    }
}

void DFS_recursive(Graph *g, int start) {
    if (start < 0 || start >= g->V) { printf("Invalid start vertex\n"); return; }
    bool *visited = (bool*)calloc(g->V, sizeof(bool));
    printf("DFS (recursive) starting from %d: ", start);
    DFSUtil(g, start, visited);
    printf("\n");
    free(visited);
}

void DFS_iterative(Graph *g, int start) {
    if (start < 0 || start >= g->V) { printf("Invalid start vertex\n"); return; }
    bool *visited = (bool*)calloc(g->V, sizeof(bool));
    int *stack = (int*)malloc(g->V * sizeof(int));
    int top = -1;

    stack[++top] = start;

    printf("DFS (iterative) starting from %d: ", start);
    while (top >= 0) {
        int u = stack[top--];
        if (visited[u]) continue;
        visited[u] = true;
        printf("%d ", u);

        int temp[64]; int tcount = 0;
        for (AdjNode *p = g->head[u]; p && tcount < 64; p = p->next) {
            temp[tcount++] = p->dest;
        }
        for (int i = tcount - 1; i >= 0; --i) {
            if (!visited[temp[i]]) stack[++top] = temp[i];
        }
    }
    printf("\n");
    free(visited);
    free(stack);
}

void freeGraph(Graph *g) {
    if (!g) return;
    for (int i = 0; i < g->V; ++i) {
        AdjNode *p = g->head[i];
        while (p) {
            AdjNode *tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    free(g->head);
    free(g);
}

int main(void) {
    int V, E, u, v;
    int choice;
    int start;
    int directedChoice;

    printf("Enter number of vertices: ");
    if (scanf("%d", &V) != 1 || V <= 0) { printf("Invalid vertex count\n"); return 0; }

    printf("Directed graph? (1 = yes, 0 = no): ");
    if (scanf("%d", &directedChoice) != 1) return 0;

    Graph *g = createGraph(V, directedChoice ? true : false);

    printf("Enter number of edges: ");
    if (scanf("%d", &E) != 1 || E < 0) { printf("Invalid edge count\n"); freeGraph(g); return 0; }

    printf("Enter edges (format: src dest) with vertices in range [0..%d]:\n", V - 1);
    for (int i = 0; i < E; ++i) {
        if (scanf("%d %d", &u, &v) != 2) { printf("Invalid edge\n"); freeGraph(g); return 0; }
        if (u < 0 || u >= V || v < 0 || v >= V) { printf("Edge out of range, skipping\n"); --i; continue; }
        addEdge(g, u, v);
    }

    printGraph(g);

    while (1) {
        printf("\n--- Traversal Menu ---\n");
        printf("1. BFS\n");
        printf("2. DFS (recursive)\n");
        printf("3. DFS (iterative)\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) break;
        if (choice == 4) break;

        printf("Enter start vertex: ");
        if (scanf("%d", &start) != 1) break;

        switch (choice) {
            case 1:
                BFS(g, start);
                break;
            case 2:
                DFS_recursive(g, start);
                break;
            case 3:
                DFS_iterative(g, start);
                break;
            default:
                printf("Invalid choice\n");
        }
    }

    freeGraph(g);
    return 0;
}

