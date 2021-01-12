#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

template <typename T = int>
T BinarySearch(T lower_bound, T upper_bound, std::function<bool(T)> unary_predicate, T precision = 1);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int boxes_number;
  std::cin >> boxes_number;
  auto boxes_sizes = ReadArray(boxes_number);

  std::sort(boxes_sizes.begin(), boxes_sizes.end());

  int lower_bound = 0, upper_bound = boxes_number / 2 + 1;
  auto possible = [&] (int middle) -> bool {
    bool answer = true;
    for (int i = 0; i < middle; ++i) {
      answer &= 2 * boxes_sizes[i] <= boxes_sizes[boxes_number - middle + i];
    }
    return answer;
  };

  std::cout << boxes_number - BinarySearch<int>(lower_bound, upper_bound, possible) << "\n";

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

template <typename T>
T BinarySearch(T lower_bound, T upper_bound, std::function<bool(T)> unary_predicate, T precision) {
  while (lower_bound + precision < upper_bound) {
    T middle = lower_bound + (upper_bound - lower_bound) / 2;
    if (unary_predicate(middle)) {
      lower_bound = middle;
    } else {
      upper_bound = middle;
    }
  }
  return lower_bound;
}
