#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <sstream>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    std::vector<std::deque<std::string>> data_;
    std::vector<std::string> results;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): 
    bucket_count(bucket_count), 
    data_( bucket_count ),
    results() {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) {
        results.push_back(was_found ? "yes" : "no");
    }

  void processQuery(const Query& query) {
    if (query.type == "check") {
      results.push_back(check(query.ind));
    }
    else {
      if (query.type == "find"){
         writeSearchResult(find(query.s));
      }
      else if (query.type == "add") {
        insert(query.s);
      }
      else if (query.type == "del") {
        del(query.s);
      }
    }
  }

    void insert(const std::string &str)  {
        auto &q = data_[hash_func(str)];
        if (std::find(q.begin(), q.end(), str ) == q.end())
          q.push_front(str);
    }

    std::string check(int ind)  {
        std::stringstream ss;
        const auto &q = data_[ind];
        if (q.empty()) {
          ss << "";
          return ss.str();
        }

        for (auto it = q.begin(); it != q.end(); ++it) {
          ss << *it << " ";
        }
        return ss.str();
    }

    bool find(const std::string &str) {
        const auto &q = data_[hash_func( str )];
        auto it = std::find(q.begin(), q.end(), str);
        return it != q.end();
    } 

    void del(const std::string &str) {
        auto &q = data_[hash_func(str)];
        auto it = std::find(q.begin(), q.end(), str);
        if (it != q.end()){
            q.erase( it );
        }      
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());

        for (const auto& r : results) {
              std::cout << r << "\n";
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
