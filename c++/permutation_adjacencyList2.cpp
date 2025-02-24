#include <iostream>
#include <vector>

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

    G.printAdjacencyList();

    return 0;
}
