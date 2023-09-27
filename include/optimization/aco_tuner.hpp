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
    // Control threads
    std::vector<std::thread> workers;
    std::vector<std::unique_ptr<BaseSearch>> tasks;
    const int n;

    // Syncronization and output
    std::mutex mtx;
    std::ostream* out;

    // Domain for search
    ParameterSet startSearch, endSearch;

    // Cached information after fit
    ParameterSet bestParameters{};
    std::vector<int> bestPath;
    double bestScore{};

    // Method for a thread
    void process(int iTask, double limit, std::size_t n);

public:
    ACOTuner(const ParameterSet& startSearch, 
            const ParameterSet& endSearch,
            double step,
            const BaseStrategy& strategy,
            int n_jobs, std::ostream* out = nullptr);

    // Search best parameters
    void fit(double limit, std::size_t n);

    // Sets output stream for log details
    void setLogStream(std::ostream* out);

    // Returns best parameters after fit
    ParameterSet getBestParameters() const;

    // Returns best path after fit
    std::vector<int> getBestPath() const;

    // Returns best score after fit
    double getBestScore() const;
};