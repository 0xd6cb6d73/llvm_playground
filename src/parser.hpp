#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <variant>

namespace lang {
enum class ParseExpType : uint8_t {
  Int,
  Symbol,
  OperatorPlus = '+',
  OperatorMinus = '-',
  OperatorMul = '*',
  OperatorDiv = '/'
};
struct ParseExp;
using ParseExpVal =
    std::variant<intptr_t, std::string, std::unique_ptr<ParseExp>>;

struct ParseExp {
  ParseExpType type;
  ParseExpVal lhs;
  ParseExpVal rhs;
};

struct ParseExpRef {
  ParseExpType type;
  size_t lhs_start;
  size_t lhs_stop;
  size_t rhs_start;
  size_t rhs_stop;
};

class Parser {
public:
  Parser() = default;
  ParseExp parse(const std::string_view str);

private:
  ParseExp parse_str(const std::string_view str);
  ParseExp parse_operands(const std::string_view str);
};
} // namespace lang