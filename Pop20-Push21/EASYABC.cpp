#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
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

  std::string string;
  std::cin >> string;

  std::unordered_map<char, int> letter_first_position, letter_last_position;

  const int length = s.length();
  for (int position = 0; position < length; ++position) {
    if (!letter_first_position.count(string[position])) {
      letter_first_position[string[position]] = position;
    }
    letter_last_position[string[position]] = position;
  }

  int maximum_distance = -1;
  for (auto [first_letter, first_position] : letter_first_position) {
    for (auto [last_letter, last_position] : letter_last_position) {
      if (first_letter != last_letter) {
        maximum_distance = std::max(maximum_distance,
          std::abs(first_position - last_position));
      }
    }
  }
  std::cout << maximum_distance << "\n";

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
