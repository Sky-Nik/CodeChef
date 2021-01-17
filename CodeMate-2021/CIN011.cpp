#include <bits/stdc++.h>
using namespace std;

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    auto a = ReadArray(n);
    vector<int> p = {0};
    partial_sum(a.begin(), a.end(), back_inserter(p));

    int max_subsegment = 0;
    int min_prefix = 0;
    for (auto pi : p) {
      min_prefix = min(min_prefix, pi);
      max_subsegment = max(max_subsegment, pi - min_prefix);
    }
    cout << max_subsegment << "\n";
  }

  return 0;
}

template <typename T>
std::vector<T> ReadArray(int size, std::istream& in_stream) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<T> array(size);
  for (auto& element : array) {
    in_stream >> element;
  }
  return array;
}
