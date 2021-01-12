#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  std::cin >> t;
  while (t --> 0) {
    int n, k;
    std::cin >> n >> k;

    int set_bits = __builtin_popcount(k);
    if (set_bits > n || n > k) {
      std::cout << -1 << "\n";
    } else {
      std::vector<int> frequency(26);
      for (int i = 0; i < 26; ++i) {
        if (k & (1 << i)) {
          frequency[i] = 1;
        }
      }

      for (int i = 0; i < n - set_bits; ++i) {
        for (int j = 25; j > 0; --j) {
          if (frequency[j] > 0) {
            --frequency[j];
            frequency[j - 1] += 2;
            break;
          }
        }
      }

      for (int i = 0; i < 26; ++i) {
        std::cout << std::string(frequency[i], 'a' + i);
      }
      std::cout << "\n";
    }
  }

  return 0;
}
