#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
      cout << string(k - 1 - i, ' ');
      for (int j = 0; j <= i; ++j) {
        cout << j + 1 << ' ';
      }
      cout << '\n';
    }
  }
  return 0;
}
