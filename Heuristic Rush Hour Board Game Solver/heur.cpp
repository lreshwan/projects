#include <cmath>
#include "heur.h"
#include <vector>
#include <set>
#include "board.h"

using namespace std;

// Complete
size_t BFSHeuristic::compute(const Board& b)
{
    return 0U;
}


// To be completed
size_t DirectHeuristic::compute(const Board& b)
{
    //sees if cars are in way of escape vehicle, if so add them to heuristic counter
    int row = b.escapeVehicle().startr;
    int endCol = b.escapeVehicle().startc + b.escapeVehicle().length;
    size_t counter = 0;

    for(int i = endCol; i < b.size(); i++){
        if((b.at(row, i)) != '.'){
            counter++;
        }
    }

    return counter;
}

// To be completed
size_t IndirectHeuristic::compute(const Board& b)
{
    // Avoid compiler warnings -- replace this
    return 0;
}

