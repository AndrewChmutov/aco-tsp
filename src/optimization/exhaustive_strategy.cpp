#include "optimization/exhaustive_strategy.hpp"

// C++ standard libraries
#include <stdexcept>
#include <vector>
#include <memory>

// Custom libraries
#include "optimization/base_search.hpp"
#include "optimization/exhaustive_search.hpp"
#include "optimization/parameter_set.hpp"

std::vector<std::unique_ptr<BaseSearch>> ExhaustiveStrategy::generateTasks(const ParameterSet &start, const ParameterSet &end, double step, int n,
                                                                    std::mutex* mtx, std::ostream* out) const noexcept(false) {
    // Check if domain is given correctly
    if (start.Q > end.Q || 
            start.K > end.K ||
            start.alpha > end.alpha ||
            start.beta > end.beta ||
            start.rho > end.rho)
        throw std::invalid_argument("Invalid domain.");
    
    // Vector to return
    std::vector<std::unique_ptr<BaseSearch>> tasks;
    tasks.reserve(n);

    // Value to changed
    double alphaDelta = (end.alpha - start.alpha) / n;

    // Temp values
    ParameterSet tempStart{1.0, 1.0, 0.0, 0.0, 0.0};
    ParameterSet tempEnd{1.0, 1.0, 5.0, 5.0, 1.0};

    // Break domain by alpha axis
    for (int i = 0; i < n; i++) {
        tempStart.alpha = alphaDelta * i;
        tempEnd.alpha = alphaDelta * (i + 1);
        tasks.push_back(std::make_unique<ExhaustiveSearch>(tempStart, tempEnd, step));
        tasks.back()->setLogStream(mtx, out);
    }

    return tasks;
}