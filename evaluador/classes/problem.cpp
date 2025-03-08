#include "problem.h"
#include <iostream>
#define pb push_back
using namespace std;

// constructor : inicializa rutas archivos
Problem::Problem(const string& fileDataset, const string& fileClusters)
    : Dataset(fileDataset), Clusters(fileClusters),
    numClusters(0), points(0), variables(0){
}
// destructor
Problem::~Problem(){    
}

void Problem::loadClusters(){
    ifstream fileClusters(Clusters);
    fileClusters >> numClusters;
    for(int i = 0; i < numClusters; i++){
        int lim;
        fileClusters >> lim;
        limClusters.pb(lim);
    }
    fileClusters.close();
    printVector1D(limClusters);
}

void Problem::loadDataset(){
    ifstream fileDataset(Dataset);
    fileDataset >> points;
    fileDataset >> variables;
    dataset.clear();
    dataset.resize(points, vector<int>(variables, 0));
    for(int i = 0; i < points; i++){
        for(int j = 0; j < variables; j++){
            fileDataset >> dataset[i][j];
        }
    }
    fileDataset.close();
    printVector2D(dataset);
}

void Problem::loadData(){
    loadClusters();
    loadDataset();
}

int Problem::getNumClusters() const{
    return numClusters;
}

const vector<int>& Problem::getLimClusters() const{
    return limClusters;
}

const vector<vector<int>>& Problem::getDataset() const{
    return dataset;
}

int Problem::getPoints() const{
    return points;
}

int Problem::getVariables() const{
    return variables;
}

void Problem::printVector1D(const vector<int>& vector) const{
    cout << "[";
    for(size_t i = 0; i < vector.size(); i++) {
        cout << vector[i];
        if(i < vector.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

void Problem::printVector2D(const vector<vector<int>>& vector) const{
    cout << "[" << endl;
    for(size_t i = 0; i < vector.size(); i++){
        cout << "  [";
        for(size_t j = 0; j < vector[i].size(); j++){
            cout << vector[i][j];
            if(j < vector[i].size() - 1){
                cout << ", ";
            }
        }
        cout << "]";
        if(i < vector.size() - 1){
            cout << ",";
        }
        cout << endl;
    }
    cout << "]" << endl;
}