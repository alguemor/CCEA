#include "solution.h"
#include "util.h"
#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

Solution::Solution(Problem& prob) : problem(prob), fitness(0.0){
    int numClusters = problem.getNumClusters();
    int numPoints = problem.getPoints();
    distances.resize(numPoints, vector<double>(numClusters, 0.0));
    assignment.resize(numPoints, 0);
    clusterLimits = problem.getLimClusters();
    clusterValues.resize(numClusters, 0.0);
    clusterCoordinates.resize(numClusters);
}

Solution::~Solution(){
}

void Solution::calculateDistances(){
    const auto& dataset = problem.getDataset();
    int numPoints = problem.getPoints();
    int numClusters = problem.getNumClusters();

    for(int i = 0; i < numPoints; i++){
        for(int j = 0; j < numClusters; j++){
            int dx = dataset[i][0] - clusterCenters[j].first;
            int dy = dataset[i][1] - clusterCenters[j].second;
            distances[i][j] = sqrt(dx*dx + dy*dy);
        }
    }
}

void Solution::sortDistances(){
    int numPoints = problem.getPoints();
    int numClusters = problem.getNumClusters();

    allDistances.clear();
    for(int i = 0; i < numPoints; i++){
        for(int j = 0; j < numClusters; j++){
            allDistances.push_back(make_tuple(i, j, distances[i][j]));
        }
    }

    sort(allDistances.begin(), allDistances.end(), [](const auto& a, const auto& b){
        return std::get<2>(a) < std::get<2>(b);
    });
}

void Solution::greedy(){
    int numPoints = problem.getPoints();

    fill(assignment.begin(), assignment.end(), 0);
    clusterLimits = problem.getLimClusters();

    if(allDistances.empty()){
        sortDistances();
    }

    for(const auto& dist_tuple : allDistances){
        int point_id = std::get<0>(dist_tuple);
        int center_id = std::get<1>(dist_tuple);
        if(assignment[point_id] != 0) continue;
        if(clusterLimits[center_id] > 0){
            assignment[point_id] = center_id;
            clusterLimits[center_id]--;
        }
    }
}

vector<vector<pair<int, int>>> Solution::getClusterCoordinates(){
    const auto& dataset = problem.getDataset();
    int numClusters = problem.getNumClusters();
    vector<vector<pair<int, int>>> coordinates(numClusters);
    
    for(int i = 0; i< assignment.size(); i++){
        int cluster = assignment[i];
        if(cluster >= 0 && cluster < numClusters){
            int x = dataset[i][0];
            int y = dataset[i][1];
            coordinates[cluster].push_back(make_pair(x, y));
        }
    }
    
    return coordinates;
}

vector<double> Solution::getClusterValues(const vector<vector<pair<int, int>>>& coordinates){
    int numClusters = problem.getNumClusters();
    vector<double> values(numClusters, 0.0);
    
    for(int c = 0; c < numClusters; c++){
        double sumDistances = 0.0;
        for(int i = 0; i < coordinates[c].size(); i++){
            for(int j = i + 1; j < coordinates[c].size(); j++){
                int x1 = coordinates[c][i].first;
                int y1 = coordinates[c][i].second;
                int x2 = coordinates[c][j].first;
                int y2 = coordinates[c][j].second;
                int dx = x2 - x1;
                int dy = y2 - y1;
                double distance = sqrt(dx*dx + dy*dy);
                sumDistances += distance;
            }
        }
        values[c] = sumDistances / coordinates[c].size();
    }
    return values;
}

double Solution::calculateFitness(const vector<double>& values){
    return accumulate(values.begin(), values.end(), 0.0);
}

void Solution::solveGreedy(){
    Util util(problem, *this); // crea instancia de Util
    clusterCenters = util.generateRandomCenters(problem.getNumClusters());

    calculateDistances();
    sortDistances();
    greedy();

    clusterCoordinates = getClusterCoordinates();
    clusterValues = getClusterValues(clusterCoordinates);
    fitness = calculateFitness(clusterValues);

    util.printClusterCenters();
    util.printAssignment();
    util.printClusterCoordinates();
    util.printClusterValues();
    util.printFitness();
}

const vector<pair<int, int>>& Solution::getClusterCenters() const{
    return clusterCenters;
}

const vector<vector<pair<int, int>>>& Solution::getClusterCoordinates() const{
    return clusterCoordinates;
}

const vector<int>& Solution::getAssignment() const{
    return assignment;
}

const vector<double>& Solution::getClusterValues() const{
    return clusterValues;
}

double Solution::getFitness() const{
    return fitness;
}