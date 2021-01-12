#include <algorithm>
#include <iostream>
#include <vector>

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

struct Testcase {
  int lines_count;
  std::vector<std::vector<int>> ants_coords;
  friend std::istream& operator>>(std::istream& in_stream, Testcase& testcase);
};

bool Turn(const std::unordered_map<int, int>& coord_frequency,
          const std::vector<int>& line_coords, int coord);

void Update(int64_t& collision_count, int& same_turn, int& same_no_turn, int diff_no_turn, bool turn);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  const auto testcases = ReadArray<Testcase>();
  for (const auto& testcase : testcases) {
    if (testcase.lines_count == 1) {  // subtask #1
      const int left_ants_count = std::count_if(
        testcase.ants_coords[0].begin(),
        testcase.ants_coords[0].end(),
        [] (int ant_coord) -> bool {
          return ant_coord < 0;
        });

      const int right_ants_count = std::count_if(
        testcase.ants_coords[0].begin(),
        testcase.ants_coords[0].end(),
        [] (int ant_coord) -> bool {
          return ant_coord > 0;
        });

      std::cout << left_ants_count * 1ll * right_ants_count << "\n";
    } else {  // subtask # 2
      std::unordered_map<int, int> coord_frequency;
      for (const auto& line_coords : testcase.ants_coords) {
        for (auto ant_coord : line_coords) {
          ++coord_frequency[std::abs(ant_coord)];
        }
      }

      int64_t collision_count = 0;

      for (int line_index = 0; line_index < testcase.lines_count; ++line_index) {
        const auto& line_coords = testcase.ants_coords[line_index];

        auto right_it = std::lower_bound(line_coords.begin(), line_coords.end(), 0);
        auto left_it = std::lower_bound(line_coords.rbegin(), line_coords.rend(), 0, std::greater<>());

        int left_turn = 0, left_no_turn = 0, right_turn = 0, right_no_turn = 0;

        while (left_it != line_coords.rend() || right_it != line_coords.end()) {
          if (left_it != line_coords.rend() && right_it != line_coords.end()) {
            if (std::abs(*left_it) < std::abs(*right_it)) {
              Update(collision_count, left_turn, left_no_turn, right_no_turn,
                Turn(coord_frequency, line_coords, *left_it));
              ++left_it;
            } else {  // std::abs(*left_it) >= std::abs(*right_it)
              Update(collision_count, right_turn, right_no_turn, left_no_turn,
                Turn(coord_frequency, line_coords, *right_it));
              ++right_it;
            }
          } else if (left_it != line_coords.rend()) {
            Update(collision_count, left_turn, left_no_turn, right_no_turn,
              Turn(coord_frequency, line_coords, *left_it));
            ++left_it;
          } else {  // right_it != line_coords.end()
            Update(collision_count, right_turn, right_no_turn, left_no_turn,
              Turn(coord_frequency, line_coords, *right_it));
            ++right_it;
          }
        }
      }

      std::unordered_map<int, std::vector<int>> coord_line_ids;
      for (int line_index = 0; line_index < testcase.lines_count; ++line_index) {
        for (auto ant_coord : testcase.ants_coords[line_index]) {
          coord_line_ids[std::abs(ant_coord)].push_back(line_index);
        }
      }

      for (auto& [key, value] : coord_line_ids) {
        const int size = value.size();
        if (size >= 2) {
          value.erase(std::unique(value.begin(), value.end()), value.end());
          const int actual_size = value.size();
          // std::cout << "Special turn happens at " << key << "\n";
          collision_count += 1 - (size - actual_size);
        }
      }

      std::cout << collision_count << "\n";
    }
  }

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

std::istream& operator>>(std::istream& in_stream, Testcase& testcase) {
  in_stream >> testcase.lines_count;
  testcase.ants_coords.resize(testcase.lines_count);
  for (int line_index = 0; line_index < testcase.lines_count; ++line_index) {
    testcase.ants_coords[line_index] = ReadArray(0, in_stream);
  }
  return in_stream;
}

bool Turn(const std::unordered_map<int, int>& coord_frequency,
          const std::vector<int>& line_coords, int coord) {
  const auto dual_it \
    = std::lower_bound(line_coords.begin(), line_coords.end(), -coord);
  if (dual_it != line_coords.end() && *dual_it == -coord) {
    return false;
  }
  return coord_frequency.at(std::abs(coord)) >= 2;
}

void Update(int64_t& collision_count, int& same_turn, int& same_no_turn, int diff_no_turn, bool turn) {
  collision_count += same_turn + diff_no_turn;
  // std::cout << "Adding " << same_turn << " + " << diff_no_turn << " to collision_count\n";
  if (turn) {
    ++same_turn;
  } else {
    ++same_no_turn;
  }
}
