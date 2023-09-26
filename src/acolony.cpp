#include "acolony.hpp"

// C++ standard libraries
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>

AColony::AColony(const std::vector<Point>& graph, double alpha, 
                    double beta, double rho, double Q, double K) :
                        graph{graph}, alpha{alpha}, beta{beta}, rho{rho}, Q{Q}, K{K} {

    setDistances();
    setEtas();
    setPheromones();

    paths.resize(n, std::vector<int>(n));
}


void AColony::setDistances() {
    // Allocate memory
    distances = std::vector<std::vector<double>>(n, std::vector<double>(n));
    double tempDistance{};

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // Ant cannot perform no move
            if (i == j) {
                distances[i][j] = std::numeric_limits<double>::max();
                continue;
            }

            // Set distances
            // To and from distance is the same
            tempDistance = calculateDistance(graph[i], graph[j]);
            distances[i][j] = tempDistance;
            distances[j][i] = tempDistance;
        }
    }
}


void AColony::setEtas() {
    // Allocate memory
    etas = std::vector<std::vector<double>>(n, std::vector<double>(n));
    double tempEta{};

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // No attractiveness: ant cannot perform no meve
            if (i == j)
                etas[i][j] = 0.0;

            // Write attractiveness
            tempEta = K / distances[i][j];
            etas[i][j] = tempEta;
            etas[j][i] = tempEta;
        }
    }
}


void AColony::setPheromones() {
    // Allocate memory
    pheromones = std::vector<std::vector<double>>(n, std::vector<double>(n, 0.1));
}


double AColony::calculateDistance(const Point& p1, const Point& p2) const {
    using std::pow;
    using std::sqrt;
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}


double AColony::calculateLength(const std::vector<int>& path) const {
    double length{};

    for (int i = 0; i < n - 1; i++)
        length += distances[path[i]][path[i + 1]];

    // Return to the initial position
    length += distances[path.front()][path.back()];

    return length;
}


void AColony::writeTSP(const std::string& path) const {
    std::ofstream file(path);

    for (int i = 0; i < n - 1; i++) {
        file << path[i] << '\n';
    }

    file << path.back();
}

std::vector<int> AColony::getBestPath() const {
    return bestPath;
}

double AColony::getBestScore() const {
    return calculateLength(bestPath);
}