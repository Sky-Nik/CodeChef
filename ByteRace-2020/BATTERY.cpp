/*
4
4 8
5 1 4 2
3 4
3 1 2
2 7
5 5
5 30
1 10 10 10 1
->
YES
YES
NO
YES
*/

#include <iostream>
#include <iterator>
#include <set>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  std::cin >> t;
  while (t --> 0) {
    int n; int64_t x;
    std::cin >> n >> x;

    std::vector<int> a(n);
    for (auto& ai : a) {
      std::cin >> ai;
    }

    std::multiset<int> unused;

    if (n & 1) {  // n is odd
      int middle = n >> 1;
      x -= a[middle];
      for (int left = middle - 1, right = middle + 1;
           0 <= left && right < n; --left, ++right) {
        unused.insert(a[left]);
        unused.insert(a[right]);
        const auto max_element_it = std::prev(unused.end());
        x -= *max_element_it;
        unused.erase(max_element_it);
      }
    } else {  // n is even
      for (int left = (n >> 1) - 1, right = n >> 1;
           0 <= left && right < n; --left, ++right) {
        unused.insert(a[left]);
        unused.insert(a[right]);
        const auto max_element_it = std::prev(unused.end());
        x -= *max_element_it;
        unused.erase(max_element_it);
      }
    }

    if (x <= 0) {
      std::cout << "YES" << "\n";
    } else {
      std::cout << "NO" << "\n";
    }
  }

  return 0;
}
