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
  const std::string_view clipped(str.begin() + 1, str.end() - 1);
  return this->parse_str(clipped);
}

ParseExp Parser::parse_str(const std::string_view str) {
  const auto type = ParseExpType(str.at(0));
  if (type == ParseExpType::OperatorPlus && str.at(1) == ' ') {
    // expected syntax is (+ lhs rhs) where either lhs and/or rhs can be an
    // expression
    const auto first_pos = str.find_first_not_of(' ', 1);
    if (first_pos == std::string::npos) {
      throw invalid_expression();
    }
    const auto second_pos = str.find_first_not_of(' ', first_pos + 1);
    if (second_pos == std::string::npos) {
      throw invalid_expression();
    }
    const auto is_first_sub = str.find_first_of('(', 1);
    if (is_first_sub != std::string::npos) {
      const auto end_paren = str.find_first_of(')', first_pos + 1);
      const std::string_view sub(str.begin() + second_pos,
                                 str.begin() + end_paren);
      const auto first = this->parse_str(sub);
      const std::string_view second_view(str.begin() + end_paren + 2,
                                         str.end());
      const auto second = this->parse_str(second_view);
      const ParseExp ret{};
    }
    const auto first = this->parse_str(std::string_view(
        str.begin() + first_pos, str.begin() + second_pos - 1));
    const auto third_pos = str.find_first_not_of(' ', second_pos + 1);
    if (third_pos != std::string::npos) {
      const auto end_paren = str.find_first_of(')', second_pos + 1);
      const std::string_view sub(str.begin() + third_pos,
                                 str.begin() + end_paren);
      const auto sub_exp = this->parse_str(sub);
    }
    const std::string_view second_view(str.begin() + second_pos, str.end());
    const auto second = this->parse_str(second_view);
    return ParseExp{ParseExpType::OperatorPlus, std::get<intptr_t>(first.lhs),
                    std::get<intptr_t>(second.lhs)};

  } else if (type == ParseExpType::OperatorMinus && str.at(1) == ' ') {
  } else if (type == ParseExpType::OperatorMul && str.at(1) == ' ') {
  } else if (type == ParseExpType::OperatorDiv && str.at(1) == ' ') {
  } else if (static_cast<char>(type) == '"') {
    // our strings need to be double-quoted
    const auto end_pos = str.find_first_of('"', 1);
    if (end_pos == std::string::npos) {
      throw unmatched_quotes();
    }
    return ParseExp{ParseExpType::Symbol,
                    std::string(str.begin() + 1, str.begin() + end_pos)};
  } else {
    intptr_t val{};
    const std::string_view num(str.data(), str.data() + str.size());
    std::from_chars(num.data(), num.data() + num.size(), val);
    return ParseExp{ParseExpType::Int, val};
  }
  throw unknown_exp_type();
}

ParseExp Parser::parse_operands(const std::string_view str) {
  return ParseExp{};
}
} // namespace lang