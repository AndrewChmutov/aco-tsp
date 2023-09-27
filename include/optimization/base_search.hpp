#pragma once

// C++ standard libraries
#include <vector>
#include <thread>
#include <fstream>

// Custom libraries
#include "parameter_set.hpp"

class BaseSearch {
protected:
    // Domain for search
    ParameterSet startSearch;
    ParameterSet endSearch;
    double step;

    // Best during search
    ParameterSet bestParameters;
    std::vector<int> bestPath;
    double bestScore;

    // Log
    std::mutex* mtx;
    std::ostream* out;

public:
    BaseSearch(ParameterSet start, ParameterSet end, double step);

    // Search method. Has to assign:
    // - bestParameters
    // - bestPath
    // - bestScore
    virtual void search() = 0;

    void setLogStream(std::mutex* mtx, std::ostream* out);

    // Returns best parameters after search
    ParameterSet getBestParameters() const;

    // Returns best path after search
    std::vector<int> getBestPath() const;

    // Returns best score after search
    double getBestScore() const;
};