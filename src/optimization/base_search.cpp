#include "optimization/base_search.hpp"

// C++ standard libraries
#include <vector>

// Custom libraries
#include "optimization/parameter_set.hpp"

BaseSearch::BaseSearch(ParameterSet start, ParameterSet end, double step) : 
                        startSearch{start}, endSearch{end}, step{step} {}


void BaseSearch::setLogStream(std::mutex* mtx, std::ostream* out) {
    this->mtx = mtx;
    this->out = out;
}

ParameterSet BaseSearch::getBestParameters() const {
    return bestParameters;
}


std::vector<int> BaseSearch::getBestPath() const {
    return bestPath;
}


double BaseSearch::getBestScore() const {
    return bestScore;
}