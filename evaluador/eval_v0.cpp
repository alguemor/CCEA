#include <iostream> // entrada/salida estandar
#include <fstream>  // operaciones c/archivos
#include <string>   // manejo cadenas texto
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>
#include <random>
#include <tuple>
using namespace std;

void imprimirVector1D(const vector<int>& vector){
    cout << "[";
    for(size_t i = 0; i < vector.size(); i++) {
        cout << vector[i];
        if(i < vector.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void imprimirVector1Ddouble(const vector<double>& vector){
    cout << "[";
    for(size_t i = 0; i < vector.size(); i++) {
        cout << vector[i];
        if(i < vector.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void imprimirVector1DPair(const vector<pair<int,int>>& vector){
    cout << "[" << endl;
    for(size_t i = 0; i < vector.size(); i++){
        cout << i + 1 << ": (" 
            << vector[i].first << ", " 
            << vector[i].second << ")\n";
    }
    cout << "]" << endl;
}

void imprimirVector2D(const vector<vector<int>>& vector){
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

void imprimirVector2Ddouble(const vector<vector<double>>& vector){
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

int main(int argc, char* argv[]){
    string nombreDataset = argv[1];
    string nombreClusters = argv[2];
    ifstream archivoData(nombreDataset);
    ifstream archivoClusters(nombreClusters);
    
    // vector de clusters c/limites
    // numero de clusters
    int numClusters;
    archivoClusters >> numClusters;
    vector<int> limClusters;
    string linea;
    int lineasClusters = 0;
    while(getline(archivoClusters, linea)){
        lineasClusters++;
        if(lineasClusters != 1){
            int lim = stoi(linea);
            limClusters.push_back(lim);
        }else{
            continue;
        }
    }
    imprimirVector1D(limClusters);
    archivoClusters.close();
    
    // vector del dataset inicial
    // obtener los valores de las columnas y filas
    string valoresDataset;
    getline(archivoData, valoresDataset);
    stringstream ss(valoresDataset);
    vector<int> filascolumnas;
    int temporal;
    while(ss >> temporal){
        filascolumnas.push_back(temporal);
    }
    int filas = filascolumnas[0];
    int columnas = filascolumnas[1];

    // generar vector[f][c]
    vector<vector<int>> datos(filas, vector<int>(columnas,0));
    int contador = 0;
    while(getline(archivoData, linea)){
        if(contador < filas){
            istringstream ss(linea);
            for(int i = 0; i < columnas && !ss.eof(); i++){
                ss >> datos[contador][i];
            }
        }
        contador++;
    }
    imprimirVector2D(datos);
    archivoData.close();


    // generar dos puntos de manera aleatoria (coordenadas x, y) para cada cluster (4)
    // obtener los valores minimo y maximo para los clusters (normalizacion)
    int minimo = numeric_limits<int>::max();
    int maximo = numeric_limits<int>::min();
    for(const auto& fila : datos){
        if(!fila.empty()){
            auto [min_it, max_it] = minmax_element(fila.begin(), fila.end());
            minimo = min(minimo, *min_it);
            maximo = max(maximo, *max_it);
        }
    }
    random_device rd;
    mt19937 gen(rd()); // Motor Mersenne Twister - estandar
    uniform_int_distribution<int> rango(minimo, maximo); // rango
    vector<pair<int, int>> centrosClusters;
    for(int i = 0; i < numClusters; i++){
        int x = rango(gen);
        int y = rango(gen);
        pair<int, int> centro(x, y);
        centrosClusters.push_back(centro);
    }
    imprimirVector1DPair(centrosClusters);

    // matriz de distancias entre punto y centroides clusters
    vector<vector<double>> distancias(filas, vector<double>(numClusters,0));
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < numClusters; j++){
            int dx = datos[i][0] - centrosClusters[j].first;
            int dy = datos[i][1] - centrosClusters[j].second;
            distancias[i][j] = dx*dx + dy*dy;
        }
    }
    imprimirVector2Ddouble(distancias);

    // ordenamiento distancias
    vector<tuple<int, int, double>> todas_distancias;
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < numClusters; j++){
            todas_distancias.push_back(make_tuple(i, j, distancias[i][j]));
        }
    }
    sort(todas_distancias.begin(), todas_distancias.end(), [](const tuple<int, int, double>& a, const tuple<int, int, double>& b){
        return get<2>(a) < get<2>(b);
    });
    
    // asignacion
    vector<int> asignacion(filas, 0);
    vector<double> valorClusters(numClusters, 0);
    for(const auto& t : todas_distancias){
        int punto_id = get<0>(t);
        int centro_id = get<1>(t);
        if(asignacion[punto_id] != 0) continue;
        if(limClusters[centro_id] > 0){
            asignacion[punto_id] = centro_id;
            valorClusters[centro_id] += get<2>(todas_distancias[punto_id]);
            limClusters[centro_id]--;
        }
    }
    imprimirVector1D(asignacion);
    imprimirVector1Ddouble(valorClusters);

    // fitness global
    double fitness_global =accumulate(valorClusters.begin(), valorClusters.end(), 0.0);
    cout << "Fitness global: " << fitness_global << endl;
}