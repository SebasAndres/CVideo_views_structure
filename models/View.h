#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class View {
public:
    string user_id;
    string group_id;
    string rate;
    time_t timestamp;
    vector<string> genres;

    View(string user_id, time_t timestamp, string group_id, string rate, vector<string> genres);
    
    void print();
};

#endif