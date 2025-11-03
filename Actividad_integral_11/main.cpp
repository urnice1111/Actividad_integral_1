/*

Descripción: Este programa lee un archivo CSV con registros de eventos de red, los ordena cronológicamente y permite buscar eventos a partir de una fecha específica.
Equipo 6
Integrantes:
-Emiliano Garcia Ramos A01753803
-Jorge Emiliano Loza Ayala A01754686
-Fernando Tovar Mejia A01666534

06/10/2025

*/

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::cin;

// Struct representing an IP address
struct ip {
    int o1;
    int o2;
    int o3;
    int o4;
};

struct Event {
  struct std::tm ts;
  struct ip ip_o;
  string port_o;
  string domain_o;
  struct ip ip_d;
  string port_d;
  string domain_d;
};

// Overload of << operator for struct ip
// If IP starts with 0 (o1 == 0) prints '-' instead
std::ostream& operator<<(std::ostream &os, const ip &i) {
    if(i.o1 == 0) {
        os << "-";
    } else {
       os << i.o1 << "." << i.o2 << "." << i.o3 << "." << i.o4;   
    }
    return os;
}

// Overload of << operator for struct Event
// Prints Event using same format as log
std::ostream& operator<<(std::ostream &os, const Event &e) {
    char dateOutput[20];
    strftime(dateOutput, 20, "%d-%m-%Y,%T", &e.ts);
    os << e.ip_o << "," << e.port_o << "," 
		<< e.domain_o << "," << e.ip_d << "," << e.port_d << "," << e.domain_d;
    return os;
}



// Overload of < operator for struct Event
// Will determine sorting order of Events
// e1 < e2 iff e1.ts < e2.ts
bool operator<(const Event &e1, const Event &e2) {

    std::tm ts1 = e1.ts;
    std::tm ts2 = e2.ts;

    // convierte la estructura tm a un valor de tipo time_t
    return std::mktime(&ts1) < std::mktime(&ts2);
}

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

int main() {

    std::ifstream file("equipo6.csv");
    std::string line;
    std::vector<Event> Events;
    


    while (std::getline(file, line)) {

        //esto se usa porque tenco mac os y cauando lee el csv al final tiene un \r, lo tenemos que quitar
        if (!line.empty() && line.back() == '\r') {
        line.pop_back();
        }
    
        if(line.empty()) {
        continue;
        }

        std::stringstream ss(line);
        std::string dateStr, timeStampTime, originIp, originPort,originDomain,ipDestino,puertoDestino,dominioDestino;
        Event e;


       //fecha
        std::getline(ss, dateStr, ',');
        std::stringstream date_ss(dateStr);
        std::string dd, mm, yyyy;
        std::getline(date_ss, dd, '-');
        std::getline(date_ss, mm, '-');
        std::getline(date_ss, yyyy, '-');
        e.ts.tm_mday = std::stoi(dd);
        e.ts.tm_mon  = std::stoi(mm) - 1;    
        e.ts.tm_year = std::stoi(yyyy) - 1900;

        //hora
        std::getline(ss, timeStampTime, ',');
        std::stringstream date_ss_time(timeStampTime);
        std::string h,m,s;
        std::getline(date_ss_time,h,':');
        std::getline(date_ss_time,m,':');
        std::getline(date_ss_time,s,':');
        e.ts.tm_hour = stoi(h);
        e.ts.tm_min = stoi(m);
        e.ts.tm_sec = stoi(s);

        //ip_adress_origen
        std::getline(ss,originIp,',');e.ip_o = handleIp(originIp); //se usa la funcion handleIp() para leer la linea y 
                                                                    //regrear un {} con los numeros serpardos por comas
        //puerto origen
        std::getline(ss,originPort,',');e.port_o = originPort;

        //dominio origen
        std::getline(ss,originDomain,',');e.domain_o = originDomain;

        //ip de destino
        std::getline(ss,ipDestino,','); e.ip_d = handleIp(ipDestino);
        
        //puerto destino

        std::getline(ss,puertoDestino,','); e.port_d = puertoDestino;
        std::getline(ss,dominioDestino,','); e.domain_d = dominioDestino;
        Events.push_back(e);
    }

    file.close();

    if (!Events.empty()){

    //ordena con sort
    sort(Events.begin(), Events.end());

    //escribe los elemntos de Events en el csv separados con comas
    std::ofstream myfile("ordenado.csv");
    int n = Events.size();
    char dateOutput[20];
    for(int i = 0; i < n; ++i) {
        strftime(dateOutput, 20, "%d-%m-%Y,%T", &Events[i].ts);
        myfile<<dateOutput;
        myfile<<',';
        myfile << Events[i];
        myfile << "\r";
    }}    

    int day, month, year;

    //El usuario ingresará la fecha de búsqueda
    cout<<"Busqueda de informacion a partir de fecha"<<endl;
    cout<<"Ingrese el dia (dd)"<<endl;
    cin>>day;
    cout<<"Ingrese el mes (mm)"<<endl;
    cin>>month;
    cout<<"Ingrese el año (yyyy)"<<endl;
    cin>>year;

    struct tm searchDate = {0};
    searchDate.tm_mday=day;
    searchDate.tm_mon=month-1;
    searchDate.tm_year=year-1900;

    time_t searchTime = mktime(&searchDate);

    //Busca el primer evento que sea mayor o igual a la fecha ingresada por el usuario
    //La función lambda compara las fechas convirtiendo la estructura tm a time_t
    auto founded = std::find_if(Events.begin(),Events.end(), 
    [searchTime](const Event &e){
        struct tm eventCopy = e.ts;
        time_t eventCopyTime=mktime(&eventCopy);
        return eventCopyTime>=searchTime;
    });

    //Si se encontró al menos un evento, se imprimen todos los eventos desde ese punto hasta el final
    if (founded!=Events.end()){
        cout<<"Eventos encontrados a partir de la fecha ingresada: "<<endl;
        for(auto it = founded; it != Events.end(); ++it){
            cout<<*it<<endl;
        }
    }

    return 0;
}

