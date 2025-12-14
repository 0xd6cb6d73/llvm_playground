#pragma once

#include "parser.hpp"

namespace lang {
class Interpreter {
public:
  Interpreter() = default;
  ParseExpVal eval(const ParseExp exp);
};
} // namespace lang