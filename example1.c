#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjacencyList;
} Graph;

typedef struct Stack {
    int top;
    int capacity;
    int *items;
} Stack;


Node *createNode(int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int numVertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = numVertices;
    graph->adjacencyList = malloc(numVertices * sizeof(Node *));
    graph->visited = malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++) {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    Node *newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

void resetVisited(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}



Stack *createStack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    stack->items = malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(Stack *stack, int value) {
    if (stack->top + 1 < stack->capacity) {
        stack->top++;
        stack->items[stack->top] = value;
    }
}

void clearStack(Stack *stack) {
    stack->top = -1;
}



void DFS(Graph *graph, Stack *stack, int vertex) {
    Node *adjList = graph->adjacencyList[vertex];
    Node *temp = adjList;

    graph->visited[vertex] = 1;
    push(stack, vertex);

    while (temp != NULL) {
        int connectedVertex = temp->data;
        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, stack, connectedVertex);
        }
        temp = temp->next;
    }
}



void insertEdges(Graph *graph, int edgeCount) {
    int src, dest;

    printf("Adaugă %d muchii (nodurile de la 0 la %d):\n", edgeCount, graph->vertices - 1);
    for (int i = 0; i < edgeCount; i++) {
        printf("Muchia %d - Introduceți două noduri (src dest): ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
}



void checkPaths(Graph *graph, int vertexCount) {
    Stack *s1 = createStack(vertexCount);
    Stack *s2 = createStack(vertexCount);

    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (i != j) {
                clearStack(s1);
                clearStack(s2);

                resetVisited(graph);
                DFS(graph, s1, i);

                resetVisited(graph);
                DFS(graph, s2, j);

                int pathExists = 0;
                for (int a = 0; a <= s1->top && !pathExists; a++) {
                    for (int b = 0; b <= s2->top; b++) {
                        if (s1->items[a] == j && s2->items[b] == i) {
                            pathExists = 1;
                            break;
                        }
                    }
                }

                printf("Drum între %d și %d: %s\n", i, j, pathExists ? "DA" : "NU");
            }
        }
    }

    free(s1->items);
    free(s1);
    free(s2->items);
    free(s2);
}



int main() {
    int vertexCount, edgeCount;

    printf("Câte noduri are graful? ");
    scanf("%d", &vertexCount);

    printf("Câte muchii are graful? ");
    scanf("%d", &edgeCount);

    Graph *graph = createGraph(vertexCount);
    insertEdges(graph, edgeCount);

    checkPaths(graph, vertexCount);

    return 0;
}
