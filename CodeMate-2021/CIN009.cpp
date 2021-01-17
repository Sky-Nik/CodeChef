#include <bits/stdc++.h>
using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int w;
  cin >> w;
  while (w--) {
    int n;
    string s;
    cin >> n >> s;
    int j = 0;
    for (int i = 0; i < n; ++i) {
      if (make_pair(tolower(s[i]), isupper(s[i])) >
          make_pair(tolower(s[j]), isupper(s[j]))) {
        j = i;
      }
    }
    cout << j + 1 << "\n";
  }

  return 0;
}
