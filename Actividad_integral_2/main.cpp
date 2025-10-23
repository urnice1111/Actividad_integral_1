#include <iostream>
#include <ctime>
#include <string>
#include "SortedLinkedList.h"

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
    return false;
}

// TODO
// Overload of < operator for event struct
// e1 < e2 iff e1.ip_d < e2.ip_d
// SortedLinkedList will use this operator to 
// determine an event's position in the list
// when inserting via 'add'
bool operator<(event &e1, event &e2) {
    return false;
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
}
