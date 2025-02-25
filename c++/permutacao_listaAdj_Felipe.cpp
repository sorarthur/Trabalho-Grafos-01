#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

class Graph {
private:
    int vertex;
    vector<vector<int>> adj; 
    // rotulo dos vertices
    vector<char> labels {'A', 'B', 'C', 'D', 'E', 'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    set<vector<int>> cycles;

    void findCycles(int start, int current, vector<int>& path, vector<bool>& visited) {
        visited[current] = true;
        path.push_back(current);
        
        for (int neighbor : adj[current]) {
            if (neighbor == start && path.size() > 2) {
                vector<int> cycle = path;
                sort(cycle.begin(), cycle.end());
                cycles.insert(cycle);
            }
            if (!visited[neighbor]) {
                findCycles(start, neighbor, path, visited);
            }
        }
        
        visited[current] = false;
        path.pop_back();
    }
    
public:
    Graph(int vertex) {
        this->vertex = vertex;
        adj.resize(vertex);
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    void printGraph() {
        for (int i = 0; i < vertex; i++) {
            cout << "[" << labels[i] << "] -> ";
            for (int neighbor : adj[i]) {
                cout << labels[neighbor] << " ";
            }
            cout << endl;
        }
    }
    
    void enumerateCycles() {
        cycles.clear();
        
        for (int i = 0; i < vertex; i++) {
            vector<int> path;
            vector<bool> visited(vertex, false);
            findCycles(i, i, path, visited);
        }
        
        cout << "\nCiclos encontrados:" << endl;
        for (const auto& cycle : cycles) {
            for (int node : cycle) {
                cout << labels[node] << " ";
            }
            cout << endl;
        }
    }
    
    void countCycles() {
        auto start = high_resolution_clock::now();
        enumerateCycles();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        cout << "\nTotal de ciclos: " << cycles.size() << endl;
        cout << "Tempo de execução: " << duration.count() << " microssegundos" << endl;
    }
};

int main() {
    Graph g(6);

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

    g.printGraph();
    g.countCycles();

    return 0;
}
