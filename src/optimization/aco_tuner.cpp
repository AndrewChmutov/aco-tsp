#include "optimization/aco_tuner.hpp"

// C++ standard libraries
#include <limits>
#include <vector>

// Custom libraries
#include "optimization/base_search.hpp"
#include "optimization/base_strategy.hpp"
#include "optimization/parameter_set.hpp"

ACOTuner::ACOTuner(const std::vector<Point>& graph,
                    const ParameterSet& startSearch,
                    const ParameterSet& endSearch,
                    const BaseStrategy& strategy,
                    int n_jobs, std::ostream* out) :
                graph{graph}, 
                startSearch{startSearch}, 
                endSearch{endSearch}, 
                n{n_jobs},
                out{out} {
    
    workers.reserve(n);
    tasks = strategy.generateTasks(startSearch, endSearch, n, &mtx, out);
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


void ACOTuner::fit() {
    // Initialize threads
    for (int i = 0; i < n; i++) {
        workers.push_back(std::thread{&BaseSearch::search, tasks[i].get()});
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