// C++ standard libraries
#include <cstdlib>
#include <iostream>

// Custom libraries
#include "point.hpp"
#include "graph_handler.hpp"
#include "acolony.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << argv[0] << " num_of_nodes" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<Point> graph;
    GraphHandler::getGraph(graph, 1.0, std::atoi(argv[1]));
    GraphHandler::writeGraph(graph, "data/graph.csv");

    AColony colony{graph, 1.5, 4.2, 0.8};
    colony.fit();
    colony.writeTSP("data/path.txt");

    return EXIT_SUCCESS;
}