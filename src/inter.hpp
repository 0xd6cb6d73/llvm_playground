#pragma once

#include "parser.hpp"

namespace lang {
template <class... Ts> struct overloaded : Ts... {
  using Ts::operator()...;
};

class Interpreter {
public:
  Interpreter() = default;
  ParseExpVal eval(const ParseExp exp);

private:
  std::vector<uint8_t> state;
  // this function only handles the primitive types, not lists or operators
  bool append(const ParseExpVal &val);
  int32_t add(const ParseExpVal *lhs, const ParseExpVal *rhs);
  int32_t minus(const ParseExpVal *lhs, const ParseExpVal *rhs);
  int32_t mul(const ParseExpVal *lhs, const ParseExpVal *rhs);
  int32_t div(const ParseExpVal *lhs, const ParseExpVal *rhs);
  int32_t visit_int32(const ParseExpVal &input);
};
} // namespace lang