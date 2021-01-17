#include <bits/stdc++.h>
using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int64_t x, y, z;
    cin >> x >> y >> z;
    int64_t r = 0;
    r += x / z;
    x %= z;
    r += y / z;
    y %= z;
    if (x + y >= z) {
      cout << r + 1 << " " << min(z - y, z - x) << "\n";
    } else {
      cout << r << " " << 0 << "\n";
    }
  }

  return 0;
}
