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
        cout << max(abs(i - k + 1), abs(j - k + 1)) + 1;
      }
      cout << '\n';
    }
  }
  return 0;
}
