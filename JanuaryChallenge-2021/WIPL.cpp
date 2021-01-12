#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

template <typename T = int>
std::pair<int, std::vector<T>> ReadArray(int size = 0, std::istream& in_stream = std::cin);

const int max_wall_height = 4'000;

const int max_dp_size = 3 * max_wall_height + 1;

struct Testcase {
  int box_count, wall_height;
  std::vector<int> boxes_heights;
  friend std::istream& operator>>(std::istream& in_stream, Testcase& testcase);
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  auto testcases = ReadArray<Testcase>().second;
  for (auto& testcase : testcases) {
    std::sort(testcase.boxes_heights.begin(), testcase.boxes_heights.end(), std::greater<>());
    int total = 0, box_count = 0;
    std::bitset<max_dp_size> dp;
    dp[0] = 1;
    bool found = false;
    for (auto box_height : testcase.boxes_heights) {
      if (found) {
        break;
      }
      if (box_height > max_wall_height) {
        box_height = max_wall_height;
      }
      total += box_height;
      ++box_count;
      dp |= dp << box_height;
      for (int first = testcase.wall_height;
           first + testcase.wall_height <= total && !found;
           ++first) {
        if (dp[first]) {
          std::cout << box_count << "\n";
          found = true;
        }
      }
    }
    if (!found) {
      std::cout << -1 << "\n";
    }
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
  in_stream >> testcase.box_count >> testcase.wall_height;
  testcase.boxes_heights = ReadArray(testcase.box_count, in_stream).second;
  return in_stream;
}
