#include "Config.h"

Config::Config(const int& decision_epoch_horizon, const vector<vector<int>>& distance_matrix){
    this->decision_epoch_horizon = decision_epoch_horizon;
    this->distance_matrix = distance_matrix;
    this->dimension = distance_matrix.size();
}