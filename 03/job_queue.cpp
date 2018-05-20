#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;

class Worker{
public:
  Worker(int id, long long finish_time):
        id(id),
        finish_time(finish_time)
    {}
  int id;
  long long finish_time;

  void debug() {
    cout << "id:" << id <<" t:" << finish_time << std::endl;
  }
};

class WorkersQueue {
  int size;
  vector<Worker> heap;

  void insert(Worker w) {
    if(heap.size() != size) {
      heap.push_back(w);
      siftUp(heap.size() - 1);
    }
  }

  void siftUp(int i) {
    while(i != 0 && comp(parent(i), i)) {
      swap(heap[parent(i)], heap[i]);
      i = parent(i);
    }
  }

  void siftDown(int i) {
    int m = i;
    int l = left(i);
    if(l < heap.size() && comp(m, l)) {m = l;}
    int r = right(i);
    if(r < heap.size() && comp(m, r)) {m = r;}
    if(i != m) {
      // cout<<"swap" << heap[i].id << " with " << heap[m].id << std::endl;
      swap(heap[i], heap[m]);
      siftDown(m);
    }
  }

  bool comp(int a, int b) {
    // cout <<"compare" << heap[a].id << "," << heap[a].finish_time << " with" << heap[b].id << "," << heap[b].finish_time<<std::endl;
    if(heap[a].finish_time == heap[b].finish_time) {
      return heap[a].id > heap[b].id;
    }
    return heap[a].finish_time > heap[b].finish_time;
  }

  int parent(int i) {
    return (i -1) / 2;
  }

  int left(int i) { return 2 * i + 1;}
  int right(int i) {return 2*i +2;}
public:
  WorkersQueue(int s) {
   size = s; 
   for(int i = 0 ; i < s; ++i) {
    insert(Worker(i, 0));
   }
 }

 Worker& get() {
  return heap[0];
 }

 void apply(int job) {
  Worker w = get();
  w.finish_time += job;
  heap[0] = w;
  siftDown(0);
 }

 void debug() {
  for(auto w: heap) {
    w.debug();
  }
 }

};

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;
  vector<int> assigned_workers_;
  vector<long long> start_times_;
  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    long long cloak = 0;
    int completed = 0;
    WorkersQueue q = WorkersQueue(num_workers_);
    while(completed < jobs_.size()) {
      Worker w = q.get();
      assigned_workers_.push_back(w.id);
      start_times_.push_back(w.finish_time);
      q.apply(jobs_[completed]);
      ++completed;
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
