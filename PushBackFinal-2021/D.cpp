#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int k;
    cin >> k;
    int n = 2 * k - 1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == j || i == n - 1 - j || i == 0 || i == n - 1) {
          cout << j + 1;
        } else {
          cout << ' ';
        }
      }
      cout << '\n';
    }
  }
  return 0;
}
