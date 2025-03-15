#ifndef problem_h
#define problem_h
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <numeric>
using namespace std;

class Problem{
private:
    // rutas archivos
    string Dataset;
    string Clusters;
    // almacenamiento datos
    int numClusters;
    vector<int> limClusters;
    vector<vector<int>> dataset;
    int points;
    int variables;
    // metodos auxiliares
    void loadClusters();
    void loadDataset();

public:
    // constructor y destructor
    Problem(const string& fileDataset, const string& fileClusters);
    ~Problem();
    // metodos almacenamiento
    int getNumClusters() const;
    const vector<int>& getLimClusters() const;
    const vector<vector<int>>& getDataset() const;
    int getPoints() const;
    int getVariables() const;
    // metodos impresion
    void printVector1D(const vector<int>& vector) const;
    void printVector2D(const vector<vector<int>>& vector) const;
    // metodo carga dataset
    void loadData();
    // metodos de evaluacion
    vector<vector<pair<int, int>>> calculateClusterCoordinates(const vector<int>& assignment) const;
    vector<double> calculateClusterValues(const vector<vector<pair<int, int>>>& coordinates) const;
    double calculateFitness(const vector<double>& clusterValues) const;
    // evaluacion completa
    double evaluateSolution(const vector<int>& assignment,
                            vector<vector<pair<int, int>>>& coordinates,
                            vector<double>& clusterValues) const;
};

#endif