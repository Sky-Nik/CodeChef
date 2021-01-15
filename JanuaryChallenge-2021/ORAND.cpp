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

int ext = 1 << 20;

const int64_t mod = 998'244'353;

bool IsFirstSubtask(const Testcase& testcase);

bool IsSecondSubtask(const Testcase& testcase);

int FastModularPower(int64_t base, int power) {
  int64_t result = 1;
  while (power) {
    if (power & 1) {
      result *= base;
      result %= mod;
    }
    base *= base;
    base %= mod;
    power >>= 1;
  }
  return result;
}

void FastWalshHadamardTransformModularInplaceOr(std::vector<int64_t>& f, bool inverse = false) {
  for (int l = 2, k = 1; l <= ext; l <<= 1, k <<= 1) {
    for (int i = 0; i < ext; i += l) {
      for (int j = 0; j < k; j++) {
        f[i + j + k] = (f[i + j + k] + f[i + j] * (inverse ? -1ll : 1ll)) % mod;
      }
    }
  }
}

void FastWalshHadamardTransformModularInplaceAnd(std::vector<int64_t>& f, bool inverse = false) {
  for (int l = 2, k = 1; l <= ext; l <<= 1, k <<= 1) {
    for (int i = 0; i < ext; i += l) {
      for (int j = 0; j < k; j++) {
        f[i + j] = (f[i + j] + f[i + j + k] * (inverse ? -1ll : 1ll)) % mod;
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  const auto testcases = ReadArray<Testcase>();
  for (const auto& testcase : testcases) {
    if (IsFirstSubtask(testcase)) {
      ext = 1 << 10;
    } else if (IsSecondSubtask(testcase)) {
      ext = 1 << 15;
    } else {  // IsThirdSubtask
      ext = 1 << 20;
    }

    std::vector<int64_t> or_operands(ext), and_operands(ext), array(ext);

    for (auto or_operation : testcase.or_operations) {
      ++or_operands[or_operation];
    }
    or_operands[0] = 1;
    FastWalshHadamardTransformModularInplaceOr(or_operands);
    for (auto& or_operand : or_operands) {
      or_operand = FastModularPower(or_operand, 1'800);
    }

    for (auto and_operation : testcase.and_operations) {
      ++and_operands[and_operation];
    }
    and_operands[ext - 1] = 1;
    FastWalshHadamardTransformModularInplaceAnd(and_operands);
    for (auto& and_operand : and_operands) {
      and_operand = FastModularPower(and_operand, 1'800);
    }

    array[0] = 1;
    for (int iteration = 0; iteration < 20; ++iteration) {
      FastWalshHadamardTransformModularInplaceOr(array);
      for (int i = 0; i < ext; ++i) {
        array[i] *= or_operands[i];
        array[i] %= mod;
      }
      FastWalshHadamardTransformModularInplaceOr(array, true);
      FastWalshHadamardTransformModularInplaceAnd(array);
      for (int i = 0; i < ext; ++i) {
        array[i] *= and_operands[i];
        array[i] %= mod;
      }
      FastWalshHadamardTransformModularInplaceAnd(array, true);
    }
    int answer = 0;
    for (auto element : array) {
      if (element) {
        ++answer;
      }
    }
    std::cout << answer << "\n";
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
