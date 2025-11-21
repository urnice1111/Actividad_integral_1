#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


struct ip {
    int o1;
    int o2;
    int o3;
    int o4;
};

ip handleIp(string& ip_str){
    ip res{};

    //Si el resultado leido con getline() es igual a "-" entonces la ip =  0.0.0.0
    if(ip_str=="-") return {0,0,0,0};
    std::stringstream ss(ip_str);
    string part;
    
    std::getline(ss, part, '.'); res.o1 = stoi(part);
    std::getline(ss, part, '.'); res.o2 = stoi(part);
    std::getline(ss, part, '.'); res.o3 = stoi(part);
    std::getline(ss, part, '.'); res.o4 = stoi(part);

    return res;
}

std::ostream& operator<<(std::ostream &os, const ip &i) {
    if(i.o1 == 0) {
        os << "-";
    } else {
       os << i.o1 << "." << i.o2 << "." << i.o3 << "." << i.o4;   
    }
    return os;
}




// TODO
// Overload of < operator for pair<ip, int>
// Will be used by make_heap to determine max value
// Should compare pairs based on their counts
bool operator<(const pair<ip, int> &p1, const pair<ip, int> &p2)
{
    return p1.second<p2.second;
}

int main() {
    std::ifstream archivoHeap("ordenado22.csv");

    if (!archivoHeap.is_open()) {
        cerr << "Error: No se pudo abrir el archivo ordenado2.csv" << endl;
        return 1;
    }

    vector<pair<ip,int>> listaContada;
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

            listaContada.push_back({handleIp(ipActual), contador});
            ipActual = ipDestinoReal;
            contador = 1;
        }
    }

    if (ipActual != "") {
        listaContada.push_back({handleIp(ipActual), contador});
    }

    std::make_heap(listaContada.begin(),listaContada.end());

    int tamañoInicial = 1;
    cout<<"----------------------------------------------"<<endl;
    cout<<"Busqueda de IP por más frecuencia de aparicion"<<endl;
    cout<<endl;
    cout<<"Ingrese la cantidad de IP's que desea visualizar: "<<endl;
    cin>>tamañoInicial;
    cout<<endl;

    if(tamañoInicial>listaContada.size())
    tamañoInicial=listaContada.size();

    for (int i=0; i<tamañoInicial;i++){ 
        pop_heap(listaContada.begin(),listaContada.end());
        cout<<"IP: "<<listaContada.back().first<<endl;
        cout<<"Frecuencia: "<<listaContada.back().second<<endl;
        cout<<endl;
        listaContada.pop_back();
    }



    return 0;
}
