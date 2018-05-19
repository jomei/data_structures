#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector<int> tmp;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }



  void GenerateSwaps() {
    swaps_.clear();

    for(int i = data_.size(); i >= 0; --i) {
      siftDown(i);
    }
  }

  void siftDown(int i) {
    int min = i;
    int left = 2 * i + 1;
    if(left < data_.size() && data_[left] < data_[min]) {
      min = left;
    }
    
    int right = 2 * i + 2;
    if(right < data_.size() && data_[right] < data_[min]) {
      min = right;
    }

    if(i != min) {
      swap(data_[i], data_[min]);
      swaps_.push_back(make_pair(i, min));
      siftDown(min);
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
