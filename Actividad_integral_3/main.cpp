#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    std::ifstream archivoHeap("ordenado22.csv");

    if (!archivoHeap.is_open()) {
        cerr << "Error: No se pudo abrir el archivo ordenado2.csv" << endl;
        return 1;
    }

    vector<pair<string,int>> listaContada;
    string linea;
    string ipActual = "";
    int contador = 0;

    while (std::getline(archivoHeap, linea)) {
        if (!linea.empty() && linea.back() == '\r') {
            linea.pop_back();
        }
        if(linea.empty()) continue;

        stringstream ss(linea);
        string basura; 
        string ipDestinoReal;

        getline(ss, basura, ','); 
        getline(ss, basura, ','); 
        getline(ss, basura, ','); 
        getline(ss, basura, ','); 
        getline(ss, basura, ','); 
        getline(ss, basura, ','); 
        getline(ss, basura, ','); 
        
        getline(ss, ipDestinoReal, ','); 

        if (ipActual == "") {
            ipActual = ipDestinoReal;
            contador = 1;
        }
        else if (ipDestinoReal == ipActual) {
            contador++;
        }
        else {
            listaContada.push_back({ipActual, contador});
            ipActual = ipDestinoReal;
            contador = 1;
        }
    }

    if (ipActual != "") {
        listaContada.push_back({ipActual, contador});
    }

    std::cout << "Tamaño de lista final: " << listaContada.size() << endl;

    for(int i = 0; i < min((int)listaContada.size(), 5); i++) {
        cout << listaContada[i].first << ": " << listaContada[i].second << endl;
    }

    return 0;
}
