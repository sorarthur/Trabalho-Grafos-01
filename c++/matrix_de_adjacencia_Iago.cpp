#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;

/*
posição das Linhas e Colunas = Vertices
valor quardado = aresta

funções:
receber arestas
colocar "1" nas posições
*/

class grafo{
    public:
        int n;
        vector<vector<int>> matriz;

        grafo(int n){
            this->n = n;
            this->matriz = vector<vector<int>>(n, vector<int>(n));
        }

        void addAresta(int a, int b){
            matriz[a][b] = 1;
            matriz[b][a] = 1;
        }

        void printMatriz(){
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << matriz[i][j] << " ";
                }
                cout << endl;
            }
        }

        void swap(vector<int>& v, int i, int j) {
            int temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }

        void temAresta(vector<vector<int>>& matriz, std::vector<int> v, int n){
            bool result = false;
            int k = 0;
            int j = 0;
            for (size_t i = 0; i < n; i++)
            {
                k = v[i];
                j = v[i+1];
                if (matriz[k][j] != 1)
                {
                    break;
                }
                else
                {
                    result = true;
                }
            }
            
        }


        void existeCiclo(std::vector<int> v, vector<vector<int>>& matriz, int n){
            bool result = false;
            int count = 0;
            int i = 0;
            int j = 0;
        
            for (size_t i = 0; i < n-1; i++)
            {
                i = v[i];
                j = v[i+1];
        
                if (v[i] == matriz[i][j])
                {
                    count += 1;
                }
            }
            if (count == n)
            {
                result = true;
            }
            
        
        }
        
        void permuta(vector<vector<int>>& matriz, int n){
            std::vector<int> v(n);
            for (size_t i = 0; i < n; i++)
            {
                v[i] = i;
            }
            permutaM(v, 0, n, matriz);
        }

        //permutação mestre
        void permutaM(vector<int>& v, int i, int n, vector<vector<int>>& matriz) {
            if (i == n) { // tamanho do vetor
                for (int k = 0; k < n; k++) {
                    cout << v[k] << " ";
                }
                cout << endl;
                //existeCiclo(v, matriz, n);//procurar ciclo
            } else {
                for (int j = i; j < n; j++) { // permutação
                    swap(v, i, j);
                    permutaM(v, i + 1, n, matriz);
                    swap(v, i, j);
                    
                }
            }
        }
};




int main(){
    grafo G(6);

    /* A - 0; B - 1; C - 2; D - 3; E - 4; F - 5 */
    G.addAresta(0, 1);
    G.addAresta(0, 3);
    G.addAresta(0, 4);
    G.addAresta(1, 2);
    G.addAresta(1, 3);
    G.addAresta(1, 4);
    G.addAresta(2, 3);
    G.addAresta(2, 4);
    G.addAresta(2, 5);
    G.addAresta(3, 5);
    G.addAresta(4, 5);

    G.printMatriz();
    cout << endl;

    auto start = chrono::high_resolution_clock::now();

    G.permuta(G.matriz, G.n);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Tempo de execucao: " << duration.count() << " microssegundos" << endl;

    return 0;
}