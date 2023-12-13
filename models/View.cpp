#include "View.h"

View::View(string user_id, time_t timestamp, string group_id, string rate, vector<string> genres) {
    this->user_id = user_id;
    this->timestamp = timestamp;
    this->group_id = group_id;
    this->rate = rate;
    this->genres = genres;
}

void View::print(){
    cout << "-------------------------------------------------------" << endl;
    cout << "User ID: " << this->user_id << endl;
    cout << "Timestamp: " << this->timestamp << endl;
    cout << "Group ID: " << this->group_id << endl;
    cout << "Rate: " << this->rate << endl;
    cout << "Genres: ";
    for (string genre : this->genres){
        cout << genre << " ";
    }
    cout << endl;
    cout << "-------------------------------------------------------" << endl;
}