#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  long long key;
  long long left;
  long long right;

  Node() : key(0), left(-1), right(-1) {}
  Node(long long key_, long long left_, long long right_) : key(key_), left(left_), right(right_) {}
};


bool is_bst(const vector<Node>& tree, long long node, long long min, long long max) {
  // cout << "node: " << node << " key: " << tree[node].key << " min: " << min << " max: " << max << endl;
  if(node == -1) {return true;}
  if(tree[node].key < min || tree[node].key > max ) {
    return false;
  }

  return (is_bst(tree, tree[node].left, min, tree[node].key-1) &&
              is_bst(tree, tree[node].right, tree[node].key, max));
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  if(tree.size() < 1) {return true;}

  return is_bst(tree, 0, INT_MIN, INT_MAX);
}

int main() {
  long long nodes;
  cin >> nodes;
  vector<Node> tree;
  for (long long i = 0; i < nodes; ++i) {
    long long key, left, right;
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
