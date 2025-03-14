#include "util.h"
#include "solution.h"
#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

Util::Util(const Problem& prob, const Solution& sol) : problem(prob), solution(sol), generator(random_device()()){
    // inicializar generador aleatorio
}

Util::~Util(){

}

vector<pair<int, int>> Util::generateRandomCenters(int numClusters) const{
    const auto& dataset = problem.getDataset();
    int minValue = numeric_limits<int>::max();
    int maxValue = numeric_limits<int>::min();
    for(const auto& point : dataset){
        if(!point.empty()){
            auto min_it = min_element(point.begin(), point.end());
            auto max_it = max_element(point.begin(), point.end());
            if(min_it != point.end()) minValue = min(minValue, *min_it);
            if(max_it != point.end()) maxValue = max(maxValue, *max_it);
        }
    }

    uniform_int_distribution<int> range(minValue, maxValue);

    vector<pair<int, int>> clusterCenters;
    for(int i = 0; i < numClusters; i++){
        int x = range(generator);
        int y = range(generator);
        clusterCenters.push_back(make_pair(x, y));
    }

    return clusterCenters;
}

void Util::printClusterCenters() const {
    const auto& centers = solution.getClusterCenters();
    cout << "Centros de clusters:" << endl;
    for (int i = 0; i < centers.size(); i++) {
        cout << "  Cluster " << i << ": (" 
             << centers[i].first << ", " 
             << centers[i].second << ")" << endl;
    }
}

void Util::printAssignment() const {
    const auto& assignment = solution.getAssignment();
    int numClusters = problem.getNumClusters();
    cout << "Asignación de puntos a clusters:" << endl;
    // Contar puntos por cluster
    vector<int> count(numClusters, 0);
    for (int c : assignment) {
        if (c >= 0 && c < numClusters) {
            count[c]++;
        }
    }
    for (int i = 0; i < count.size(); i++) {
        cout << "  Cluster " << i << ": " << count[i] << " puntos" << endl;
    }
}

void Util::printClusterCoordinates() const {
    const auto& coordinates = solution.getClusterCoordinates();
    cout << "Puntos por cluster:" << endl;
    for (int c = 0; c < coordinates.size(); c++) {
        cout << "  Cluster " << c << " (" << coordinates[c].size() << " puntos):" << endl;  
        // Limitar la salida si hay muchos puntos
        const int max_points_to_show = 5;
        for (int i = 0; i < min(max_points_to_show, (int)coordinates[c].size()); i++) {
            cout << "    (" << coordinates[c][i].first << ", " 
                 << coordinates[c][i].second << ")" << endl;
        }
        if (coordinates[c].size() > max_points_to_show) {
            cout << "    ... y " << (coordinates[c].size() - max_points_to_show) 
                 << " puntos más" << endl;
        }
    }
}

void Util::printClusterValues() const {
    const auto& values = solution.getClusterValues();
    cout << "Valores de fitness por cluster:" << endl;
    for (int i = 0; i < values.size(); i++) {
        cout << "  Cluster " << i << ": " << values[i] << endl;
    }
}

void Util::printFitness() const {
    const auto& fitness = solution.getFitness();
    cout << "Fitness global: " << fitness << endl;
}