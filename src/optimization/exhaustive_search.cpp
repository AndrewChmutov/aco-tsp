#include "optimization/exhaustive_search.hpp"

// Custom libraries
#include "optimization/base_search.hpp"
#include "optimization/parameter_set.hpp"

ExhaustiveSearch::ExhaustiveSearch(ParameterSet start, ParameterSet end) : BaseSearch{start, end} {}


void ExhaustiveSearch::search() {}