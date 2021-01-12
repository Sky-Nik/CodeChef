#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

struct RMQ {
  int length = 0;
  std::vector<int> block_min, array;

  void Clear() {
    length = 0;
    block_min.clear();
    array.clear();
  }

  void Initialize(const std::vector<int>& a) {
    int n = a.size();
    array.resize(n);
    length = sqrt(n + .0) + 1;
    block_min.resize(length);
    for (int block_id = 0; block_id < length; ++block_id) {
      block_min[block_id] = block_id * length;
    }
    for (int i = 0; i < n; ++i) {
      const int block_id = i / length;
      if (a[block_min[block_id]] > a[i]) {
        block_min[block_id] = i;
      }
      array[i] = a[i];
    }
  }

  int MinIndex(int left, int right) {
    int answer = left;
    for (int i = left; i < right; ) {
      if (i % length == 0 && i + length <= right) {
        const int block_id = i / length;
        if (array[answer] > array[block_min[block_id]]) {
          answer = block_min[block_id];
        }
        i += length;
      } else {
        if (array[answer] > array[i]) {
          answer = i;
        }
        ++i;
      }
    }
    return answer;
  }
} rmq;

std::vector<int> b_prefix;

int64_t Solve(int left, int right) {
  if (left >= right || b_prefix[right] == b_prefix[left]) {
    return 0;
  }
  int middle = rmq.MinIndex(left, right);
  int left_count = b_prefix[middle + 1] - b_prefix[left];
  int right_count = b_prefix[right] - b_prefix[middle];
  return left_count * 1ll * right_count * 1ll * rmq.array[middle] \
    + Solve(left, middle) + Solve(middle + 1, right);
}


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  std::cin >> t;
  while (t --> 0) {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n), b(m);
    for (auto& ai : a) {
      std::cin >> ai;
    }

    rmq.Initialize(a);

    for (auto& bj : b) {
      std::cin >> bj;
      --bj;  // convert to 0-based
    }

    std::vector<int> b_present(n);
    for (auto bj : b) {
      b_present[bj] = 1;
    }
    b_prefix = {0};
    std::partial_sum(b_present.begin(), b_present.end(),
                     std::back_inserter(b_prefix));

    std::cout << Solve(0, n) << "\n";

    rmq.Clear();
    b_prefix.clear();
  }

  return 0;
}
