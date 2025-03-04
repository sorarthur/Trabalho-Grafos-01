#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <set>

using namespace std;

class Graph {
private:
    int vertex; // Número de vértices no grafo
    vector<vector<int>> adjacencyList; // Lista de adjacência para armazenar as conexões do grafo

public:
    // Construtor para inicializar o grafo com um número específico de vértices
    Graph(int vertex) {
        this->vertex = vertex;
        adjacencyList.resize(vertex); // Redimensiona a lista de adjacência para o número de vértices
    }

    // Função para adicionar uma aresta entre dois vértices u e v
    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v); // Adiciona v à lista de adjacência de u
        adjacencyList[v].push_back(u); // Adiciona u à lista de adjacência de v (grafo não direcionado)
    }

    // Função para imprimir a lista de adjacência do grafo
    void print() {
        printf("\nADJACENCY LIST\n");
        for (int i = 0; i < vertex; ++i) {
            printf("[%c]: ", 'A' + i); // Imprime o vértice atual (A, B, C, etc.)
            for (int j : adjacencyList[i]) {
                printf("%c ", 'A' + j); // Imprime os vértices adjacentes
            }
            cout << endl;
        }
    }
    
    // Função para verificar se existe uma aresta entre dois vértices u e v
    bool hasEdge(int u, int v) {
        // Procura v na lista de adjacência de u
        return find(adjacencyList[u].begin(), adjacencyList[u].end(), v) != adjacencyList[u].end();
    }

    // Função para contar o número de ciclos no grafo
    void countCycles() {
        printf("\nCYCLES FOUND:\n");
        vector<int> vertices(vertex); // Vetor para armazenar os vértices
        set<string> seenCycles; // Conjunto para armazenar ciclos já vistos
        int cycleCount = 0; // Contador de ciclos

        // Inicializa o vetor de vértices com valores de 0 a vertex-1
        for (int i = 0; i < vertex; i++) {
            vertices[i] = i;
        }

        // Inicia a medição do tempo de execução
        auto start = chrono::high_resolution_clock::now();

        // Gera todas as permutações possíveis dos vértices
        do {
            bool verify = true;
            // Verifica se a permutação atual forma um caminho válido
            for (int i = 0; i < vertex - 1; i++) {
                if (!hasEdge(vertices[i], vertices[i + 1])) { // Verifica se há uma aresta entre vértices consecutivos
                    verify = false;
                    break; // Se não houver aresta, a permutação não forma um caminho válido
                }
            }

            // Se a permutação formar um caminho válido, verifica se forma um ciclo
            if (verify) {
                for (int i = 2; i < vertex; i++) {
                    if (hasEdge(vertices[i], vertices[0])) { // Verifica se o vértice atual está conectado ao primeiro
                        // Extrai o ciclo da permutação
                        vector<int> cycle(vertices.begin(), vertices.begin() + i + 1);
                        // Encontra o índice do menor vértice no ciclo
                        int minIndex = min_element(cycle.begin(), cycle.end()) - cycle.begin();
                        // Rotaciona o ciclo para começar pelo menor vértice
                        rotate(cycle.begin(), cycle.begin() + minIndex, cycle.end());
                        // Garante que o ciclo seja único, invertendo se necessário
                        if (cycle[1] > cycle.back()) {
                            reverse(cycle.begin() + 1, cycle.end());
                        }
                        // Converte o ciclo em uma string para armazenamento no conjunto
                        string cycleStr;
                        for (int v : cycle) {
                            cycleStr += (char)('A' + v);
                        }
                        // Se o ciclo não foi visto antes, adiciona ao conjunto e imprime
                        if (seenCycles.insert(cycleStr).second) {
                            for (size_t i = 0; i < cycle.size(); i++) {
                                if (i > 0) cout << "-";
                                cout << (char)('A' + cycle[i]);
                            }
                            cout << endl;
                                                            
                            cycleCount++; // Incrementa o contador de ciclos
                        }
                    }
                }
            }
        } while (next_permutation(vertices.begin(), vertices.end())); // Gera a próxima permutação

        // Finaliza a medição do tempo de execução
        auto end = chrono::high_resolution_clock::now();
        // Calcula a duração em microsegundos
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

        // Imprime o número total de ciclos encontrados e o tempo de execução em microsegundos
        cout << "Total Cycles: " << cycleCount << endl;
        cout << "Execution Time: " << duration.count() << " microseconds" << endl;
    }
};

int main() {
    // Cria um grafo com 6 vértices
    Graph g(6);

    // Adiciona arestas ao grafo
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    // Imprime a lista de adjacência do grafo
    g.print();
    // Conta e imprime os ciclos no grafo, medindo o tempo em microsegundos
    g.countCycles();
    return 0;
}
