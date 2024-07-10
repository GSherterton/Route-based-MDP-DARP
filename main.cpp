#include <iostream>
#include <vector>
#include "Config.h"

using namespace std;

static int K = 7; //decision epoch horizon

//things to change
//decision epoch definition, distance matrix definition

int main(){
    //a decision epoch occurs when the vehicle arrives at a location and observers new customer requests.
    /*the current state sk at decision epoch k includes the time of arrival, the vehicle's current location,
    passangers on the vehicle, the times at which the passengers were picked up,
    the pickup and delivery locations of these in-process requests as well as those of any outstanding requests, and the associated time windows.*/
    vector<vector<int>> distance_matrix =   {{0, 1, 2, 3},
                                             {1, 0, 5, 2},
                                             {2, 5, 0, 1},
                                             {3, 2, 1, 0}};

    Config config = Config(K, distance_matrix);

    for(int k = 0; k <= config.get_decision_epoch_horizon(); k++){//iterates at each decision epoch
        
    }

    return 0;
}