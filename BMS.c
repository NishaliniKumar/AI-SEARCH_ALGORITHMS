#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a node in the adjacency list
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent the graph
struct Graph {
    int V; // Number of vertices
    struct Node** adjList; // Array of adjacency lists
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with 'V' vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adjList = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // For an undirected graph, add an edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Utility function to print a path
void printPath(int path[], int pathLength) {
    for (int i = 0; i < pathLength; i++) {
        printf("%d", path[i]);
        if (i < pathLength - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

// Recursive function to find and print all paths from src to dest
void findAllPaths(struct Graph* graph, int src, int dest, bool visited[], int path[], int pathLength) {
    visited[src] = true;
    path[pathLength] = src;
    pathLength++;

    if (src == dest) {
        // We have reached the destination, print the path
        printPath(path, pathLength);
    } else {
        // Recur for all adjacent vertices of the current vertex
        struct Node* current = graph->adjList[src];
        while (current != NULL) {
            int adjacentNode = current->data;
            if (!visited[adjacentNode]) {
                findAllPaths(graph, adjacentNode, dest, visited, path, pathLength);
            }
            current = current->next;
        }
    }

    // Mark the current node as unvisited to explore other paths
    visited[src] = false;
}

// Function to find and print all paths from src to dest
void BMS(struct Graph* graph, int src, int dest) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    int* path = (int*)malloc(graph->V * sizeof(int));
    int pathLength = 0;

    printf("Paths from %d to %d:\n", src, dest);
    findAllPaths(graph, src, dest, visited, path, pathLength);

    free(visited);
    free(path);
}

// Function to print the graph
void printGraph(struct Graph* graph) {
    printf("Graph Representation:\n");
    for (int i = 0; i < graph->V; i++) {
        struct Node* current = graph->adjList[i];
        printf("Node %d: ", i);
        while (current != NULL) {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int V, E;
    printf("Enter the number of nodes: ");
    scanf("%d", &V);

    struct Graph* graph = createGraph(V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    printf("Enter the edges (source node and destination node):\n");
    for (int i = 0; i < E; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printGraph(graph);

    int src, dest;
    printf("Enter source node: ");
    scanf("%d", &src);
    printf("Enter destination node: ");
    scanf("%d", &dest);

    BMS(graph, src, dest);

    return 0;
}
