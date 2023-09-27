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
                n{n_jobs},
                out{out} {
    
    workers.reserve(n);
    tasks = strategy.generateTasks(startSearch, endSearch, step, n, &mtx, out);
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


void ACOTuner::process(int iTask, double limit, std::size_t n) {
    tasks[iTask]->search(limit, n);
}


void ACOTuner::fit(double limit, std::size_t n) {
    // Initialize threads
    for (int i = 0; i < n; i++) {
        workers.push_back(std::thread{&ACOTuner::process, this, i, limit, n});
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