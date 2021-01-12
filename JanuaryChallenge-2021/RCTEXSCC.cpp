#include <iostream>

int64_t pow(int64_t num, int64_t pow) {
  int64_t res = 1;
  while (pow) {
    if (pow & 1) {
      res *= num;
      res %= mod;
    }
    num *= num;
    num %= mod;
    pow >>= 1;
  }
  return res;
}

int64_t inv(int64_t num) {
  return pow(num, mod - 2);
}

const int64_t mod = 998'244'353;

int64_t add(int64_t first) {
  return first;
}

template <typename... Args>
int64_t add(int64_t first, Args... args) {
  return (first + add(args...)) % mod;
}

int64_t mul(int64_t first) {
  return first;
}

template <typename... Args>
int64_t mul(int64_t first, Args... args) {
  return (first * mul(args...)) % mod;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int64_t m, n, k;
  std::cin >> m >> n >> k;
  if (m == 2) {
    std::cout << mul(add(mul(2, k, k, k, k, n), mul(mod - 3, k, k, k, n), mul(2, k, k, k), mul(k, n), mod - k), inv(mul(k, k, k, k))) << "\n";
  } else {
    std::cout << mul(add(mul(n, k), mod - n + 1), inv(k)) << "\n";
  }

  return 0;
}