#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <chrono>

using namespace std;

// Class to represent the Graph
class Graph
{
private:
    int vertex;  // Number of vertices in the graph
    vector<vector<int>> adjacencyList;  // Adjacency list to store the graph edges

public:
    // Constructor to initialize the graph with the number of vertices
    Graph(int vertex){
        this->vertex = vertex;
        adjacencyList.resize(vertex);  // Resize the adjacency list based on the number of vertices
    }

    // Function to add an edge between two vertices u and v
    void addEdge(int u, int v){
        adjacencyList[u].push_back(v);  // Add v to the adjacency list of u
        adjacencyList[v].push_back(u);  // Add u to the adjacency list of v (because it's an undirected graph)
    }

    // Function to print the adjacency list of the graph
    void print(){
        printf("\nADJACENCY LIST\n");
        // Loop through each vertex and print its adjacent vertices
        for (int i = 0; i < vertex; ++i)
        {
            printf("[%c]: ", 'A' + i );  // Print the vertex label (A, B, C, etc.)
            for (int j = 0; j < adjacencyList[i].size(); ++j)
            {
              printf("%c ", 'A' + adjacencyList[i][j] );  // Print each adjacent vertex
            }
            cout << endl;
        }
    }

    // Function to check if there is an edge between vertices u and v
    bool hasEdge(int u, int v){
        // Iterate through the adjacency list of vertex u and check if v is present
        for(int n : adjacencyList[u]){
            if (n == v)
            {
                return true;  // If there is an edge, return true
            }
        }
        return false;  // Return false if no edge is found
    }

    // Function to count and print all cycles in the graph
    void countCycles(){
        printf("\nCYCLES FOUND:\n");
        vector<int> vertices(vertex);  // Vector to store the list of vertices (from 0 to vertex-1)
        set<string> seenCycles;  // Set to store already printed cycles (to avoid duplicates)
        int cycleCount = 0;  // Variable to count the total number of cycles

        // Initialize the vector of vertices
        for (int i = 0; i < vertex; i++){
            vertices[i] = i;
        }

        // Start measuring execution time
        auto start = chrono::high_resolution_clock::now();

        // Generate all permutations of the vertices and check for cycles
        do{
            bool verify = true;  // Flag to verify if there is an edge between consecutive vertices

            // Check if all consecutive vertices in the permutation are connected by edges
            for (int i = 0; i < vertex-1; i++){
                if (!hasEdge(vertices[i], vertices[i+1])){
                    verify = false;  // If any consecutive vertices are not connected, set verify to false and break
                    vertex = i;
                }
            }

            // If all consecutive vertices are connected, check if there is a cycle
            if (verify){
                // Loop through all vertices and check for cycles
                for (int i = 0; i < vertex; i++){                
                    if (i >= 2){  // Start checking from the 3rd vertex onward
                        if (hasEdge(vertices[i], vertices[0])){  // Check if there is an edge from the last vertex to the first
                            string cycle = "";  // String to store the current cycle
                            for (int j = 0; j <= i; j++){  // Add each vertex in the cycle to the string
                                cycle += (char)('A' + vertices[j]);
                            }
                            // If the cycle hasn't been printed before, add it to the set and print it
                            if (seenCycles.find(cycle) == seenCycles.end()){
                                seenCycles.insert(cycle);  // Add the cycle to the set to avoid printing duplicates
                                for (int j = 0; j <= i; j++){
                                    printf("%c ", 'A' + vertices[j]);  // Print each vertex in the cycle
                                }
                                cout << endl;
                                cycleCount++;  // Increment the cycle count
                            }
                        }
                    }
                }
            }
        } while (next_permutation(vertices.begin(), vertices.end()));  // Generate the next permutation of vertices

        // End measuring execution time
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;  // Calculate the duration of the execution

        cout << "Total Cycles: " << cycleCount << endl;  // Print the total number of cycles
        cout << "Execution Time: " << duration.count() << " seconds" << endl;  // Print the execution time
    }
};

// Main function to execute the program
int main(void){
    Graph g(6);  // Create a graph with 6 vertices

    // Add edges between vertices (undirected graph)
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

    g.print();  // Print the adjacency list of the graph
    g.countCycles();  // Find and print all cycles in the graph
    return 0;
}
