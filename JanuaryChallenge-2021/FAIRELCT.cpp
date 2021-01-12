#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

template <typename T = int>
std::pair<int, std::vector<T>> ReadArray(int size = 0, std::istream& in_stream = std::cin);

struct Testcase {
  int first_pack_count, second_pack_count;
  std::vector<int> first_packs, second_packs;
  friend std::istream& operator>>(std::istream& in_stream, Testcase& testcase);
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  auto testcases = ReadArray<Testcase>().second;
  for (auto& testcase : testcases) {
    std::sort(testcase.first_packs.begin(), testcase.first_packs.end());
    std::sort(testcase.second_packs.begin(), testcase.second_packs.end(), std::greater<>());
    int first_vote_count \
      = std::accumulate(testcase.first_packs.begin(), testcase.first_packs.end(), 0);
    int second_vote_count \
      = std::accumulate(testcase.second_packs.begin(), testcase.second_packs.end(), 0);
    const int max_swap_count = std::min(testcase.first_pack_count, testcase.second_pack_count);
    int swap_count = 0;
    while (swap_count < max_swap_count && first_vote_count <= second_vote_count) {
      const int swap_vote_delta \
        = testcase.second_packs[swap_count] - testcase.first_packs[swap_count];
      first_vote_count += swap_vote_delta;
      second_vote_count -= swap_vote_delta;
      ++swap_count;
    }
    if (first_vote_count > second_vote_count) {
      std::cout << swap_count << "\n";
    } else {
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
  in_stream >> testcase.first_pack_count >> testcase.second_pack_count;
  testcase.first_packs = ReadArray(testcase.first_pack_count, in_stream).second;
  testcase.second_packs = ReadArray(testcase.second_pack_count, in_stream).second;
  return in_stream;
}
