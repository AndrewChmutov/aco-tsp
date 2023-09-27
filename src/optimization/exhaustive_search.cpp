#include "optimization/exhaustive_search.hpp"

// Custom libraries
#include "optimization/base_search.hpp"
#include "optimization/parameter_set.hpp"

ExhaustiveSearch::ExhaustiveSearch(ParameterSet start, ParameterSet end, double step) : BaseSearch{start, end, step} {}


void ExhaustiveSearch::search() {}