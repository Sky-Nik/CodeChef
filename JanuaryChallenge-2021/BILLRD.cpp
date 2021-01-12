#include <iostream>
#include <vector>

template <typename T = int>
std::pair<int, std::vector<T>> ReadArray(int size = 0, std::istream& in_stream = std::cin);

struct Point {
  int x, y;
};

struct Direction {
  int dx = 1, dy = 1;
};

void Step(Point& point, Direction& direction, int billiard_size);

struct Testcase {
  int billiard_size, step_count;
  Point starting_point;
  friend std::istream& operator>>(std::istream& in_stream, Testcase& testcase);
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  auto testcases = ReadArray<Testcase>().second;
  for (auto& testcase : testcases) {
    if (testcase.starting_point.x == testcase.starting_point.y) {
      std::cout << testcase.billiard_size << " " << testcase.billiard_size << "\n";
    } else {
      testcase.step_count %= 4;
      if (!testcase.step_count) {
        testcase.step_count = 4;
      }
      Direction direction;
      for (int step = 0; step < testcase.step_count; ++step) {
        Step(testcase.starting_point, direction, testcase.billiard_size);
      }
      std::cout << testcase.starting_point.x << " " << testcase.starting_point.y << "\n";
    }
  }

  return 0;
}

void Step(Point& point, Direction& direction, int billiard_size) {
  const int delta_x = direction.dx == 1 ? billiard_size - point.x : point.x;
  const int delta_y = direction.dy == 1 ? billiard_size - point.y : point.y;
  const int delta = std::min(delta_x, delta_y);
  point.x += direction.dx * delta;
  point.y += direction.dy * delta;
  direction.dx *= (point.x == billiard_size || point.x == 0) ? -1 : 1;
  direction.dy *= (point.y == billiard_size || point.y == 0) ? -1 : 1;
}

template <typename T>
std::pair<int, std::vector<T>> ReadArray(int size, std::istream& in_stream) {
  if (!size) {
    in_stream >> size;
  }
  std::vector<T> array(size);
  for (auto& element : array) {
    in_stream >> element;
  }
  return {size, std::move(array)};
}

std::istream& operator>>(std::istream& in_stream, Testcase& testcase) {
  in_stream >> testcase.billiard_size >> testcase.step_count \
    >> testcase.starting_point.x >> testcase.starting_point.y;
  return in_stream;
}
