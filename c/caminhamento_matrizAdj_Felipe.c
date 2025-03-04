#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_VERTICES 100
#define MAX_CYCLES 1000

typedef struct {
    int numVertex;
    int matrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

bool visited[MAX_VERTICES];
int path[MAX_VERTICES];
int cycleCount = 0;
int cycles[MAX_CYCLES][MAX_VERTICES];
int cycleLengths[MAX_CYCLES];

void startGraph(Graph *g, int numVertex) {
    g->numVertex = numVertex;
    memset(g->matrix, 0, sizeof(g->matrix));
}

void addEdge(Graph *g, int u, int v) {
    g->matrix[u][v] = 1;
    g->matrix[v][u] = 1;
}

bool isSameCycle(int *cycle1, int *cycle2, int length) {
    for (int i = 0; i < length; i++) {
        bool match = true;
        for (int j = 0; j < length; j++) {
            if (cycle1[j] != cycle2[(i + j) % length]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    for (int i = 0; i < length; i++) {
        bool match = true;
        for (int j = 0; j < length; j++) {
            if (cycle1[j] != cycle2[(i - j + length) % length]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

void print(Graph *g) {
    // Imprime cabeçalho (colunas)
    printf("    ");
    for (int j = 0; j < g->numVertex; j++) {
        printf("%c   ", 'a' + j); // imprime a, b, c, d, etc.
    }
    printf("\n");

    // Imprime cada linha da matriz
    for (int i = 0; i < g->numVertex; i++) {
        // Imprime o rótulo da linha
        printf("%c  ", 'a' + i);
        // Imprime os valores da linha (supondo que g->matrix seja uma matriz 2D)
        for (int j = 0; j < g->numVertex; j++) {
            printf("%d   ", g->matrix[i][j]);
        }
        printf("\n");
    }
}

bool isDuplicateCycle(int *newCycle, int length) {
    for (int i = 0; i < cycleCount; i++) {
        if (cycleLengths[i] == length && isSameCycle(cycles[i], newCycle, length)) {
            return true;
        }
    }
    return false;
}

void normalizeCycle(int *cycle, int length) {
    int minIndex = 0;
    for (int i = 1; i < length; i++) {
        if (cycle[i] < cycle[minIndex]) {
            minIndex = i;
        }
    }
    int sortedCycle[MAX_VERTICES];
    for (int i = 0; i < length; i++) {
        sortedCycle[i] = cycle[(minIndex + i) % length];
    }
    memcpy(cycle, sortedCycle, length * sizeof(int));
}

void storeCycle(int length) {
    int cycle[MAX_VERTICES];
    memcpy(cycle, path, length * sizeof(int));
    normalizeCycle(cycle, length);
    if (!isDuplicateCycle(cycle, length)) {
        memcpy(cycles[cycleCount], cycle, length * sizeof(int));
        cycleLengths[cycleCount] = length;
        cycleCount++;
        for (int i = 0; i < length; i++) {
            printf("%c", 'A' + cycle[i]);
            if (i < length - 1)
                printf("-");
        }
        printf("-%c\n", 'A' + cycle[0]);
    }
}

void findCycles(Graph *g, int start, int v, int length) {
    visited[v] = true;
    path[length] = v;
    
    for (int u = 0; u < g->numVertex; u++) {
        if (g->matrix[v][u]) {
            if (u == start && length >= 2) {
                path[length + 1] = start;
                storeCycle(length + 1);
            } else if (!visited[u] && u > start) {
                findCycles(g, start, u, length + 1);
            }
        }
    }
    
    visited[v] = false;
}

void contarCiclos(Graph *g) {
    clock_t start_time = clock();
    cycleCount = 0;
    memset(visited, false, sizeof(visited));
    
    for (int i = 0; i < g->numVertex; i++) {
        findCycles(g, i, i, 0);
    }
    
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000000;
    
    printf("Total Cycles: %d\n", cycleCount);
    printf("Execution Time: %.2f microseconds\n", time_taken);
}

int main(void) {
    Graph g;
    int numVertex = 6;
    startGraph(&g, numVertex);

    addEdge(&g, 0, 1);
    addEdge(&g, 0, 3);
    addEdge(&g, 0, 4);
    addEdge(&g, 1, 2);
    addEdge(&g, 1, 3);
    addEdge(&g, 1, 4);
    addEdge(&g, 2, 3);
    addEdge(&g, 2, 4);
    addEdge(&g, 2, 5);
    addEdge(&g, 3, 5);
    addEdge(&g, 4, 5);
    printf("GRAPH: \n");
    print(&g);
    printf("\nCYCLES:\n");
    contarCiclos(&g);
    return 0;
}
