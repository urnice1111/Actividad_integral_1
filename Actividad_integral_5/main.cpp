#include<iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <time.h>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::pair;
using std::getline;
using std::unordered_map;
using std::ifstream;
using std::stringstream;


int main(){
    ifstream file("ordenado.csv");
    string line;

    unordered_map<string, pair<int, time_t>> umap;

    while(getline(file,line)){
        tm ts;
        stringstream ss(line);
        string basura;
        string timeStampTime;
        string dateStr;
        string dominioDestino;
        

        //fecha
        getline(ss, dateStr, ',');
        stringstream date_ss(dateStr);
        string dd, mm, yyyy;
        getline(date_ss, dd, '-');
        getline(date_ss, mm, '-');
        getline(date_ss, yyyy, '-');
        ts.tm_mday = std::stoi(dd);
        ts.tm_mon  = std::stoi(mm) - 1;    
        ts.tm_year = std::stoi(yyyy) - 1900;

        //hora
        getline(ss, timeStampTime, ',');
        stringstream date_ss_time(timeStampTime);
        string h,m,s;
        getline(date_ss_time,h,':');
        getline(date_ss_time,m,':');
        getline(date_ss_time,s,':');
        ts.tm_hour = stoi(h);
        ts.tm_min = stoi(m);
        ts.tm_sec = stoi(s);

        time_t actualAccess = mktime(&ts);

        getline(ss,basura,',');
        getline(ss,basura,',');
        getline(ss,basura,',');
        getline(ss,basura,',');
        getline(ss,basura,',');

        getline(ss,dominioDestino,',');

        pair<int, time_t> value(0, actualAccess);

        if(umap.count(dominioDestino)==0){
            umap.insert({dominioDestino, value});
        } else {
            double difference = difftime(actualAccess, umap.at(dominioDestino).second);

            if (difference<=30){
                umap.at(dominioDestino).second=actualAccess;
                umap.at(dominioDestino).first++;
            }
        }
    }

    for(auto it = umap.begin(); it != umap.end(); it++){
        cout<< "Dominio destino: "<< it ->first<<endl;
        cout<< "Contador: "<<it ->second.first<<endl;
        cout<<endl;
    }

    return 0;
}
