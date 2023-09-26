#include "graph_handler.hpp"

// C++ standard libraries
#include <fstream>
#include <random>
#include <sstream>

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


void GraphHandler::writeGraph(const std::vector<Point> &graph, const std::string &path) {
    // Output file
    std::ofstream file(path);

    // Headers
    file << "x,y\n";

    for (const auto& [x, y] : graph)
        file << x << ',' << y << '\n';
}


void GraphHandler::readGraph(std::vector<Point>& graph, const std::string& path) {
    // Input file
    std::ifstream file(path);
    // Buffer;
    std::string line, token;
    std::stringstream ss;
    Point p;

    // Skip headers
    std::getline(file, line);
    while (std::getline(file, line)) {
        // Get stream of the line
        ss.clear();
        ss << line;

        // Go until comma
        std::getline(ss, token, ',');
        p.x = std::stod(token);

        // Go until newline
        std::getline(ss, token, '\n');
        p.y = std::stod(token);

        // Add new point
        graph.push_back(p);
    }
}