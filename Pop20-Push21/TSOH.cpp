n#include <algorithm>
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

  int coins_number;
  std::cin >> coins_number;
  const auto coins_values = ReadArray(coins_number);

  const int64_t kImpossible = -1'000'000'000'000ll;

  // prev taken, segment count, prefix length
  std::vector<std::vector<std::vector<int64_t>>> dp(2,
    std::vector<std::vector<int64_t>>(3,
      std::vector<int64_t>(coins_number + 1, kImpossible)));
  dp[false][0].assign(coins_number + 1, 0);

  for (int prefix_length = 0; prefix_length < coins_number; ++prefix_length) {
    // we don't take coins_values[prefix_length]
    for (int segment_count = 0; segment_count <= 2; ++segment_count) {
      dp[false][segment_count][prefix_length + 1] \
        = std::max(dp[false][segment_count][prefix_length],
                   dp[true][segment_count][prefix_length]);
    }

    // we do take coins_values[prefix_length]

    // new segment
    for (int segment_count = 0; segment_count < 2; ++segment_count) {
      dp[true][segment_count + 1][prefix_length + 1] \
        = std::max(dp[false][segment_count][prefix_length],
                   dp[true][segment_count][prefix_length])
          + coins_values[prefix_length];
    }

    // same segment
    for (int segment_count = 0; segment_count <= 2; ++segment_count) {
      dp[true][segment_count][prefix_length + 1] \
        = std::max(dp[true][segment_count][prefix_length + 1],
                   dp[true][segment_count][prefix_length] + coins_values[prefix_length]);
    }
  }

  std::cout << std::max(dp[false][2][coins_number], dp[true][2][coins_number]) << "\n";

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
