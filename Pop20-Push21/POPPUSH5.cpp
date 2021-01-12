#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

using Graph = vector<vector<pair<int, int>>>;

bool dfs(const Graph& graph, std::vector<int>& visited,
         std::vector<int>& to_clean, int vertex, bool parent_clean = true) {
  visited[vertex] = 1;
  bool want_to_clean = !parent_clean;
  bool return_value = want_to_clean;
  for (auto [adj, clean] : graph[vertex]) {
    if (!visited[adj]) {
      bool adj_answer = dfs(graph, visited, to_clean, adj, clean == 1);
      want_to_clean &= !adj_answer; 
      return_value |= adj_answer;
    }
  }
  to_clean[vertex] = want_to_clean;
  return return_value;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n;
  cin >> n;

  Graph graph(n);
  for (int e = 1; e < n; ++e) {
    int u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
  }

  std::vector<int> visited(n), clean(n);
  dfs(graph, visited, clean, 0);
  cout << accumulate(clean.begin(), clean.end(), 0) << "\n";

  return 0;
}

template <typename T>
std::vector<T> ReadArray(int size, std::istream& in_stream) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<T> array(size);
  for (auto& element : array) {
    in_stream >> element;
  }
  return array;
}
