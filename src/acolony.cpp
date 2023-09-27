#include "acolony.hpp"

// C++ standard libraries
#include <fstream>
#include <random>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>

AColony::AColony(const std::vector<Point>& graph, double alpha, 
                    double beta, double rho, double Q, double K) :
                        graph{graph}, alpha{alpha}, beta{beta}, rho{rho}, Q{Q}, K{K}, n{graph.size()} {

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
    std::ofstream file(path, std::ios_base::trunc);

    for (int i = 0; i < n - 1; i++) {
        file << bestPath[i] << '\n';
    }

    file << bestPath.back();
}

std::vector<int> AColony::getBestPath() const {
    return bestPath;
}

double AColony::getBestScore() const {
    return calculateLength(bestPath);
}


void AColony::fit() {
    using std::pow;

    // Random engine generator
    std::minstd_rand randEngine;
    double randomRoll{};
    int choice{};

    // Iterations
    int count{5'000};

    // Weights
    double sumOfWeights{};
    std::vector<double> weights;

    double tempTau{};
    // while iterations
    while (count--) {
        // for each ant
        for (int iAnt = 0; iAnt < n; iAnt++) {
            // Clear the weights
            weights.assign(n, 0.0);
            paths[iAnt][0] = iAnt;
            // Visit all cities
            for (int iVisit = 1; iVisit < n; iVisit++) {
                // Calculate weights
                for (int iNode = 0; iNode < n; iNode++) {
                    // Mark city ant can no longer visit
                    if (iNode == iAnt)
                        weights[iNode] = std::numeric_limits<double>::lowest();
                    // Avoid visited cities
                    else if (weights[iNode] >= 0.0)
                        weights[iNode] = pow(pheromones[iAnt][iNode], alpha) * pow(etas[iAnt][iNode], beta); 
                }

                // Random choice with weights //

                // Sum weights
                sumOfWeights = 0.0;
                for (const auto& weight : weights)
                    // Avoid visited nodes
                    if (weight > 0)
                        sumOfWeights += weight;

                // Random roll [0, sumOfWeights)
                randomRoll = std::uniform_real_distribution<double>(0.0, sumOfWeights)(randEngine);
                for (choice = 0; choice < n; choice++) {
                    if (randomRoll < weights[choice])
                        break;
                    else if (weights[choice] > 0.0)
                        randomRoll -= weights[choice];
                }

                paths[iAnt][iVisit] = choice;
                weights[choice] = std::numeric_limits<double>::lowest();
            }

            // Choose best path
            if (bestPath.empty() || (calculateLength(paths[iAnt]) < calculateLength(bestPath)))
                bestPath = paths[iAnt];
        }

        // Evaporation
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                pheromones[i][j] *= 1 - rho;


        // Ants leave pheromone
        for (int iAnt = 0; iAnt < n; iAnt++) {
            tempTau = Q / calculateLength(paths[iAnt]);

            for (int iVisit = 0; iVisit < n - 1; iVisit++) {
                pheromones[paths[iAnt][iVisit]][paths[iAnt][iVisit + 1]] += tempTau;
                pheromones[paths[iAnt][iVisit + 1]][paths[iAnt][iVisit]] += tempTau;
            }
            pheromones[paths[iAnt].front()][paths[iAnt].back()] += tempTau;
            pheromones[paths[iAnt].back()][paths[iAnt].front()] += tempTau;
        }

        // Highlight best solution
        for (int iVisit = 0; iVisit < n - 1; iVisit++) {
            pheromones[bestPath[iVisit]][bestPath[iVisit + 1]] += tempTau;
            pheromones[bestPath[iVisit + 1]][bestPath[iVisit]] += tempTau;
        }
        pheromones[bestPath.front()][bestPath.back()] += tempTau;
        pheromones[bestPath.back()][bestPath.front()] += tempTau;
    }
}