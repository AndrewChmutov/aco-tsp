// C++ standard libraries
#include <cstdlib>
#include <iostream>

// Custom libraries
#include "point.hpp"
#include "graph_handler.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << argv[0] << " num_of_nodes" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<Point> graph;
    GraphHandler::getGraph(graph, 1.0, std::atoi(argv[1]));

    for (auto& [x, y] : graph) {
        std::cout << x << ' ' << y << '\n';
    }

    GraphHandler::writeGraph(graph, "data/graph.csv");

    return EXIT_SUCCESS;
}