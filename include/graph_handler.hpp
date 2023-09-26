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

    static void writeGraph(const std::vector<Point>& graph, const std::string& path);

    static void readGraph(std::vector<Point>& graph, const std::string& path);
};