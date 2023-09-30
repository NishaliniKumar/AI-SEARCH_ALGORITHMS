#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the adjacency list
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent the graph
struct Graph {
    int V; // Number of vertices
    struct Node** adjacency_list;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adjacency_list = (struct Node**)malloc(V * sizeof(struct Node*));
    
    // Initialize all adjacency lists as empty
    for (int i = 0; i < V; i++) {
        graph->adjacency_list[i] = NULL;
    }
    
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjacency_list[src];
    graph->adjacency_list[src] = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->adjacency_list[dest];
    graph->adjacency_list[dest] = newNode;
}

// Function to print the graph
void printGraph(struct Graph* graph) {
    printf("Adjacency List representation of the graph:\n");
    for (int i = 0; i < graph->V; i++) {
        printf("Node %d: ", i);
        struct Node* current = graph->adjacency_list[i];
        while (current != NULL) {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int V, E;
    printf("Enter the number of nodes (vertices): ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    struct Graph* graph = createGraph(V);

    printf("Enter the source and destination for each edge:\n");
    for (int i = 0; i < E; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printGraph(graph);

    return 0;
}
