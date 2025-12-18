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

struct ParseExpSide {
  ParseExpType type;
  ParseExpVal val;
};

class Parser {
public:
  Parser() = default;
  ParseExp parse(const std::string_view str);

private:
  ParseExp parse_str(const std::string_view str);
  ParseExpSide parse_member(const std::string_view str);
};
} // namespace lang