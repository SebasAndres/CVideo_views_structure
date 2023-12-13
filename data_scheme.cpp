#include "data_scheme.h"

data_scheme::data_scheme(){
    this->generos_user = unordered_map<string, unordered_map<time_t, unordered_set<string>>>();
    this->date_by_user = unordered_map<string, priority_queue<time_t, vector<time_t>, greater<time_t>>>();
    this->rate_user = unordered_map<string, unordered_map<time_t, unordered_set<string>>>();
}

data_scheme::~data_scheme(){
    this->generos_user.clear();
    this->date_by_user.clear();
    this->rate_user.clear();
}

void data_scheme::register_view(View view){        
    vector<string> genres = view.genres;
    string rate = view.rate;

    if (this->generos_user.find(view.user_id) == this->generos_user.end()){
        // Usuario no definido        
        unordered_set<string> genres_set = unordered_set<string>();
        for (string genre : genres){
            genres_set.insert(genre);
        }
        unordered_map<time_t, unordered_set<string>> date_genres = unordered_map<time_t, unordered_set<string>>();
        date_genres.insert({view.timestamp, genres_set});
        this->generos_user.insert({view.user_id, date_genres});
    }
    else {
        // Usuario definido
        if (this->generos_user[view.user_id].find(view.timestamp) == this->generos_user[view.user_id].end()){
            // Fecha no definida
            unordered_set<string> genres_set = unordered_set<string>();
            for (string genre : genres){
                genres_set.insert(genre);
            }
            this->generos_user[view.user_id].insert({view.timestamp, genres_set});
        }
        else {
            // Fecha definida
            for (string genre : genres){
                this->generos_user[view.user_id][view.timestamp].insert(genre);
            }
        }
    }

    if (this->date_by_user.find(view.user_id) == this->date_by_user.end()){
        // Usuario no definido
        priority_queue<time_t, vector<time_t>, greater<time_t>> dates = priority_queue<time_t, vector<time_t>, greater<time_t>>();
        dates.push(view.timestamp);
        this->date_by_user.insert({view.user_id, dates});
    }
    else {
        // Usuario definido
        this->date_by_user[view.user_id].push(view.timestamp);
        while (this->date_by_user[view.user_id].size() > 80
               && this->date_by_user[view.user_id].top() < view.timestamp - 60*60*24*80){
            this->date_by_user[view.user_id].pop();
        }
    }

    if (this->rate_user.find(view.user_id) == this->rate_user.end()){
        // Usuario no definido
        unordered_set<string> rates_set = unordered_set<string>();
        rates_set.insert(rate);
        unordered_map<time_t, unordered_set<string>> date_rates = unordered_map<time_t, unordered_set<string>>();
        date_rates.insert({view.timestamp, rates_set});
        this->rate_user.insert({view.user_id, date_rates});
    }
    else {
        // Usuario definido
        if (this->rate_user[view.user_id].find(view.timestamp) == this->rate_user[view.user_id].end()){
            // Fecha no definida
            unordered_set<string> rates_set = unordered_set<string>();
            rates_set.insert(rate);
            this->rate_user[view.user_id].insert({view.timestamp, rates_set});
        }
        else {
            // Fecha definida
            this->rate_user[view.user_id][view.timestamp].insert(rate);
        }
    }
}

int getRate(string rate){
    unordered_map<string, int> dict = {
        {"G", 1},
        {"PG", 2},
        {"PG-13", 3},
        {"R", 4},
        {"NC-17", 5}
    };
    return dict[rate];
}

string getRateFromId(int id){
    string dict[5] = {"G", "PG", "PG-13", "R", "NC-17"};
    return dict[id];
}

int getMaxRate(unordered_set<string> rates){
    int maxRate = 0;
    for (string rate : rates){
        int rate_int = getRate(rate);
        if (rate_int > maxRate){
            maxRate = rate_int;
        }
    }
    return maxRate;
}

bool isValidDate(time_t date){
    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    return date > now - 60*60*24*80;
}

GENRES_N_RATE data_scheme::get_genres_n_rate_by_user(string user_id){
    /* 
    Devuelve los generos y el maxRate vistos por el usuario en los ultimos 
    80 dias. 
    */

    list<time_t> last80dates;
    int i = 0;

    auto datesOfUser = this->date_by_user[user_id];
    while (i < 80 && !datesOfUser.empty()){
        last80dates.push_front(datesOfUser.top());
        datesOfUser.pop(); 
        i++;
    }

    unordered_set<string> genres;
    int maxRate_int = 0;

    while (!last80dates.empty()){
        time_t date = last80dates.front();
        last80dates.pop_front();
        if (isValidDate(date)){
            for (string genre : this->generos_user[user_id][date]){
                genres.insert(genre);
            }
            auto genreseen = this->rate_user[user_id][date];
            int maxPgRate_date = getMaxRate(genreseen);
            if (maxPgRate_date > maxRate_int){
                maxRate_int = maxPgRate_date;
            }
        }
    }

    string maxRate = getRateFromId(maxRate_int);
    vector<string> genres_vec;
    for (string genre : genres){
        genres_vec.push_back(genre);
    }

    GENRES_N_RATE res = GENRES_N_RATE(genres_vec, maxRate);

    return res;
}
