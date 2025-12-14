#pragma once

#include "parser.hpp"

namespace lang {
class Interpreter {
public:
  Interpreter() = default;
  ParseExpVal eval(const ParseExp exp);

private:
  std::vector<uint8_t> state;
  // this function only handles the primitive types, not lists or operators
  bool append(const ParseExpVal &val);
};
} // namespace lang