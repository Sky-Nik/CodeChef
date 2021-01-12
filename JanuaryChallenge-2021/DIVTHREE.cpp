#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

template <typename T = int>
std::pair<int, std::vector<T>> ReadArray(int size = 0, std::istream& in_stream = std::cin);

struct Testcase {
  int setters_count, problems_count, days_count;
  std::vector<int> setters_problems;
  friend std::istream& operator>>(std::istream& in_stream, Testcase& testcase);
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  const auto testcases = ReadArray<Testcase>().second;
  for (const auto& testcase : testcases) {
    std::cout << std::min(testcase.days_count,
      std::accumulate(testcase.setters_problems.begin(),
                      testcase.setters_problems.end(), 0)
        / testcase.problems_count) << "\n";
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
  in_stream >> testcase.setters_count >> testcase.problems_count >> testcase.days_count;
  testcase.setters_problems = ReadArray(testcase.setters_count, in_stream).second;
  return in_stream;
}
