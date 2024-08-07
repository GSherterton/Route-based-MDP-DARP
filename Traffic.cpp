#include <iostream>
#include <vector>

#define INFINITY 1000000000

using namespace std;

//olhar priority Queue para ver se nao fica melhor
//funcao que inicializa e preenche a matriz de adjacencia
void preencheAdj(const vector<vector<double>>& matrix, vector<vector<int>>& adj){
    int n = matrix.size();

    for(int i = 0; i < n; i++){
        vector<int> aux;
        //cout << "Criando a adjacencia do vertice " << i << ":" << endl;
        for(int j = 0; j < n; j++){
            if(matrix[i][j]){
                //cout << "Adicionei o vertice " << j << endl;
                aux.push_back(j);
            }
        }
        adj.push_back(aux);
    }
}

void updateAllPoints(vector<vector<double>>& base, vector<vector<double>>& traffic, vector<vector<double>>& current_distance){
    for(int i = 0; i < current_distance.size(); i++){
        for(int j = 0; j < current_distance[0].size(); j++){
            current_distance[i][j] = base[i][j] * traffic[i][j];
        }
    }
}

//pode se fazer uma funcao que atualize uma lista de pontos por exemplo ou algo semelhante

struct Route{
    vector<int> route;
    double obj = 0;
};

void findRoute(vector<int>& route, vector<int>& pen, int beg, int end){
    vector<int> aux;

    aux.push_back(end);
    while(pen[end] != beg){
        cout << "Penultimo: " << pen[end] << endl;
        aux.push_back(pen[end]);
        end = pen[end];
    }
    aux.push_back(beg);

    for(int i = aux.size()-1; i >= 0; i--){
        route.push_back(aux[i]);
    }
}

//tentar implementar o vetor de visitado com lista em vez de vector
void dijkstra(int beg, const vector<vector<double>>&matrix, vector<double>& distance, vector<bool>& visited, vector<int>& pen){
    for(int i = 0; i < matrix.size(); i++){
        int indexAux = -1;

        for(int j = 0; j < matrix.size(); j++){//pode mudar isso para uma lista de visitados para fazer menos iteracoes
            if(!visited[j] && (indexAux == -1 || distance[j] < distance[indexAux])){
                indexAux = j;
            }
        }

        if(distance[indexAux] == INFINITY){
            break;
        }

        visited[indexAux] = true;

        //pode mudar isso para caso o grafo nao seja completo
        for(int j = 0; j < matrix.size(); j++){
            if(matrix[indexAux][j]){
                double soma = distance[indexAux] + matrix[indexAux][j];
                if(distance[j] > soma){   
                    distance[j] = soma;
                    pen[j] = indexAux;
                }
            }
        }
    }
}

Route shortestPath(int beg, int end, const vector<vector<double>>& matrix){
    Route R;

    vector<bool> visited(matrix.size(), 0); //inicializa todos como falso
    vector<double> distance(matrix.size(), INFINITY);//inicializa todos como infinito
    distance[beg] = 0;//altera apenas o vertice de partida para 0
    vector<int> pen(matrix.size(), -1);//vetor de penultimo vertice visitado antes de chegar nele

    dijkstra(beg, matrix, distance, visited, pen);

    R.obj = distance[end];
    findRoute(R.route, pen, beg, end);

    return R;
}

void printMatrix(const vector<vector<double>>& matrix){
    //ajustando os valores para o vector
    int size = matrix.size() - 1;

    for(int i = 0; i <= size; i++){
        cout << "|";
        for(int j = 0; j <= size; j++){
            cout << matrix[i][j] << ((j == size) ? "|\n" : ", ");
        }
    }
}

void exibeRota(Route r){
    cout << "Rota: ";
    int n = r.route.size() - 1;

    for(int i = 0; i <= n; i++){
        cout << r.route[i] << (i == n ? "\n" : " -> ");
    }
}

//poderiamos ter um vetor de matrizes de trafego que evoluiria com o tempo por exemplo
//isso pode ser uma classe
//trabalhando com o grafo nesse sentido nao faria sentido o grafo ser completo e nesse sentido faria sentido usar uma matriz de adjacencia
int main(){
    //uma matriz base que sera usada como os menores tempos de viagem de um ponto ao outro
    vector<vector<double>> base_distance_matrix =   {{0, 7, 10, 3, 12},
                                                    {7, 0, 3, 4, 5},
                                                    {10, 3, 0, 8, 4},
                                                    {3, 4, 8, 0, 1},
                                                    {12, 5, 4, 1, 0}};

    vector<vector<int>> adj_matrix;
    
    preencheAdj(base_distance_matrix, adj_matrix);

    //uma matriz de trafego que sera usada para armazenar o valor do trafego, minimo valor é 1
    vector<vector<double>> traffic_matrix =     {{0, 1, 1.3, 1.1, 1.2},
                                                {1, 0, 1.8, 1.3, 1},
                                                {1.3, 1.8, 0, 1, 1.2},
                                                {1.1, 1.3, 1, 0, 1},
                                                {1.2, 1, 1.2, 1, 0}};

    vector<vector<double>> current_distance_matrix = base_distance_matrix;

    printMatrix(current_distance_matrix);

    cout << "------------------------------------\n";

    updateAllPoints(base_distance_matrix, traffic_matrix, current_distance_matrix);
    printMatrix(current_distance_matrix);

    cout << "------------------------------------\n";

    for(int i = 0; i < adj_matrix.size(); i++){
        cout << "|";
        for(int j = 0; j < adj_matrix[i].size(); j++){
            cout << adj_matrix[i][j] << ((j == (adj_matrix[i].size() - 1)) ? "|\n" : ", ");
        }
    }

    Route r;
    int beg = 2;
    int end = 3;
    r = shortestPath(beg, end, base_distance_matrix);
    cout << "Valor obj: " << r.obj << endl;
    exibeRota(r);

    return 0;
}