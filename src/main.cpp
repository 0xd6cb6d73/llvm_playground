#include "compiler.hpp"
#include "inter.hpp"

#include "parser.hpp"
import std;

int main() {
  lang::Parser parser;
  lang::Interpreter inter;
  lang::comp::Compiler compiler;
  auto exp = std::make_unique<lang::ParseExp>(parser.parse(std::string(R"((+ 1 1))")));
  const auto ret = inter.eval(*exp);
  const auto comp = compiler.LowerToLLVM(std::move(exp), "main_eval.ll");
  return std::get<std::intptr_t>(ret);
}