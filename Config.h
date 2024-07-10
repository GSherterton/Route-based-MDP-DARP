#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Config{
    private:
        int decision_epoch_horizon;
        vector<vector<int>> distance_matrix;
        int dimension;

    public:
        Config(const int& decision_epoch_horizon, const vector<vector<int>>& distance_matrix);
        
        inline int get_decision_epoch_horizon() const { return decision_epoch_horizon; }
        inline int get_distance(const int& i, const int& j) const { return distance_matrix[i-1][j-1]; }
        inline int get_dimension() const { return dimension; }
};