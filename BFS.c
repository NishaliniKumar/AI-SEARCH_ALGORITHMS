#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

// Structure to represent a node in the graph
struct Node {
    int label;
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
    newNode->label = dest;
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;
}

// Function to perform Breadth-First Search
bool BFS(struct Graph* graph, int startNode, int targetNode) {
    int visited[MAX_NODES] = {0}; // Initialize all nodes as unvisited
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    int parent[MAX_NODES]; // Store the parent of each node for reconstructing the path
    for (int i = 0; i < MAX_NODES; i++) {
        parent[i] = -1; // Initialize parent array
    }

    visited[startNode] = 1;
    queue[rear++] = startNode;

    while (front < rear) {
        int currentNode = queue[front++];
        if (currentNode == targetNode) {
            // Found the target node, reconstruct and print the path
            printf("Path: %d", currentNode);
            int current = currentNode;
            while (parent[current] != -1) {
                current = parent[current];
                printf(" <- %d ", current);
            }
            printf("\n");
            return true; // Path found
        }

        struct Node* currentNeighbor = graph->adjacencyList[currentNode];
        while (currentNeighbor != NULL) {
            int neighborNode = currentNeighbor->label;
            if (!visited[neighborNode]) {
                visited[neighborNode] = 1;
                parent[neighborNode] = currentNode;
                queue[rear++] = neighborNode;
            }
            currentNeighbor = currentNeighbor->next;
        }
    }

    return false; // No path found
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

    int startNode, targetNode;
    printf("Enter the source node: ");
    scanf("%d", &startNode);
    printf("Enter the target node: ");
    scanf("%d", &targetNode);

    printf("Finding path from Node %d to Node %d using BFS:\n", startNode, targetNode);
    if (!BFS(&graph, startNode, targetNode)) {
        printf("No path found.\n");
    }

    return 0;
}
