#pragma once

// C++ standard libraries
#include <vector>

// Custom libraries
#include "parameter_set.hpp"

class BaseSearch {
    // Domain for search
    ParameterSet startSearch;
    ParameterSet endSearch;

    // Best during search
    ParameterSet bestParameters;
    std::vector<int> bestPath;
    double bestScore;

public:
    BaseSearch(ParameterSet start, ParameterSet end);

    // Search method. Has to assign:
    // - bestParameters
    // - bestPath
    // - bestScore
    virtual void search() = 0;

    // Returns best parameters after search
    ParameterSet getBestParameters() const;

    // Returns best path after search
    std::vector<int> getBestPath() const;

    // Returns best score after search
    double getBestScore() const;
};