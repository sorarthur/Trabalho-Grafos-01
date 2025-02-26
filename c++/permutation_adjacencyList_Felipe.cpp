#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <set>

using namespace std;

class Graph {
private:
    int vertex;
    vector<vector<int>> adjacencyList;

public:
    Graph(int vertex) {
        this->vertex = vertex;
        adjacencyList.resize(vertex);
    }

    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }

    void print() {
        printf("\nADJACENCY LIST\n");
        for (int i = 0; i < vertex; ++i) {
            printf("[%c]: ", 'A' + i);
            for (int j : adjacencyList[i]) {
                printf("%c ", 'A' + j);
            }
            cout << endl;
        }
    }

    bool hasEdge(int u, int v) {
        return find(adjacencyList[u].begin(), adjacencyList[u].end(), v) != adjacencyList[u].end();
    }

    void countCycles() {
        printf("\nCYCLES FOUND:\n");
        vector<int> vertices(vertex);
        set<string> seenCycles;
        int cycleCount = 0;

        for (int i = 0; i < vertex; i++) {
            vertices[i] = i;
        }

        auto start = chrono::high_resolution_clock::now();

        do {
            bool verify = true;
            for (int i = 0; i < vertex - 1; i++) {
                if (!hasEdge(vertices[i], vertices[i + 1])) {
                    verify = false;
                    i = vertex;
                }
            }

            if (verify) {
                for (int i = 2; i < vertex; i++) {
                    if (hasEdge(vertices[i], vertices[0])) {
                        vector<int> cycle(vertices.begin(), vertices.begin() + i + 1);
                        int minIndex = min_element(cycle.begin(), cycle.end()) - cycle.begin();
                        rotate(cycle.begin(), cycle.begin() + minIndex, cycle.end());
                        if (cycle[1] > cycle.back()) {
                            reverse(cycle.begin() + 1, cycle.end());
                        }
                        string cycleStr;
                        for (int v : cycle) {
                            cycleStr += (char)('A' + v);
                        }
                        if (seenCycles.insert(cycleStr).second) {
                            for (int v : cycle) {
                                printf("%c ", 'A' + v);
                            }
                            cout << endl;
                            cycleCount++;
                        }
                    }
                }
            }
        } while (next_permutation(vertices.begin(), vertices.end()));

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;

        cout << "Total Cycles: " << cycleCount << endl;
        cout << "Execution Time: " << duration.count() << " seconds" << endl;
    }
};

int main() {
    Graph g(6);

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

    g.print();
    g.countCycles();
    return 0;
}
