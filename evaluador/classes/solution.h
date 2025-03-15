#ifndef solution_h
#define solution_h
#include "problem.h"
#include <vector>
#include <tuple>
#include <utility>
#include <random>
#include <cmath>
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
    vector<vector<pair<int, int>>> clusterCoordinates;
    vector<double> clusterValues;
    double fitness;

    void greedy();
    const vector<vector<pair<int, int>>>& getClusterCoordinates(); // flag
    vector<double> getClusterValues(const vector<vector<pair<int, int>>>& coordinates);
    double calculateFitness(const vector<double>& clusters);

    void solveGreedy();

    const vector<pair<int, int>>& getClusterCenters() const;
    const vector<vector<pair<int, int>>>& getClusterCoordinates() const;
    const vector<int>& getAssignment() const;
    const vector<double>& getClusterValues() const;
    double getFitness() const;
};

#endif