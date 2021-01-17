#include <bits/stdc++.h>
using namespace std;

void dfs(const unordered_map<int, vector<int>>& g, 
         unordered_map<int, bool>& u, int vertex) {
  u[vertex] = true;
  for (auto adjacent : g.at(vertex)) {
    if (!u[adjacent]) {
      dfs(g, u, adjacent);
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n, m, a, b;
  cin >> n >> m >> a >> b;
  unordered_map<int, vector<int>> g;
  g.reserve(n);
  unordered_map<int, bool> u;
  u.reserve(n);
  while (m--) {
    int i, j;
    cin >> i >> j;
    g[i].push_back(j);
    g[j].push_back(i);
    u[i] = false;
    u[j] = false;
  }

  int cc = n - u.size();
  for (auto [vertex, used] : u) {
    if (!used) {
      dfs(g, u, vertex);
      ++cc;
    }
  }

  if (a < b) {  // antivirus is cheaper
    cout << cc * a << "\n";
  } else {  // wire is cheaper
    cout << a + (cc - 1) * b << "\n";
  }

  return 0;
}
