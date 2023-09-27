#pragma once

// Custom libraries
#include "base_search.hpp"
#include "optimization/parameter_set.hpp"

class ExhaustiveSearch : public BaseSearch {
    static std::size_t id;
    std::size_t current_id;
public:
    ExhaustiveSearch(ParameterSet start, ParameterSet end, double step);

    virtual void search(double limit, std::size_t n) override;
};