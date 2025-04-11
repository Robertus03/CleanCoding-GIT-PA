#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjacency_lists;
} Graph;


Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Graph* create_graph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->visited = (int*)calloc(vertices, sizeof(int));
    graph->adjacency_lists = (Node**)malloc(vertices * sizeof(Node*));
    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
    }
    return graph;
}

void add_edge(Graph* graph, int src, int dest) {
    Node* node = create_node(dest);
    node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = node;

    node = create_node(src); 
    node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = node;
}

void reset_visited(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}



typedef struct QueueNode {
    int data;
    struct QueueNode *next;
} QueueNode;

int is_empty(QueueNode* q) {
    return q == NULL;
}

void enqueue(QueueNode** q, int data) {
    QueueNode* new_node = create_node(data);
    if (*q == NULL) {
        *q = new_node;
    } else {
        QueueNode* temp = *q;
        while (temp->next) temp = temp->next;
        temp->next = new_node;
    }
}

int dequeue(QueueNode** q) {
    int data = (*q)->data;
    QueueNode* temp = *q;
    *q = (*q)->next;
    free(temp);
    return data;
}



void DFS(Graph* graph, int vertex) {
    Node* adj = graph->adjacency_lists[vertex];
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (adj) {
        int v = adj->data;
        if (!graph->visited[v]) {
            DFS(graph, v);
        }
        adj = adj->next;
    }
}

void BFS(Graph* graph, int start) {
    QueueNode* queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        Node* temp = graph->adjacency_lists[current];
        while (temp) {
            int adj = temp->data;
            if (!graph->visited[adj]) {
                graph->visited[adj] = 1;
                enqueue(&queue, adj);
            }
            temp = temp->next;
        }
    }
}



void insert_edges(Graph* graph, int num_edges) {
    int src, dest;
    printf("Adaugă %d muchii (noduri de la 0 la %d):\n", num_edges, graph->vertices - 1);
    for (int i = 0; i < num_edges; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}



int main() {
    int num_vertices, num_edges, start;

    printf("Câte noduri are graful? ");
    scanf("%d", &num_vertices);
    printf("Câte muchii are graful? ");
    scanf("%d", &num_edges);

    Graph* graph = create_graph(num_vertices);
    insert_edges(graph, num_edges);

    printf("Nod start pentru DFS: ");
    scanf("%d", &start);
    printf("DFS: ");
    DFS(graph, start);

    reset_visited(graph);
    printf("\nNod start pentru BFS: ");
    scanf("%d", &start);
    printf("BFS: ");
    BFS(graph, start);

    printf("\n");
    return 0;
}
