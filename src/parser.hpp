#pragma once

#include <cstdint>
#include <string>
#include <variant>
#include <vector>

namespace lang {
enum class ParseExpType : uint8_t {
  Int,
  Symbol,
  List,
  OperatorPlus,
  OperatorMinus,
  OperatorMul,
  OperatorDiv
};
struct ParseExp;
using ParseExpVal = std::variant<int32_t, std::string, ParseExp>;

struct ParseExp {
  ParseExpType type;
  ParseExpVal *lhs;
  ParseExpVal *rhs;
};

class Parser {
public:
  Parser() = default;
  std::vector<uint8_t> parse(const ParseExp &exp);
};
} // namespace lang