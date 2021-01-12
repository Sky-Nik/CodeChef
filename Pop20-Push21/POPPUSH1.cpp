#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int sweets_number;
  std::cin >> sweets_number;
  const auto sweets_types = ReadArray(sweets_number);

  std::unordered_map<int, int> sweets_types_frequencies;
  for (auto sweet_type : sweets_types) {
    ++sweets_types_frequencies[sweet_type];
  }

  int days = 0;
  for (auto [sweet_type, count] : sweets_types_frequencies) {
    if (count % 2 == 0) {     // even
      days += count / 2;      // 2, 2, ..., 2
    } else {                  // odd
      days += count / 2 + 1;  // 2, 2, ..., 2, 1
    }
  }
  std::cout << days << "\n";

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
