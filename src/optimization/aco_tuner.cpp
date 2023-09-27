#include "optimization/aco_tuner.hpp"

// C++ standard libraries
#include <limits>
#include <vector>

// Custom libraries
#include "optimization/base_search.hpp"
#include "optimization/base_strategy.hpp"
#include "optimization/parameter_set.hpp"

ACOTuner::ACOTuner(const ParameterSet& startSearch,
                    const ParameterSet& endSearch,
                    double step,
                    const BaseStrategy& strategy,
                    int n_jobs, std::ostream* out) :
                startSearch{startSearch}, 
                endSearch{endSearch}, 
                n_jobs{n_jobs},
                out{out} {
    
    workers.reserve(n_jobs);
    tasks = strategy.generateTasks(startSearch, endSearch, step, n_jobs, &mtx, out);
}


void ACOTuner::setLogStream(std::ostream *out) {
    this->out = out;

    for (auto& task : tasks)
        task->setLogStream(&mtx, out);
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


void ACOTuner::process(int iTask, double limit, std::size_t n_nodes) {
    tasks[iTask]->search(limit, n_nodes);
}
#include <iostream>

void ACOTuner::fit(double limit, std::size_t n_nodes) {
    // Initialize threads
    for (int i = 0; i < n_jobs; i++) {
        workers.push_back(std::thread{&ACOTuner::process, this, i, limit, n_nodes});
    }

    // Join threads
    for (auto& worker : workers) {
        if (worker.joinable())
            worker.join();
    }

    // Save best results
    bestScore = std::numeric_limits<double>::max();
    double tempScore{};
    for (const auto& task : tasks) {
        tempScore = task->getBestScore();
        if (tempScore < bestScore) {
            bestScore= tempScore;
            bestParameters = task->getBestParameters();
            bestPath = task->getBestPath();
        }
    }
}