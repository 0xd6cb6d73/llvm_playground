#pragma once

#include "parser.hpp"

namespace lang {
class Interpreter {
public:
  Interpreter() = default;
  ParseExpVal eval(const ParseExpVal exp);
};
} // namespace lang