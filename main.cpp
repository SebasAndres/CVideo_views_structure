// g++ main.cpp data_scheme.cpp models/View.cpp models/GENRES_N_RATE.cpp -o main

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "data_scheme.h"
#include "models/View.h"
#include "models/GENRES_N_RATE.h"

using namespace std;

time_t dayInThePast(int daysbackwards){
    // Devuelve el timestamp de hace daysbackwards dias atras
    chrono::system_clock::time_point now = chrono::system_clock::now();
    chrono::system_clock::time_point one_day_ago = now - chrono::hours(24*daysbackwards);
    time_t one_day_ago_time_t = std::chrono::system_clock::to_time_t(one_day_ago);
    return one_day_ago_time_t;
}

int main(){

    // Example of registers

    time_t timestamp1 = chrono::system_clock::to_time_t(chrono::system_clock::now());
    string user_id1 = "@SebasAndres";    
    string group_id1 = "1"; 
    string rate1 = "G"; 
    vector<string> genres1 = {"Accion", "Terror"};

    View sample_view_register1 = View(user_id1, timestamp1, group_id1, rate1, genres1);
    // sample_view_register1.print();

    string user_id2 = "@Juanita";    
    string group_id2 = "2"; 
    string rate2 = "G"; 
    vector<string> genres2 = {"Comedia", "Drama"};
    time_t timestamp2 = dayInThePast(81);
        
    View sample_view_register2 = View(user_id2, timestamp2, group_id1, rate2, genres2);
    // sample_view_register2.print();

    data_scheme ds = data_scheme();
    ds.register_view(sample_view_register1);
    ds.register_view(sample_view_register2);

    GENRES_N_RATE res = ds.get_genres_n_rate_by_user(user_id2);
    for (string genre : res.genres){
        cout << genre << " ";
    }
    cout << endl;
    cout << res.maxRate << endl;

    return 0;
}

