/* 
Emiliano Garcia Ramos A01753803
Fernando Tovar Mejia A
*/

#include "Digraph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(){
    std::ifstream file("ordenado22.csv");  
    std::string line;
    
    Digraph<std::string> graph;
    
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        // Lee las 6 columnas del archivo. 
        // La 3 es la ip de origen y la 6 es la ip de destino.
        while(std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if(tokens.size() >= 6) {
            std::string ip_origen = tokens[2];   // Columna 3
            std::string ip_destino = tokens[5];  // Columna 6
            
            // No hace falta logica aqui porque verifica si el nodo ya existe y si no, lo agrega en el Digraph.h
            graph.add_edge(ip_origen, ip_destino);
        }
    }
    // En el achivo, hay 363 ips diferentes, asi que si se cuentan cuantos nodos hay, deberia ser tambien 363   
    int num_nodos = graph.get_node_count();
    std::cout << "Total de nodos en el grafo: " << num_nodos << std::endl;
    
    std::string max_out_degree_ip = graph.get_max_out_degree_node();
    
    std::cout << "IP con mayor grado de salida: " << max_out_degree_ip << std::endl;
    
    file.close();
    return 0;
}