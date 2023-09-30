#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NODES 100

// Structure to represent an edge in the graph
struct Edge {
    int from;
    int to;
    int cost;
};

// Structure to represent a node in the graph
struct Node {
    int number;
};

// Function to perform Uniform-Cost Search
void uniformCostSearch(struct Node nodes[], struct Edge edges[], int numNodes, int numEdges, int source, int destination) {
    int visited[MAX_NODES] = {0}; // To keep track of visited nodes
    int distance[MAX_NODES];     // To store the minimum distance to each node
    int parent[MAX_NODES];       // To store the parent node for each node in the path

    // Initialize distances to infinity and parent to -1
    for (int i = 0; i < numNodes; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    // Initialize distance to the source node as 0
    distance[source] = 0;

    // Uniform-Cost Search loop
    for (int i = 0; i < numNodes - 1; i++) {
        int minDistance = INT_MAX;
        int u = -1;

        // Find the node with the minimum distance that has not been visited yet
        for (int j = 0; j < numNodes; j++) {
            if (!visited[j] && distance[j] < minDistance) {
                minDistance = distance[j];
                u = j;
            }
        }

        if (u == -1) {
            break; // No more reachable nodes
        }

        visited[u] = 1;

        // Relaxation step - Update distance for neighboring nodes
        for (int j = 0; j < numEdges; j++) {
            if (edges[j].from == nodes[u].number) {
                int v = edges[j].to;
                int edgeCost = edges[j].cost;

                if (!visited[v] && distance[u] + edgeCost < distance[v]) {
                    distance[v] = distance[u] + edgeCost;
                    parent[v] = u;
                }
            }
        }
    }

    // Print the path from source to destination
    if (distance[destination] != INT_MAX) {
        printf("Shortest path from %d to %d:\n", source, destination);
        int current = destination;
        while (current != -1) {
            printf("%d", nodes[current].number);
            if (parent[current] != -1) {
                printf(" <- ");
            }
            current = parent[current];
        }
        printf("\nMinimum Cost: %d\n", distance[destination]);
    } else {
        printf("No path from %d to %d\n", source, destination);
    }
}

int main() {
    struct Node nodes[MAX_NODES];
    struct Edge edges[MAX_NODES];
    int numNodes, numEdges;

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter the node numbers:\n");
    for (int i = 0; i < numNodes; i++) {
        scanf("%d", &nodes[i].number);
    }

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    printf("Enter the edges (from to cost):\n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].cost);
    }

    int source, destination;
    printf("Enter the source node: ");
    scanf("%d", &source);
    printf("Enter the destination node: ");
    scanf("%d", &destination);

    uniformCostSearch(nodes, edges, numNodes, numEdges, source, destination);

    return 0;
}
