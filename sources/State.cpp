#include "State.h"

State::State(const Config& config){
    this->decision_epoch = 0;
    this->time = 0;
    this->position = 0; //mudar para colocar um depot
    this->status = vector<int>(config.get_dimension(), 0); //seta todos os status para 0
}