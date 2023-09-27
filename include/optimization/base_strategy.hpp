#pragma once

// C++ standard libraries
#include <ostream>
#include <vector>
#include <memory>

// Custom libraries
#include "base_search.hpp"
#include "parameter_set.hpp"

class BaseStrategy {
public:
    // Split domain into n pieces
    virtual std::vector<std::unique_ptr<BaseSearch>> generateTasks(const ParameterSet& start, const ParameterSet& end, int n, 
                                                                std::mutex* mtx = nullptr, std::ostream* out = nullptr) const noexcept(false) = 0;
};