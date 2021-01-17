#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int k;
    cin >> k;
    int m = k * k;
    int i = 0, j = 0, n = 0;
    vector<pair<int, int>> d = {{0,1},{1,0},{0,-1},{-1,0}};
    vector<vector<int>> board(k, vector<int>(k));

    while (m) {
      board[i][j] = m;
      for (int l = 0; l < 4; ++l) {
        if (0 <= d[n].first + i && d[n].first + i < k &&
            0 <= d[n].second + j && d[n].second + j < k &&
            board[d[n].first + i][d[n].second + j]) {
          break;
        }
        n = (n + 1) % 4;
      }
      i = d[n].first + i;
      j = d[n].second + j;
      --m;
    }

    for (auto row : board) {
      for (auto col : row) {
        cout << col << ' ';
      }
      cout << '\n';
    }
  }

  return 0;
}
