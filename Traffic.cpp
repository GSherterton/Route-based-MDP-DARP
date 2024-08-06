#include <iostream>
#include <vector>

#define INFINITY 1000000000

using namespace std;

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

vector<int> findRoute(vector<int>& route, vector<int>& pen, int beg, int end){
    vector<int> aux;

    aux.push_back(end);
    while(pen[end] != beg){
        aux.push_back(pen[end]);
        end = pen[end];
    }
    aux.push_back(beg);

    for(int i = aux.size()-1; i > 0; i++){
        route.push_back(aux[i]);
    }
}

void dijkstra(int beg, const vector<vector<double>>&matrix, vector<double>& distance, vector<bool>& visited, vector<int>& pen){
    int min = INFINITY;

    //for(int i = 1; i )
}

Route shortestPath(int beg, int end, const vector<vector<double>>& matrix){
    Route R;

    vector<bool> visited(matrix.size(), 0);
    vector<double> distance(matrix.size(), INFINITY);
    distance[beg] = 0;
    vector<int> pen(matrix.size(), -1);

    dijkstra(beg, matrix, distance, visited, pen);

    R.obj = distance[end];
    findRoute(R.route, pen, beg, end);
}

void print(const vector<vector<double>>& matrix){
    //ajustando os valores para o vector
    int size = matrix.size() - 1;

    for(int i = 0; i <= size; i++){
        cout << "|";
        for(int j = 0; j <= size; j++){
            cout << matrix[i][j] << ((j == size) ? "|\n" : ", ");
        }
    }
}

//poderiamos ter um vetor de matrizes de trafego que evoluiria com o tempo por exemplo
//isso pode ser uma classe
int main(){
    //uma matriz base que sera usada como os menores tempos de viagem de um ponto ao outro
    vector<vector<double>> base_distance_matrix =   {{0, 7, 10, 3, 12},
                                                    {7, 0, 3, 4, 5},
                                                    {10, 3, 0, 8, 4},
                                                    {3, 4, 8, 0, 1},
                                                    {12, 5, 4, 1, 0}};

    //uma matriz de trafego que sera usada para armazenar o valor do trafego, minimo valor é 1
    vector<vector<double>> traffic_matrix =     {{0, 1, 1.3, 1.1, 1.2},
                                                {1, 0, 1.8, 1.3, 1},
                                                {1.3, 1.8, 0, 1, 1.2},
                                                {1.1, 1.3, 1, 0, 1},
                                                {1.2, 1, 1.2, 1, 0}};

    vector<vector<double>> current_distance_matrix = base_distance_matrix;

    print(current_distance_matrix);

    cout << "------------------------------------\n";

    updateAllPoints(base_distance_matrix, traffic_matrix, current_distance_matrix);
    print(current_distance_matrix);

    

    return 0;
}