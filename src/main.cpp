#include "inter.hpp"

#include "parser.hpp"
#include <cstdint>

int main() {
  lang::Parser parser;
  lang::Interpreter inter;
  const auto exp = parser.parse(std::string(R"((+ 1 1))"));
  const auto ret = inter.eval(exp);
  return std::get<intptr_t>(ret);
}