#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int k;
    cin >> k;
    int n = k >> 1;
    for (int i = 0; i < k; ++i) {
      cout << string(abs(i - n), ' ');
      for (int j = 1; j <= n - 1; ++j) {
        cout << j + abs(i - n);
      }
      cout << '\n';
    }
  }
  return 0;
}
