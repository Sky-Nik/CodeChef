#include <iostream>
#include <string>
#include <vector>

template <typename T = int>
std::pair<int, std::vector<T>> ReadArray(int size = 0, std::istream& in_stream = std::cin);

struct Testcase {
  int length;
  std::string encoded_string;
  friend std::istream& operator>>(std::istream& in_stream, Testcase& testcase);
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  const auto testcases = ReadArray<Testcase>().second;
  for (const auto& testcase : testcases) {
    for (int index = 0; index < testcase.length; index += 4) {
      std::cout << (char)('a'
        + ((testcase.encoded_string[index] - '0') << 3)
        + ((testcase.encoded_string[index + 1] - '0') << 2)
        + ((testcase.encoded_string[index + 2] - '0') << 1)
        + ((testcase.encoded_string[index + 3] - '0')));
    }
    std::cout << "\n";
  }

  return 0;
}

template <typename T>
std::pair<int, std::vector<T>> ReadArray(int size, std::istream& in_stream) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<T> array(size);
  for (auto& element : array) {
    in_stream >> element;
  }
  return {size, std::move(array)};
}

std::istream& operator>>(std::istream& in_stream, Testcase& testcase) {
  in_stream >> testcase.length >> testcase.encoded_string;
  return in_stream;
}
