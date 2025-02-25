#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <set>

using namespace std;

class Graph
{
private:
    vector<vector<int>> adjList; // Lista de adjacência para armazenar o grafo
    int V;                       // Número de vértices no grafo

public:
    // Construtor para o grafo com V vértices
    Graph(int V)
    {
        this->V = V;
        adjList.resize(V); // Redimensiona o vetor de adjacência para o número de vértices
    }

    // Função para adicionar uma aresta ao grafo
    void addEdge(int u, int v)
    {
        adjList[u].push_back(v); // Adiciona o vértice v à lista de adjacências de u
        adjList[v].push_back(u); // Como o grafo é não-direcionado, adiciona v à lista de adjacências de u e vice-versa
    }

    // Função para verificar se uma permutação de vértices forma um ciclo
    bool isCycle(vector<int> &cycle)
    {
        int n = cycle.size(); // Obtém o tamanho do ciclo

        // Percorre todos os vértices do ciclo
        for (int i = 0; i < n; i++)
        {
            int u = cycle[i];           // Pega o vértice atual
            int v = cycle[(i + 1) % n]; // Pega o próximo vértice (circular)

            // Verifica se existe uma aresta entre u e v
            if (find(adjList[u].begin(), adjList[u].end(), v) == adjList[u].end())
            {
                return false; // Se não encontrar aresta entre u e v, não é um ciclo
            }
        }
        return true; // Se todas as arestas existirem, é um ciclo
    }

    // Função para imprimir um ciclo, é chamada dentro do caminhar
    void imprimirCiclo(vector<int> &cycle)
    {
        for (int i : cycle)
        {
            cout << (char)(i + 'A') << " "; // Converte o índice para o caractere correspondente (A, B, C...)
        }
        cout << endl;
    }

    // Função para realizar a busca por ciclos
    void caminhar(int start, int length, vector<int> &cycle, vector<bool> &visited, set<string> &foundCycles)
    {
        if (cycle.size() == length)
        {
            if (isCycle(cycle))
            { // Verifica se a permutação atual é um ciclo
                vector<int> tempCycle = cycle;
                sort(tempCycle.begin(), tempCycle.end()); // Ordena o ciclo para evitar duplicação de ordem

                // Cria uma string representando o ciclo
                string cycleStr = "";
                for (int i : tempCycle)
                {
                    cycleStr += (char)(i + 'A'); // Converte o índice para o caractere correspondente (A, B, C...)
                    cycleStr += " ";
                }

                // Verifica se o ciclo já foi encontrado
                if (foundCycles.find(cycleStr) == foundCycles.end())
                {
                    foundCycles.insert(cycleStr); // Adiciona o ciclo ao conjunto de ciclos encontrados
                    imprimirCiclo(cycle);         // Chama a função para imprimir o ciclo
                }
            }
            return;
        }

        // Percorre todos os vértices para tentar formar um ciclo
        for (int i = start; i < V; i++)
        {
            if (!visited[i])
            {
                visited[i] = true;                                // Marca o vértice como visitado
                cycle.push_back(i);                               // Adiciona o vértice à lista de ciclo
                caminhar(0, length, cycle, visited, foundCycles); // Chama recursivamente para o próximo vértice
                cycle.pop_back();                                 // Remove o último vértice do ciclo
                visited[i] = false;                               // Marca o vértice como não visitado para explorar outras possibilidades
            }
        }
    }

    // Função para contar e exibir os ciclos encontrados
    void countCycles()
    {
        clock_t start_time = clock(); // Marca o tempo de início da execução

        set<string> foundCycles; // Conjunto para armazenar ciclos encontrados (evita duplicação)

        // Busca ciclos de tamanhos 3 a 6
        for (int length = 3; length <= 6; length++)
        {
            cout << "\nBuscando ciclos de tamanho " << length << ":\n";
            vector<int> cycle;                                // Lista que representa o ciclo
            vector<bool> visited(V, false);                   // Lista para verificar se um vértice já foi visitado
            caminhar(0, length, cycle, visited, foundCycles); // Chama a função de caminhada para buscar ciclos
        }

        clock_t end_time = clock();                                             // Marca o tempo de fim da execução
        double total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; // Calcula o tempo total de execução
        cout << "\nCiclos encontrados: " << foundCycles.size() << endl;         // Imprime o número de ciclos encontrados
        cout << "Tempo de execucao: " << total_time << " segundos\n";           // Imprime o tempo de execução
    }
};

int main()
{
    // Criar o grafo com 6 vértices (A a F)
    Graph g(6);

    // Adicionar as arestas conforme o enunciado
    g.addEdge(0, 1); // A <-> B
    g.addEdge(0, 3); // A <-> D
    g.addEdge(0, 4); // A <-> E
    g.addEdge(1, 3); // B <-> D
    g.addEdge(1, 2); // B <-> C
    g.addEdge(1, 4); // B <-> E
    g.addEdge(2, 3); // C <-> D
    g.addEdge(2, 4); // C <-> E
    g.addEdge(2, 5); // C <-> F
    g.addEdge(3, 5); // D <-> F
    g.addEdge(4, 5); // E <-> F

    // Contar e exibir os ciclos encontrados
    g.countCycles();

    return 0;
}