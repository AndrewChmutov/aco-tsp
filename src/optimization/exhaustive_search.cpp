#include "optimization/exhaustive_search.hpp"

// C++ standard libraries
#include <limits>
#include <mutex>
#include <iomanip>

// Custom libraries
#include "optimization/base_search.hpp"
#include "optimization/parameter_set.hpp"
#include "graph_handler.hpp"
#include "acolony.hpp"

ExhaustiveSearch::ExhaustiveSearch(ParameterSet start, ParameterSet end, double step) : BaseSearch{start, end, step} { current_id = id++; }

std::size_t ExhaustiveSearch::id = 0;

void ExhaustiveSearch::search(double limit, std::size_t nodesCount) {
    std::vector<Point> graph;
    double tempResult{};
    bestScore = std::numeric_limits<double>::max();

    for (double a = startSearch.alpha; a < endSearch.alpha; a += step) {
        for (double b = startSearch.beta; b < endSearch.beta; b += step) {
            for (double p = startSearch.rho; p < endSearch.rho; p += step) {
                GraphHandler::getGraphRandom(graph, limit, nodesCount);
                AColony colony(graph, a, b, p);
                
                colony.fit();
                tempResult = colony.getBestScore();

                if (tempResult < bestScore) {
                    bestScore = tempResult;
                    bestPath = colony.getBestPath();
                    bestParameters = {startSearch.Q, startSearch.K, a, b, p};
                }
            }
        }

        if (out) {
            std::lock_guard<std::mutex> lock{*mtx};
            *out << std::setprecision(2) << "-----id " << current_id << "-----" <<
                    "\nQ:\t" << bestParameters.Q <<
                    "\nK:\t" << bestParameters.K <<
                    "\nalpha\t" << bestParameters.alpha <<
                    "\nbeta:\t" << bestParameters.beta <<
                    "\nrho:\t" << bestParameters.rho <<
                    "\nresult:\t" << bestScore << '\n';
        }
    }

    if (out) {
        std::lock_guard<std::mutex> lock{*mtx};
        *out << std::setprecision(2) << "*****id " << current_id << "*****" <<
                "\nBest result this thread:\t" << bestScore <<
                "\nQ:\t" << bestParameters.Q <<
                "\nK:\t" << bestParameters.K <<
                "\nalpha\t" << bestParameters.alpha <<
                "\nbeta:\t" << bestParameters.beta <<
                "\nrho:\t" << bestParameters.rho << '\n';
    }
}