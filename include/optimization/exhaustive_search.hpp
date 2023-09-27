#pragma once

// Custom libraries
#include "base_search.hpp"
#include "optimization/parameter_set.hpp"

class ExhaustiveSearch : public BaseSearch {
public:
    ExhaustiveSearch(ParameterSet start, ParameterSet end, double step);

    virtual void search() override;
};