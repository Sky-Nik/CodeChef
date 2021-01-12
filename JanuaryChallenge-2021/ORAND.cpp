#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

template <typename T = int>
std::vector<T> ReadArray(int size = 0, std::istream& in_stream = std::cin);

struct Testcase {
  int or_operations_count, and_operations_count;
  std::vector<int> or_operations, and_operations;
  friend std::istream& operator>>(std::istream& in_stream, Testcase& testcase);
};

bool IsFirstSubtask(const Testcase& testcase);

bool IsSecondSubtask(const Testcase& testcase);

void DFS(int vertex, const Testcase& testcase, std::vector<bool>& visited);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  const auto testcases = ReadArray<Testcase>();
  for (const auto& testcase : testcases) {
    if (IsFirstSubtask(testcase)) {
      std::vector<bool> visited(1 << 10);
      DFS(0, testcase, visited);
      std::cout << std::accumulate(visited.begin(), visited.end(), 0) << "\n";
    } else if (IsSecondSubtask(testcase)) {
      throw std::runtime_error("not implemented");
      // todo
    } else {  // subtask # 3
      throw std::runtime_error("not implemented");
      // todo
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
  in_stream >> testcase.or_operations_count >> testcase.and_operations_count;
  testcase.or_operations = ReadArray(testcase.or_operations_count);
  testcase.and_operations = ReadArray(testcase.and_operations_count);
  return in_stream;
}

void DFS(int vertex, const Testcase& testcase, std::vector<bool>& visited) {
  visited[vertex] = true;
  for (auto or_operation : testcase.or_operations) {
    if (!visited[vertex | or_operation]) {
      DFS(vertex | or_operation, testcase, visited);
    }
  }
  for (auto and_operation : testcase.and_operations) {
    if (!visited[vertex & and_operation]) {
      DFS(vertex & and_operation, testcase, visited);
    }
  }
}

bool IsFirstSubtask(const Testcase& testcase) {
  return testcase.or_operations_count <= (1 << 10) &&
    testcase.and_operations_count <= (1 << 10) &&
    *std::max_element(testcase.or_operations.begin(),
                      testcase.or_operations.end()) < (1 << 10) &&
    *std::max_element(testcase.and_operations.begin(),
                      testcase.and_operations.end()) < (1 << 10);
}

bool IsSecondSubtask(const Testcase& testcase) {
  return testcase.or_operations_count <= (1 << 15) &&
    testcase.and_operations_count <= (1 << 15) &&
    *std::max_element(testcase.or_operations.begin(),
                      testcase.or_operations.end()) < (1 << 15) &&
    *std::max_element(testcase.and_operations.begin(),
                      testcase.and_operations.end()) < (1 << 15);
}
