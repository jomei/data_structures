#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>


using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;

typedef pair<bool, vector<int>> result;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

result check(const vector<Node>& tree, int node) {
  result r_l;
  result r_r;
  if (tree[node].left == -1 && tree[node].right == -1) {
    return {true, {node}};
  }
  
  if(tree[node].left != -1) {
    r_l = check(tree, tree[node].left);
    if(!r_l.first){ return {false, {}}; }
    for(int i : r_l.second) {
      if(tree[i].key > tree[node].key) { return {false, {}}; }
    }
  }

  if(tree[node].right != -1) {
    r_r = check(tree, tree[node].right);
    if(!r_r.first){ return {false, {}}; }
    for(int i : r_r.second) {
      if(tree[i].key < tree[node].key) { return {false, {}}; }
    }
  }

  vector<int> r = r_l.second;
  r.push_back(node);
  r.insert(r.end(), r_r.second.begin(), r_r.second.end());

  return {true, r};
}

bool is_bst(const vector<Node>& tree, int node, int min, int max) {
  // cout << "node: " << node << " key: " << tree[node].key << " min: " << min << " max: " << max << endl;
  if(node == -1) {return true;}
  if(tree[node].key < min || tree[node].key > max ) {
    return false;
  }

  return (is_bst(tree, tree[node].left, min, tree[node].key-1) &&
              is_bst(tree, tree[node].right, tree[node].key+1, max));
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  if(tree.size() < 1) {return true;}

  return is_bst(tree, 0, INT_MIN, INT_MAX);
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
