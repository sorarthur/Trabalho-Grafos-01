#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
    // Verifica rotações na ordem normal.
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
    // Verifica rotações na ordem inversa.
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

bool isDuplicateCycle(int *newCycle, int length) {
    for (int i = 0; i < cycleCount; i++) {
        if (cycleLengths[i] == length && isSameCycle(cycles[i], newCycle, length)) {
            return true;
        }
    }
    return false;
}

void normalizeCycle(int *cycle, int length) {
    // Rotaciona o ciclo para que o vértice de menor valor fique na primeira posição.
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
        printf("Ciclo %d: ", cycleCount);
        // Imprime o ciclo, adicionando o vértice inicial no final para evidenciar o fechamento.
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
                // Adiciona o vértice inicial para fechar o ciclo
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
    cycleCount = 0;
    memset(visited, false, sizeof(visited));
    
    for (int i = 0; i < g->numVertex; i++) {
        findCycles(g, i, i, 0);
    }
    
    printf("Total de ciclos encontrados: %d\n", cycleCount);
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

    contarCiclos(&g);
    return 0;
}
