#include "optimization/aco_tuner.hpp"

// C++ standard libraries
#include <vector>

// Custom libraries
#include "optimization/base_search.hpp"
#include "optimization/base_strategy.hpp"
#include "optimization/parameter_set.hpp"

ACOTuner::ACOTuner(const std::vector<Point>& graph,
                    const ParameterSet& startSearch,
                    const ParameterSet& endSearch,
                    const BaseStrategy& strategy,
                    int n_jobs) :
                graph{graph}, 
                startSearch{startSearch}, 
                endSearch{endSearch}, 
                n{n_jobs} {
    
    workers.reserve(n);
    tasks = strategy.generateTasks(startSearch, endSearch, n);
}


ParameterSet ACOTuner::getBestParameters() const {
    return bestParameters;
}


std::vector<int> ACOTuner::getBestPath() const {
    return bestPath;
}


double ACOTuner::getBestScore() const {
    return bestScore;
}


void ACOTuner::fit() {}