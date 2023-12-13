#include <iostream>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <list>
#include <functional>

#include "models/View.h"
#include "models/GENRES_N_RATE.h"

using namespace std;

class data_scheme {
private:
    /*
    Generos&User := <UserID, DictTrie<Fecha, SetTrie<Genero>>>
    Fechas&User := DictTrie<UserID, PriorityQueueMin<Fecha>>
    Rate&User := DictTrie<UserID, DictTrie<Fecha, SetTrie<Rate>>>    
    */
    unordered_map<string, unordered_map<time_t, unordered_set<string>>> generos_user;
    unordered_map<string, priority_queue<time_t, vector<time_t>, greater<time_t>>> date_by_user;
    unordered_map<string, unordered_map<time_t, unordered_set<string>>> rate_user;

public:
    data_scheme();
    ~data_scheme();

    void register_view(View view);
    GENRES_N_RATE get_genres_n_rate_by_user(string user_id);
};