#pragma once

#include "parser.hpp"

import std;

namespace lang {
class Interpreter {
public:
  Interpreter() = default;
  ParseExpVal eval(const ParseExp &exp);

private:
  std::intptr_t add(const ParseExpVal &lhs, const ParseExpVal &rhs);
  std::intptr_t minus(const ParseExpVal &lhs, const ParseExpVal &rhs);
  std::intptr_t mul(const ParseExpVal &lhs, const ParseExpVal &rhs);
  std::intptr_t div(const ParseExpVal &lhs, const ParseExpVal &rhs);
  std::intptr_t visit_int32(const ParseExpVal &input);
};
} // namespace lang