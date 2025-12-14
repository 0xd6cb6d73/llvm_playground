#pragma once

#include <cstdint>
#include <string>
#include <variant>
#include <vector>

namespace lang {
enum class ParseExpOperator : char {
  Plus = '+',
  Minus = '-',
  Mul = '*',
  Div = '/'
};
struct OperatorPack {
  ParseExpOperator op;
  int32_t lhs;
  int32_t rhs;
};
enum class ParseExpType : uint8_t { Int, Symbol, List, Operator };
struct ParseExp;
using ParseExpVal =
    std::variant<int32_t, std::string, std::vector<ParseExp>, OperatorPack>;
struct ParseExp {
  ParseExpType type;
  ParseExpVal value;
};

class Parser {
public:
  Parser() = default;
  std::vector<uint8_t> parse(const ParseExp &exp);
};
} // namespace lang