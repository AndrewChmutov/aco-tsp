// C++ standard libraries
#include <cstdlib>
#include <iostream>

// Custom libraries
#include "point.hpp"
#include "graph_handler.hpp"
#include "acolony.hpp"
#include "optimization/parameter_set.hpp"
#include "optimization/aco_tuner.hpp"
#include "optimization/exhaustive_strategy.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << argv[0] << " num_of_nodes" << std::endl;
        exit(EXIT_FAILURE);
    }
    int nodesCount = std::atoi(argv[1]);
    int threadCount = 8;

    // std::vector<Point> graph;
    // GraphHandler::getGraph(graph, 1.0, std::atoi(argv[1]));
    // GraphHandler::writeGraph(graph, "data/graph.csv");

    // AColony colony{graph, 1.5, 4.2, 0.8};
    // colony.fit();
    // colony.writeTSP("data/path.txt");

    ParameterSet startSearch {1.0, 1.0, 0.1, 0.1, 0.1};
    ParameterSet endSearch {1.0, 1.0, 5.0, 5.0, 1.0};

    ACOTuner tuner{startSearch, endSearch, 0.1, ExhaustiveStrategy(), 8};
    tuner.setLogStream(&std::cout);

    tuner.fit(1.0, nodesCount);

    ParameterSet best = tuner.getBestParameters();

    std::cout << "\n\n\n=====AntColonyTuner: " << nodesCount << " nodes=====\n" <<
            "\nBest result:\t" << tuner.getBestScore() <<
            "\nQ:\t" << best.Q <<
            "\nK:\t" << best.K <<
            "\nalpha\t" << best.alpha <<
            "\nbeta:\t" << best.beta <<
            "\nrho:\t" << best.rho << '\n';

    return EXIT_SUCCESS;
}