#pragma once

#include "parser.hpp"

namespace lang {
class Interpreter {
public:
  Interpreter() = default;
  ParseExpVal eval(const ParseExp &exp);

private:
  intptr_t add(const ParseExpVal &lhs, const ParseExpVal &rhs);
  intptr_t minus(const ParseExpVal &lhs, const ParseExpVal &rhs);
  intptr_t mul(const ParseExpVal &lhs, const ParseExpVal &rhs);
  intptr_t div(const ParseExpVal &lhs, const ParseExpVal &rhs);
  intptr_t visit_int32(const ParseExpVal &input);
};
} // namespace lang