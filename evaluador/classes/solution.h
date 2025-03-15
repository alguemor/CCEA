#ifndef solution_h
#define solution_h
#include "problem.h"
#include <vector>
#include <tuple>
#include <utility>
#include <random>
#include <numeric>
using namespace std;

class Solution{
private:
    Problem& problem;
    vector<vector<double>> distances;
    vector<tuple<int, int, double>> allDistances;
    vector<int> clusterLimits;
    bool clusterCoordinatesUpdated; // flag coordenadas actualizadas

    void calculateDistances();
    void sortDistances();
    void calculateClusterCoordinates();

public:
    Solution(Problem& prob);
    ~Solution();

    vector<pair<int, int>> clusterCenters;
    vector<int> assignment;
    // cache en Solution, logica en Problem
    vector<vector<pair<int, int>>> clusterCoordinates;
    vector<double> clusterValues;
    double fitness;

    void greedy();
    const vector<vector<pair<int, int>>>& getClusterCoordinates(); // flag
    // metodo actualizar valores evaluacion
    void updateEvaluation();
    void solveGreedy();
    // getters
    const vector<pair<int, int>>& getClusterCenters() const;
    const vector<vector<pair<int, int>>>& getClusterCoordinates() const;
    const vector<int>& getAssignment() const;
    const vector<double>& getClusterValues() const;
    double getFitness() const;
};

#endif