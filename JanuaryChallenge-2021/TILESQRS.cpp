#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

std::vector<int> gray_code_changing_bits;

void InitializeGrayCode(int bits_count = 4);

struct Testcase {
  int board_size, initial_diamonds, max_query_count;
  friend std::istream& operator>>(std::istream& in_stream, Testcase& testcase);
};

enum kDiagonalType {
  kPrimary = 1,    // '\'
  kSecondary = 0,  // '/'
  kUnknown = 2
};

enum QueryType {
  kAsk = 1,
  kAnswer = 2
};

int current_diamond;

void Ask(std::vector<std::vector<kDiagonalType>>* answer_ptr,
         int row, int column, int* current_diamonds_ptr,
         std::istream& in_stream = std::cin, std::ostream& out_stream = std::cout);

void Answer(const std::vector<std::vector<kDiagonalType>>& answer,
            std::istream& in_stream = std::cin, std::ostream& out_stream = std::cout);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  InitializeGrayCode();

  int testcases_count;
  std::cin >> testcases_count;
  while (testcases_count --> 0) {
    Testcase testcase;
    std::cin >> testcase;

    std::vector<std::vector<kDiagonalType>> answer(testcase.board_size,
      std::vector<kDiagonalType>(testcase.board_size, kDiagonalType::kUnknown));

    // top-left corner
    bool determined = false;
    std::vector<int> current_diamonds(16);
    current_diamonds[0] = current_diamond = testcase.initial_diamonds;
    for (int i = 0; i < 15 && !determined; ++i) {
      if (gray_code_changing_bits[i] == 0) {
        Ask(&answer, 0, 0, &(current_diamonds[i + 1]));

        if (current_diamonds[i + 1] != current_diamonds[i]) {
          determined = true;
          answer[0][1] = kDiagonalType::kPrimary;
          answer[1][0] = kDiagonalType::kPrimary;
          answer[1][1] = kDiagonalType::kSecondary;

          if (current_diamonds[i + 1] > current_diamonds[i]) {
            answer[0][0] = kDiagonalType::kSecondary;
          } else {  // current_diamonds[i] < current_diamonds[i - 1]
            answer[0][0] = kDiagonalType::kPrimary;
          }
        }
      } else if (gray_code_changing_bits[i] == 1) {
        Ask(&answer, 0, 1, &(current_diamonds[i + 1]));
      } else if (gray_code_changing_bits[i] == 2) {
        Ask(&answer, 1, 0, &(current_diamonds[i + 1]));
      } else {  // gray_code_changing_bits[i] == 3
        Ask(&answer, 1, 1, &(current_diamonds[i + 1]));
      }
    }

    // top row
    for (int column = 2; column < testcase.board_size; ++column) {
      current_diamonds[0] = current_diamond;
      determined = false;
      if (answer[1][column - 1] == kDiagonalType::kSecondary) {
        Ask(&answer, 1, column - 1, &(current_diamonds[0]));
      }

      for (int i = 0; i < 7 && !determined; ++i) {
        if (gray_code_changing_bits[i] == 0) {
          Ask(&answer, 0, column - 1, &(current_diamonds[i + 1]));

          if (current_diamonds[i + 1] != current_diamonds[i]) {
            determined = true;
            answer[0][column] = kDiagonalType::kPrimary;
            answer[1][column] = kDiagonalType::kSecondary;
          }
        } else if (gray_code_changing_bits[i] == 1) {
          Ask(&answer, 0, column, &(current_diamonds[i + 1]));
        } else {  // gray_code_changing_bits[i] == 2
          Ask(&answer, 1, column, &(current_diamonds[i + 1]));
        }
      }
    }

    // left column
    for (int row = 2; row < testcase.board_size; ++row) {
      current_diamonds[0] = current_diamond;
      determined = false;
      if (answer[row - 1][1] == kDiagonalType::kSecondary) {
        Ask(&answer, row - 1, 1, &(current_diamonds[0]));
      }

      for (int i = 0; i < 7 && !determined; ++i) {
        if (gray_code_changing_bits[i] == 0) {
          Ask(&answer, row - 1, 0, &(current_diamonds[i + 1]));

          if (current_diamonds[i + 1] != current_diamonds[i]) {
            determined = true;
            answer[row][0] = kDiagonalType::kPrimary;
            answer[row][1] = kDiagonalType::kSecondary;
          }
        } else if (gray_code_changing_bits[i] == 1) {
          Ask(&answer, row, 0, &(current_diamonds[i + 1]));
        } else {  // gray_code_changing_bits[i] == 2
          Ask(&answer, row, 1, &(current_diamonds[i + 1]));
        }
      }
    }

    // rest
    for (int row = 2; row < testcase.board_size; ++row) {
      for (int column = 2; column < testcase.board_size; ++column) {
        current_diamonds[0] = current_diamond;

        if (answer[row - 1][column - 1] == kDiagonalType::kPrimary) {
          Ask(&answer, row - 1, column - 1, &(current_diamonds[0]));
        }
        if (answer[row][column - 1] == kDiagonalType::kSecondary) {
          Ask(&answer, row, column - 1, &(current_diamonds[0]));
        }
        if (answer[row - 1][column] == kDiagonalType::kSecondary) {
          Ask(&answer, row - 1, column, &(current_diamonds[0]));
        }

        Ask(&answer, row, column, &(current_diamonds[1]));

        if (current_diamonds[1] > current_diamonds[0]) {
          answer[row][column] = kDiagonalType::kSecondary;
        } else {  // current_diamonds[1] < current_diamonds[0]
          answer[row][column] = kDiagonalType::kPrimary;
        }
      }
    }

    Answer(answer);
  }

  return 0;
}

void InitializeGrayCode(int bits_count) {
  for (int i = 0; i < bits_count; ++i) {
    const int current_size = gray_code_changing_bits.size();
    gray_code_changing_bits.push_back(i);
    for (int j = 0; j < current_size; ++j) {
      gray_code_changing_bits.push_back(gray_code_changing_bits[j]);
    }
  }
}

std::istream& operator>>(std::istream& in_stream, Testcase& testcase) {
  in_stream >> testcase.board_size >> testcase.max_query_count >> testcase.initial_diamonds;
  return in_stream;
}

void Ask(std::vector<std::vector<kDiagonalType>>* answer_ptr,
         int row, int column, int* current_diamonds_ptr,
         std::istream& in_stream, std::ostream& out_stream) {
  // the question itself
  out_stream << QueryType::kAsk << " " << row + 1 << " " << column + 1 << std::endl;

  // read the response
  in_stream >> current_diamond;
  assert(current_diamond != -1);
  *current_diamonds_ptr = current_diamond;

  // update answer if it is already known
  if ((*answer_ptr)[row][column] == kDiagonalType::kPrimary) {
    (*answer_ptr)[row][column] = kDiagonalType::kSecondary;
  } else if ((*answer_ptr)[row][column] == kDiagonalType::kSecondary) {
    (*answer_ptr)[row][column] = kDiagonalType::kPrimary;
  }
}

void Answer(const std::vector<std::vector<kDiagonalType>>& answer,
            std::istream& in_stream, std::ostream& out_stream) {
  // the answer itself
  out_stream << QueryType::kAnswer << std::endl;
  for (const auto& row : answer) {
    for (const auto diagonal : row) {
      out_stream << diagonal << " ";
    }
    out_stream << std::endl;
  }

  // verify the response
  int response;
  in_stream >> response;
  assert(response != -1);
}
