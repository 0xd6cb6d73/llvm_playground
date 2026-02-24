#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <variant>

namespace lang {
namespace impl {
constexpr std::array<std::string, 6> ExpFunctions{std::string("call"),  std::string("set"),
                                                  std::string("def"),   std::string("if"),
                                                  std::string("while"), std::string("for")};
}
enum class ParseExpType : uint8_t {
  Int,
  Symbol,
  OperatorPlus = '+',
  OperatorMinus = '-',
  OperatorMul = '*',
  OperatorDiv = '/',
  FuncCall,
  FuncSet,
  FuncDef,
};

enum class FunName : uint8_t { Call = 0, Set = 1, Def = 2, If = 3, While = 4, For = 5 };
class ExpFuncs {
public:
  ExpFuncs(FunName name) { this->str = impl::ExpFunctions.at(static_cast<uint8_t>(name)); };
  std::string_view str;
};
struct ParseExp;
using ParseExpVal = std::variant<intptr_t, std::string, std::unique_ptr<ParseExp>>;

struct ParseExp {
  ParseExpType type;
  ParseExpVal lhs;
  ParseExpVal rhs;
};

struct ParseExpSide {
  ParseExpType type;
  ParseExpVal val;
};

size_t find_end_paren(const std::string_view str);

class Parser {
public:
  Parser() = default;
  ParseExp parse(const std::string_view str);

private:
  ParseExp parse_str(const std::string_view str);
  ParseExpSide parse_int(const std::string_view str);
  ParseExp parse_call(const std::string_view str);
  ParseExp parse_set(const std::string_view str);
  ParseExp parse_def(const std::string_view str);
  ParseExp parse_if(const std::string_view str);
  ParseExp parse_while(const std::string_view str);
  ParseExp parse_for(const std::string_view str);
  ParseExp parse_operator(const std::string_view str, const ParseExpType type);
};
} // namespace lang