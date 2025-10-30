#include <iostream>
#include <ctime>
#include <string>
#include "SortedLinkedList.h"
#include <fstream>
#include <sstream>

using std::cout;
using std::cin;
using std::string;


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
    os << date_output << "," << e.ip_o << "," << e.port_o << "," 
		<< e.domain_o << "," << e.ip_d << "," << e.port_d << "," 
		<< e.domain_d;
    return os;
}

// TODO
// Overload of < operator for struct ip
// ip1 < ip2 if ip1.o1 < ip2.o1
// else if ip1.o1 == ip2.o1, then ip1 < ip2 if ip1.02 < ip2.o2
// and so on
bool operator<(ip &ip1, ip &ip2)
{
    if(ip1.o1<ip2.o1){
        return true;
    }
    else if(ip1.o1==ip2.o1){
        return ip1.o2 < ip2.o2;
    } else{
        return false;
    }
}

// TODO
// Overload of < operator for event struct
// e1 < e2 iff e1.ip_d < e2.ip_d
// SortedLinkedList will use this operator to 
// determine an event's position in the list
// when inserting via 'add'-
bool operator<(event &e1, event &e2) {
    if(e1.ip_d<e2.ip_d){
        return true;
    } else {
        return false;
    }

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

// TODO
int main() {
    // Create an empty SortedLinkedList
    // Open the log
        // For each line create an event
        // Add the event to the list
    // When done, the SLL will contain all
    // events sorted by destination ip

    // Save SLL contents to a file

    // Ask the user for a destination ip
    // Define a lambda that recieves an event
    // and compares it to the ip provided by the user
    // Use the find method to obtain an iterator
    // to the first element of the list with the
    // destination ip
    // Print out all events with the same ip
    std::ifstream file("equipo6.csv");
    string line;
    SortedLinkedList<event> sll;


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
        event e;


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
        sll.add(e);
    }

    
    file.close();
    
    
    sll.print();





   


}
