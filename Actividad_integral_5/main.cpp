#include<iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <ctime>
#include <vector>
#include <algorithm>

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
using std::sort;


int main(){
    ifstream file("ordenado.csv");
    string line;

    unordered_map<string, pair<int, time_t>> umap;

    while(getline(file,line)){
        tm ts = {0};
        stringstream ss(line);
        string basura;
        string timeStampTime;
        string dateStr;
        string dominioDestino;

        if (!line.empty() && line.back() == '\n') {
            line.pop_back();
        }
        if(line.empty()) continue;
        

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

        for(int i=0; i<5; i++) getline(ss,basura,',');

        getline(ss,dominioDestino,',');

        pair<int, time_t> value(0, actualAccess);

        if(umap.count(dominioDestino)==0){
            umap.insert({dominioDestino, value});
        } else {
            double difference = difftime(actualAccess, umap.at(dominioDestino).second);

            if (abs(difference<=30)){
                umap.at(dominioDestino).first++;
            }
            umap.at(dominioDestino).second=actualAccess;
        }
    }

    vector<pair<string,int>> ordenado;

    for(auto it = umap.begin(); it != umap.end(); it++){
        ordenado.push_back({it->first, it ->second.first});
    }

    sort(ordenado.begin(), ordenado.end(), 
        [](const pair<string, int> &a, const pair<string, int> &b) {
            return a.second > b.second; 
        }
    );

    for(int i = 0; i < 10; i++){
        cout << "#" << i+1 << ": " << ordenado[i].first 
             << " | Cantidad: " << ordenado[i].second << endl;
    }



    return 0;
}
