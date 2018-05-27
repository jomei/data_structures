#include <iostream>
#include <vector>
#include <string>
#include <map> 

using std::string;
using std::vector;
using std::cin;
using std::map;
using std::pair;


struct Query {
    Query(string type = "", int number = 0):
        type(type),
        number(number),
        deleted(false)
    {}
    string type, name;
    int number;
    bool deleted;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}


void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    try {
           map <int, Query> contacts;
    for (size_t i = 0; i < queries.size(); ++i) {
        if (queries[i].type == "add") {
            contacts[queries[i].number] = queries[i];
        } else if (queries[i].type == "del") {
             contacts.at(queries[i].number).deleted = true;
        } else {
            string response = "not found";
            if(contacts[queries[i].number].name != "" && !contacts[queries[i].number].deleted){
                result.push_back(contacts.at(queries[i].number).name);
            }else {
                 result.push_back(response);
            }
           
        }
    } 
} catch {
     for (size_t i = 0; i < queries.size(); ++i) {
        std::cout<< 
     }
}

    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
