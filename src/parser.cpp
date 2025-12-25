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

ParseExpType get_exp_type(const std::string_view str) {
  const auto type = ParseExpType(str.at(0));
  if (type == ParseExpType::OperatorPlus && str.at(1) == ' ') {
    return type;
  } else if (type == ParseExpType::OperatorMinus && str.at(1) == ' ') {
    return type;
  } else if (type == ParseExpType::OperatorMul && str.at(1) == ' ') {
    return type;
  } else if (type == ParseExpType::OperatorDiv && str.at(1) == ' ') {
    return type;
  } else if (static_cast<char>(type) == '"') {
    return ParseExpType::Symbol;
  }
  const auto first_space_pos = str.find_first_of(' ', 0);
  if (first_space_pos == std::string::npos) {
    return ParseExpType::Int;
  }
  if (const auto name = ExpFuncs(FunName::Call); str.starts_with(name.str)) {
    return ParseExpType::FuncCall;

  } else if (const auto name = ExpFuncs(FunName::Set);
             str.starts_with(name.str)) {
    return ParseExpType::FuncSet;

  } else if (const auto name = ExpFuncs(FunName::Def);
             str.starts_with(name.str)) {
    return ParseExpType::FuncDef;
  }
  throw unknown_exp_type();
}

ParseExp Parser::parse(const std::string_view str) {
  const auto first = str.at(0);
  // we only parse S-expressions, which look like this
  // (operator lhs rhs)
  assert(str.at(0) == '(');
  assert(str.at(str.size() - 1) == ')');
  const std::string_view clipped(str.begin() + 1, str.end() - 1);
  return this->parse_str(clipped);
}

ParseExp Parser::parse_str(const std::string_view str) {
  // parsing needs to be done left to right, this function expects an operator
  // and one or more operands
  const auto type = get_exp_type(str);
  bool is_operator = false;
  switch (type) {
    using enum ParseExpType;
  case Int: {
    const auto ret = this->parse_int(str);
    return ParseExp{ret.type, std::get<intptr_t>(ret.val)};
  }
  case Symbol: {
    // our strings need to be double-quoted
    const auto end_pos = str.find_first_of('"', 1);
    if (end_pos == std::string::npos) {
      throw unmatched_quotes();
    }
    return ParseExp{ParseExpType::Symbol,
                    std::string(str.begin() + 1, str.begin() + end_pos)};
  }
  case OperatorPlus:
    return this->parse_operator(str, type);
  case OperatorMinus:
    return this->parse_operator(str, type);
  case OperatorMul:
    return this->parse_operator(str, type);
  case OperatorDiv:
    return this->parse_operator(str, type);
  case FuncCall: {
  }
  case FuncSet: {
  }
  case FuncDef: {
  } break;
  }
  throw unknown_exp_type();
}

ParseExpSide Parser::parse_int(const std::string_view str) {
  intptr_t val{};
  const std::string_view num(str.data(), str.data() + str.size());
  std::from_chars(num.data(), num.data() + num.size(), val);
  return ParseExpSide{ParseExpType::Int, val};
}

size_t find_end_paren(const std::string_view str) {
  // https://stackoverflow.com/questions/12752225/how-do-i-find-the-position-of-matching-parentheses-or-braces-in-a-given-piece-of
  auto pos = str.find_first_of('(');
  if (pos == std::string::npos) {
    return 0;
  }
  int32_t paren_count = 1;
  while (paren_count > 0) {
    if (str.at(++pos) == '(') {
      paren_count++;
    } else if (str.at(pos) == ')') {
      paren_count--;
    }
  }
  return pos;
}

ParseExp Parser::parse_call(const std::string_view str) { return ParseExp{}; }
ParseExp Parser::parse_set(const std::string_view str) { return ParseExp{}; }
ParseExp Parser::parse_def(const std::string_view str) { return ParseExp{}; }
ParseExp Parser::parse_if(const std::string_view str) { return ParseExp{}; }
ParseExp Parser::parse_while(const std::string_view str) { return ParseExp{}; }
ParseExp Parser::parse_for(const std::string_view str) { return ParseExp{}; }
ParseExp Parser::parse_operator(const std::string_view str,
                                const ParseExpType type) {
  bool is_first_exp = false;
  bool is_second_exp = false;
  // expected syntax is (+ lhs rhs) where lhs and rhs can both either be an
  // expression or a value
  const auto first_pos = str.find_first_not_of(' ', 1);
  if (first_pos == std::string::npos) {
    throw invalid_expression();
  }
  const auto first_sub = str.find_first_of('(');
  if (first_sub <= first_pos) {
    is_first_exp = true;
  }
  const auto first_end_paren = find_end_paren(str);
  const auto second_pos = is_first_exp
                              ? first_end_paren + 2
                              : str.find_first_not_of(' ', first_pos + 1);
  if (second_pos == std::string::npos) {
    throw invalid_expression();
  }
  const auto second_sub = str.find_first_of('(', second_pos);
  if (second_sub <= second_pos) {
    is_second_exp = true;
  }
  const std::string_view first_view(
      str.begin() + (is_first_exp ? first_pos + 1 : first_pos),
      str.begin() + (is_first_exp ? second_pos - 2 : second_pos - 1));
  auto first = !is_first_exp
                   ? this->parse_int(first_view).val
                   : std::make_unique<ParseExp>(this->parse_str(first_view));
  const std::string_view second_view(
      str.begin() + (is_second_exp ? second_pos + 1 : second_pos),
      str.begin() + (is_second_exp ? str.size() - 1 : str.size()));
  // const std::string_view second_view(str.begin() + second_pos, str.end());
  auto second = !is_second_exp
                    ? this->parse_int(second_view).val
                    : std::make_unique<ParseExp>(this->parse_str(second_view));
  return ParseExp{type, std::move(first), std::move(second)};
}
} // namespace lang