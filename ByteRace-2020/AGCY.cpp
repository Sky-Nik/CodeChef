#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int t;
  std::cin >> t;
  while (t --> 0) {
    int n, q;
    std::cin >> n >> q;

    std::vector<std::pair<int, int>> queries(q);
    for (auto& query : queries) {
      std::cin >> query.first >> query.second;
      --query.first, --query.second;  // convert to 0-based
    }

    int event_count = q << 1;
    std::vector<std::pair<int, int>> events;  // true if opening false if closing
    for (const auto& query : queries) {
      events.emplace_back(query.first, 0);
      // the intervals are half-open
      events.emplace_back(query.second + 1, query.second - query.first + 1);
    }

    std::sort(events.begin(), events.end());

    int statue_count = 0, segment_count = 0, event_id = 0;
    for (int i = 0; i < n; ++i) {
      while (event_id < event_count && events[event_id].first == i) {
        if (events[event_id].second == 0) {
          ++segment_count;
        } else {
          --segment_count;
          statue_count -= events[event_id].second;
        }
        ++event_id;
      }
      statue_count += segment_count;
      std::cout << statue_count << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
