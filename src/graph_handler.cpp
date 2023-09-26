#include "graph_handler.hpp"

// C++ standard libraries
#include <fstream>
#include <random>

void GraphHandler::getGraph(std::vector<Point> &graph, const double limit, const std::size_t size) {
    // Random engine
    std::minstd_rand randEngine;
    // Distribution for generation
    std::uniform_real_distribution<double> dist(0, limit);

    // Fill graph with random coords
    graph.resize(size);
    for (auto& [x, y] : graph) {
        x = dist(randEngine);
        y = dist(randEngine);
    }
}