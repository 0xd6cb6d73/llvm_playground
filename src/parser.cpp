#include "parser.hpp"
#include <cassert>
#include <charconv>
#include <cstdint>
#include <exception>
#include <string_view>

namespace lang {
class invalid_expression : std::exception {};
class unmatched_quotes : std::exception {};
class unknown_exp_type : std::exception {};

ParseExp Parser::parse(const std::string_view str) {
  const auto first = str.at(0);
  assert(str.at(0) == '(');
  assert(str.at(str.size() - 1) == ')');
  return this->parse_str(str);
}

ParseExp Parser::parse_str(const std::string_view str) {
  const auto type = ParseExpType(str.at(1));
  if (type == ParseExpType::OperatorPlus && str.at(2) == ' ') {
    // expected syntax is (+ lhs rhs)
    const auto first_pos = str.find_first_not_of(' ', 1);
    if (first_pos == std::string::npos) {
      throw invalid_expression();
    }
    const auto first = this->parse_str(str);

  } else if (type == ParseExpType::OperatorMinus && str.at(2) == ' ') {
  } else if (type == ParseExpType::OperatorMul && str.at(2) == ' ') {
  } else if (type == ParseExpType::OperatorDiv && str.at(2) == ' ') {
  } else if (static_cast<char>(type) == '"') {
    // our strings need to be double-quoted
    const auto end_pos = str.find_first_of('"', 2);
    if (end_pos == std::string::npos) {
      throw unmatched_quotes();
    }
    return ParseExp{ParseExpType::Symbol,
                    std::string(str.begin() + 2, str.begin() + end_pos)};
  } else {
    intptr_t val{};
    const auto num =
        std::string_view(str.data() + 1, str.data() + str.size() - 1);
    std::from_chars(num.data(), num.data() + num.size(), val);
    return ParseExp{ParseExpType::Int, val};
  }
  throw unknown_exp_type();
}
} // namespace lang