#pragma once

// C++ standard libraries
#include <vector>
#include <random>
#include <string>

// Custom libraries
#include "point.hpp"

class GraphHandler {
public:
    // Modifies the vector given in parameters
    // Limits the random values for X and Y axes
    static void getGraph(std::vector<Point>& graph, const double limit, const std::size_t size);

    // Get graph randomly each time
    static void getGraphRandom(std::vector<Point>& graph, const double limit, const std::size_t size);

    // Write graph to a file
    static void writeGraph(const std::vector<Point>& graph, const std::string& path);

    // Read graph from a file
    static void readGraph(std::vector<Point>& graph, const std::string& path);
};