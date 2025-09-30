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

// Struct representing an IP address
struct ip {
    int o1;
    int o2;
    int o3;
    int o4;
};

// Struct representing a log event (connection between two nodes)
// ts: Date-time of the event as ctime's tm (check docs: https://cplusplus.com/reference/ctime/tm/)
// ip_o: IP of the origin node
// port_o: Port of the origin node
// domain_o: Domain of the origin node
// ip_d: IP of the destination node
// port_d: Port of the destination node
// domain_d: Domain of the destination node
struct event {
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

// Overload of << operator for struct event
// Prints event using same format as log
std::ostream& operator<<(std::ostream &os, const event &e) {
    char date_output[20];
    strftime(date_output, 20, "%d-%m-%Y,%T", &e.ts);
    os << e.ip_o << "," << e.port_o << "," 
		<< e.domain_o << "," << e.ip_d << "," << e.port_d << "," << e.domain_d;
    return os;

}



// Overload of < operator for struct event
// Will determine sorting order of events
// e1 < e2 iff e1.ts < e2.ts
bool operator<(const event &e1, const event &e2) {
    return false;
}

ip handle_ip(string& ip_str){
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
    std::vector<event> events;
    


    while (std::getline(file, line)) {

        //esto se usa porque tenco mac os y cauando lee el csv al final tiene un \r, lo tenemos que quitar
        if (!line.empty() && line.back() == '\r') {
        line.pop_back();
        }
    
        if(line.empty()) {
        continue;
        }

        std::stringstream ss(line);
        std::string date_str, time_stamp_time, origin_ip, 
        origin_port,origin_domain, ip_detino,puerto_destino,dominio_destino;
        event e;


       //fecha
        std::getline(ss, date_str, ',');
        std::stringstream date_ss(date_str);
        std::string dd, mm, yyyy;
        std::getline(date_ss, dd, '-');
        std::getline(date_ss, mm, '-');
        std::getline(date_ss, yyyy, '-');
        e.ts.tm_mday = std::stoi(dd);
        e.ts.tm_mon  = std::stoi(mm) - 1;    
        e.ts.tm_year = std::stoi(yyyy) - 1900;

        //hora
        std::getline(ss, time_stamp_time, ',');
        std::stringstream date_ss_time(time_stamp_time);
        std::string h,m,s;
        std::getline(date_ss_time,h,':');
        std::getline(date_ss_time,m,':');
        std::getline(date_ss_time,s,':');
        e.ts.tm_hour = stoi(h);
        e.ts.tm_min = stoi(m);
        e.ts.tm_sec = stoi(s);

        //ip_adress_origen
        std::getline(ss,origin_ip,',');e.ip_o = handle_ip(origin_ip); //se usa la funcion handle_ip() para leer la linea y 
                                                                    //regrear un {} con los numeros serpardos por comas
        //puerto origen
        std::getline(ss,origin_port,',');e.port_o = origin_port;

        //dominio origen
        std::getline(ss,origin_domain,',');e.domain_o = origin_domain;

        //ip de destino
        std::getline(ss,ip_detino,','); e.ip_d = handle_ip(ip_detino);
        
        //puerto destino

        std::getline(ss,puerto_destino,','); e.port_d = puerto_destino;
        std::getline(ss,dominio_destino,','); e.domain_d = dominio_destino;
        events.push_back(e);
    }
    file.close();
    if(!events.empty()) {cout<<events[0];}
    // if(!events.empty()){
        

        // <<"Fecha: "<<events[0].ts.tm_mday<<"-"<<events[0].ts.tm_mon<<"-"<<events[0].ts.tm_mday<<"\n"
        // <<"Time: "<<events[0].ts.tm_hour<<":"<<events[0].ts.tm_min<<":"<<events[0].ts.tm_sec<<"\n"
        // <<"Direccion ip de origen: "<<events[0].ip_o<<"\n"
        // <<"Puerto de origen: "<<events[0].port_o<<"\n"
        // <<"Dominio de origen: "<<events[0].domain_o<<"\n"
        // <<"Direcction ip de destino: "<<events[0].ip_d<<"\n"
        // <<"Puerto de destino: "<<events[0].port_d<<"\n"
        // <<"Dominio de destino: "<<events[0].domain_d<<"\n";
    

    
    
    
    return 0;
    }    

