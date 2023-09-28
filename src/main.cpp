// C++ standard libraries
#include <cstdlib>
#include <iostream>

// Custom libraries
#include "point.hpp"
#include "graph_handler.hpp"
#include "acolony.hpp"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cout << argv[0] << " num_of_nodes alpha beta rho" << std::endl;
        exit(EXIT_FAILURE);
    }

    int nodesCount = std::atoi(argv[1]);
    double alpha = std::stod(argv[2]);
    double beta = std::stod(argv[3]);
    double rho = std::stod(argv[4]);

    std::vector<Point> graph;
    GraphHandler::getGraphRandom(graph, 1.0, std::atoi(argv[1]));
    GraphHandler::writeGraph(graph, "data/graph.csv");

    AColony colony{graph, alpha, beta, rho};
    colony.fit();
    colony.writeTSP("data/path.txt");

    return EXIT_SUCCESS;
}