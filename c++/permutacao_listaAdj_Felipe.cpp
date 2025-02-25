#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// classe Graph que representa um grafo não direcionado
class Graph {
private:
    int vertex;  // número de vértices no grafo
    vector<vector<int>> adj;  // lista de adjacência para armazenar os vizinhos de cada vértice
    
    // vetor de rótulos para os vértices (usado para nomear os vértices de A a Z)
    vector<char> labels {'A', 'B', 'C', 'D', 'E', 'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    
    set<vector<int>> cycles;  // conjunto para armazenar os ciclos encontrados, garantindo que não haja ciclos duplicados

    // função recursiva para encontrar ciclos a partir de um vértice 'start'
    void findCycles(int start, int current, vector<int>& path, vector<bool>& visited) {
        visited[current] = true;  // marca o vértice atual como visitado
        path.push_back(current);  // adiciona o vértice atual ao caminho
        
        // percorre todos os vizinhos do vértice atual
        for (int neighbor : adj[current]) {
            // verifica se encontrou um ciclo (retorna ao vértice de início e o ciclo tem pelo menos 3 vértices)
            if (neighbor == start && path.size() > 2) {
                vector<int> cycle = path;  // cria uma cópia do caminho
                sort(cycle.begin(), cycle.end());  // ordena o ciclo para garantir que ciclos diferentes, mas com os mesmos vértices, sejam considerados iguais
                cycles.insert(cycle);  // insere o ciclo no conjunto de ciclos (não permite duplicatas)
            }
            // caso o vizinho ainda não tenha sido visitado, chama recursivamente para buscar ciclos
            if (!visited[neighbor]) {
                findCycles(start, neighbor, path, visited);
            }
        }
        
        // desfaz a visita ao vértice atual e remove-o do caminho
        visited[current] = false;
        path.pop_back();
    }
    
public:
    // construtor que inicializa o número de vértices e a lista de adjacência
    Graph(int vertex) {
        this->vertex = vertex;
        adj.resize(vertex);  // redimensiona a lista de adjacência para o número de vértices
    }
    
    // função para adicionar uma aresta entre dois vértices u e v
    void addEdge(int u, int v) {
        adj[u].push_back(v);  // adiciona v à lista de adjacência de u
        adj[v].push_back(u);  // adiciona u à lista de adjacência de v (grafo não direcionado)
    }
    
    // função para imprimir o grafo (listas de adjacência)
    void printGraph() {
        for (int i = 0; i < vertex; i++) {
            cout << "[" << labels[i] << "] -> ";  // imprime o rótulo do vértice
            for (int neighbor : adj[i]) {  // para cada vizinho, imprime o rótulo do vizinho
                cout << labels[neighbor] << " ";
            }
            cout << endl;
        }
    }
    
    // função para enumerar todos os ciclos do grafo
    void enumerateCycles() {
        cycles.clear();  // limpa o conjunto de ciclos para garantir que ciclos anteriores não sejam considerados
        
        // para cada vértice no grafo, tenta encontrar ciclos a partir desse vértice
        for (int i = 0; i < vertex; i++) {
            vector<int> path;  // armazena o caminho atual durante a busca
            vector<bool> visited(vertex, false);  // vetor para marcar os vértices visitados
            findCycles(i, i, path, visited);  // chama a função recursiva para encontrar ciclos
        }
        
        // exibe todos os ciclos encontrados
        cout << "\nCiclos encontrados:" << endl;
        for (const auto& cycle : cycles) {
            for (int node : cycle) {
                cout << labels[node] << " ";  // imprime os rótulos dos vértices do ciclo
            }
            cout << endl;
        }
    }
    
    // função para contar o número de ciclos e medir o tempo de execução
    void countCycles() {
        auto start = high_resolution_clock::now();  // marca o tempo de início da execução
        enumerateCycles();  // chama a função que encontra os ciclos
        auto stop = high_resolution_clock::now();  // marca o tempo de término da execução
        auto duration = duration_cast<microseconds>(stop - start);  // calcula a duração da execução em microssegundos
        
        // exibe o número de ciclos encontrados e o tempo de execução
        cout << "\nTotal de ciclos: " << cycles.size() << endl;
        cout << "Tempo de execução: " << duration.count() << " microssegundos" << endl;
    }
};

int main() {
    Graph g(6);  // cria um grafo com 6 vértices
    
    // adiciona as arestas do grafo (conectando vértices)
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(2, 5);
    g.addEdge(4, 5);
    
    // exibe o grafo
    g.printGraph();
    
    // conta e exibe os ciclos e o tempo de execução
    g.countCycles();

    return 0;
}
