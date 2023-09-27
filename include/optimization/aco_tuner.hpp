#pragma once

// C++ standard libraries
#include <memory>
#include <vector>
#include <thread>

// Custom libraries
#include "base_search.hpp"
#include "base_strategy.hpp"
#include "parameter_set.hpp"
#include "acolony.hpp"

class ACOTuner {
    // Graph
    const std::vector<Point>& graph;

    // Control threads
    std::vector<std::thread> workers;
    std::vector<std::unique_ptr<BaseSearch>> tasks;
    const int n;

    // Domain for search
    ParameterSet startSearch, endSearch;

    // Cached information after fit
    ParameterSet bestParameters{};
    std::vector<int> bestPath;
    double bestScore{};

public:
    ACOTuner(const std::vector<Point>& graph, 
            const ParameterSet& startSearch, 
            const ParameterSet& endSearch, 
            const BaseStrategy& strategy,
            int n_jobs);

    // Search best parameters
    void fit();

    // Returns best parameters after fit
    ParameterSet getBestParameters() const;

    // Returns best path after fit
    std::vector<int> getBestPath() const;

    // Returns best score after fit
    double getBestScore() const;
};