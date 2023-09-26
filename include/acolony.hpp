#pragma once

// C++ standard libraries
#include <vector>
#include <string>

// Custom libraries
#include "point.hpp"

class AColony {
    // Graph
    const std::vector<Point>& graph;
    // Hyperparameters
    const double Q, K, alpha, beta, rho;
    // Size of graph
    std::size_t n;

    // Table for distance, attractiveness, and pheromones
    std::vector<std::vector<double>> distances;
    std::vector<std::vector<double>> etas;
    std::vector<std::vector<double>> pheromones;

    // Paths of current ants
    std::vector<std::vector<int>> paths;
    std::vector<int> bestPath;

    // Calculate all distances within given graph
    void setDistances();

    // Calculate attractiveness within given graph
    void setEtas();

    // Setup initial pheromones
    void setPheromones();

    // Get Euclidean distance
    double calculateDistance(const Point& p1, const Point& p2) const;

    // Get length of the path
    double calculateLength(const std::vector<int>& path) const;
public:
    AColony(const std::vector<Point>& graph, double alpha = 1.0, 
            double beta = 1.0, double rho = 0.2, 
            double Q = 1.0, double K = 1.0);

    // Calculate path for TSP
    void fit();

    // Write path to the file
    void writeTSP(const std::string& path) const;

    // Get best path
    std::vector<int> getBestPath() const;

    // Get best score
    double getBestScore() const;
};