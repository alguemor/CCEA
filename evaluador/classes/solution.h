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
    vector<pair<int, int>> clusterCenters;
    vector<vector<double>> distances;
    vector<int> assignment;
    vector<tuple<int, int, double>> allDistances;
    vector<int> clusterLimits;
    vector<vector<pair<int, int>>> clusterCoordinates;
    vector<double> clusterValues;
    double fitness;

    void initializeRandomCenters();
    void calculateDistances();
    void sortDistances();

public:
    Solution(Problem& prob);
    ~Solution();

    void greedy();
    vector<vector<pair<int, int>>> getClusterCoordinates();
    vector<double> getClusterValues(const vector<vector<pair<int, int>>>& coordinates);
    double calculateFitness(const vector<double>& clusters);

    void solveGreedy();

    const vector<pair<int, int>>& getClusterCenters() const;
    const vector<int>& getAssignment() const;
    const vector<double>& getClusterValues() const;
    double getFitness() const;

    void printClusterCenters() const;
    void printAssignment() const;
    void printClusterCoordinates() const;
    void printClusterValues() const;
    void printFitness() const;
};

#endif