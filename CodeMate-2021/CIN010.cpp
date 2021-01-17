#include <bits/stdc++.h>
using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  vector<bool> is_prime_small(33'000, true);
  for (int d = 2; d < 33'000; ++d) {
    if (is_prime_small[d]) {
      for (int m = d * d; m < 33'000; m += d) {
        is_prime_small[m] = false;
      }
    }
  }

  int t;
  cin >> t;
  while (t--) {
    int low, high;
    cin >> low >> high;

    vector<bool> is_prime_large(high - low + 1, true);
    if (low == 1)
      is_prime_large[0] = false;  
    for (int d = 2; d < 33'000; ++d) {
      if (is_prime_small[d]) {
        for (int m = d * (low / d); m <= high; m += d) {
          if (m >= low && m > d) {
            is_prime_large[m - low] = false;
          }
        }
      }
    }

    for (int num = low; num <= high; ++num) {
      if (is_prime_large[num - low]) {
        cout << num << " ";
      }
    }
    cout << "\n";
  }

  return 0;
}
