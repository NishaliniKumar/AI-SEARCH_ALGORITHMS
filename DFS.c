#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// Structure to represent a node in the graph
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent the graph
struct Graph {
    int numNodes;
    struct Node* adjacencyList[MAX_NODES];
};

// Function to initialize a graph
void initializeGraph(struct Graph* graph, int numNodes) {
    graph->numNodes = numNodes;
    for (int i = 0; i < numNodes; i++) {
        graph->adjacencyList[i] = NULL;
    }
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = dest;
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;
}

// Function to perform Depth-First Search and print the paths
void DFS(struct Graph* graph, int currentNode, int targetNode, int* visited, int* path, int depth) {
    visited[currentNode] = 1;
    path[depth] = currentNode;

    if (currentNode == targetNode) {
        printf("Path: ");
        for (int i = 0; i <= depth; i++) {
            printf("%d", path[i]);
            if (i < depth) {
                printf(" -> ");
            }
        }
        printf("\n");
    } else {
        struct Node* currentNeighbor = graph->adjacencyList[currentNode];
        while (currentNeighbor != NULL) {
            int neighborNode = currentNeighbor->data;
            if (!visited[neighborNode]) {
                DFS(graph, neighborNode, targetNode, visited, path, depth + 1);
            }
            currentNeighbor = currentNeighbor->next;
        }
    }

    visited[currentNode] = 0;
}

int main() {
    struct Graph graph;
    int numNodes, numEdges;

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    initializeGraph(&graph, numNodes);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        printf("Enter source and destination of edge %d: ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(&graph, src, dest);
    }

    int visited[MAX_NODES] = {0}; // Initialize all nodes as unvisited
    int path[MAX_NODES];

    int startNode, targetNode;
    printf("Enter the source node: ");
    scanf("%d", &startNode);
    printf("Enter the target node: ");
    scanf("%d", &targetNode);

    printf("Paths from Node %d to Node %d using DFS:\n", startNode, targetNode);
    DFS(&graph, startNode, targetNode, visited, path, 0);

    return 0;
}