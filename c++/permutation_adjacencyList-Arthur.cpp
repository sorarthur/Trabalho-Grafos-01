#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class graph
{
private:
    int numOfVertex;
    vector<vector<int>> adjacencyList;
public:
    graph(int vertexN){
        numOfVertex = vertexN;
        adjacencyList.resize(numOfVertex);
    }

    void addEdge(int v1, int v2){
        adjacencyList[v1].push_back(v2);
        adjacencyList[v2].push_back(v1);
    }


 
    void printAdjacencyList(){
        for (int i = 0; i < numOfVertex; ++i)
        {
            cout << "Vertex " << i << " is connected to: ";
            for (int j = 0; j < adjacencyList[i].size(); ++j)
            {
                cout << adjacencyList[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool hasEdge(int v1, int v2){
        for(int neighbor : adjacencyList[v1]){
            if (neighbor == v2)
            {
                return true;
            }
        }
        return false;
    }

    void allCycles(){
        vector<int> vertices(numOfVertex);

        for (size_t i = 0; i < numOfVertex; i++)
        {
            vertices[i] = i;
        }
        
        do
        {
            bool isValid = true; // verify if has edge between vi and vi+1

            for (size_t i = 0; i < numOfVertex-1; i++)
            {
                if (!hasEdge(vertices[i], vertices[i+1]))
                {
                    isValid = false;
                    break;
                }
            }

            if (isValid)
            {
                for (size_t i = 0; i < numOfVertex; i++)
                {                
                    if (i >= 2)
                    {
                        // verify if the last of the sub-graph is the
                        // first of the graph, when it's true, the sub-graph is a cycle
                        if (hasEdge(vertices[i], vertices[0]))
                        {
                            for (size_t j = 0; j <= i; j++)
                            {
                                printf("%c ", 'A' + vertices[j]);
                            }
                            cout << endl;
                        }
                    }
                }
            }
        } while (next_permutation(vertices.begin(), vertices.end()));
    }

};

int main(void){
    graph G(6);

    /* A - 0; B - 1; C - 2; D - 3; E - 4; F - 5 */
    G.addEdge(0, 1);
    G.addEdge(0, 3);
    G.addEdge(0, 4);
    G.addEdge(1, 2);
    G.addEdge(1, 3);
    G.addEdge(1, 4);
    G.addEdge(2, 3);
    G.addEdge(2, 4);
    G.addEdge(2, 5);
    G.addEdge(3, 5);
    G.addEdge(4, 5);

    // G.printAdjacencyList();

    G.allCycles();
    return 0;
}
