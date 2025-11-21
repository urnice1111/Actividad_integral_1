#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::getline;
using std::stringstream;
using std::cin;

struct ip {
    int o1;
    int o2;
    int o3;
    int o4;
};

//Funcion auxiliar para convertir string a ip
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

//Sobrecarga de operador << para imprimir direccion ip
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
        cout << "Error: No se pudo abrir el archivo ordenado2.csv" << endl;
        return 1;
    }

    vector<pair<ip,int>> listaContada;
    string linea;
    string ipActual = "";
    int contador = 0;

    //Lectura de archivo ordenado22.csv para extraer ip destino
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


        //Condicion para la primera direccion IP
        if (ipActual == "") {
            ipActual = ipDestinoReal;
            contador = 1;
        }

        //Contador de frecuencia de IP
        else if (ipDestinoReal == ipActual) {
            contador++;
        }

        //Si ipDestinoReal != ipActual, almacena ipActual y el contador en el vector listaContada y actualiza los nuevos valores 
        else {
            listaContada.push_back({handleIp(ipActual), contador});
            ipActual = ipDestinoReal;
            contador = 1;
        }
    }

    //Condicion para la última dirección ip
    if (ipActual != "") {
        listaContada.push_back({handleIp(ipActual), contador});
    }

    //Convierte el vector listaContada en un heap
    std::make_heap(listaContada.begin(),listaContada.end());

    int tamañoInicial = 1;
    cout<<"----------------------------------------------"<<endl;
    cout<<"Busqueda de IP por más frecuencia de aparicion"<<endl;
    cout<<endl;
    cout<<"Ingrese la cantidad de IP's que desea visualizar: "<<endl;
    cin>>tamañoInicial;
    cout<<endl;

    //En caso de que el usuario ingrese un valor mayor a la cantidad de direcciones IP, ajusta el valor
    if(tamañoInicial>listaContada.size())
    tamañoInicial=listaContada.size();

    //Inicializacion de bucle para mostrar las IP
    for (int i=0; i<tamañoInicial;i++){ 
        pop_heap(listaContada.begin(),listaContada.end());
        cout<<"IP: "<<listaContada.back().first<<endl;
        cout<<"Frecuencia: "<<listaContada.back().second<<endl;
        cout<<endl;
        listaContada.pop_back();
    }

    return 0;
}
