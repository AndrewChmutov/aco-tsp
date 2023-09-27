#pragma once

// C++ standard libraries
#include <ostream>
#include <vector>
#include <memory>

// Custom libraries
#include "base_search.hpp"
#include "base_strategy.hpp"
#include "exhaustive_search.hpp"
#include "optimization/parameter_set.hpp"

class ExhaustiveStrategy : public BaseStrategy {
public:
    virtual std::vector<std::unique_ptr<BaseSearch>> generateTasks(const ParameterSet& start, const ParameterSet& end, double step,
                                                        int n, std::mutex* mtx = nullptr, std::ostream* out = nullptr) const noexcept(false) override;
};