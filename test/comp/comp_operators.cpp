#include <cstdint>
#include <format>
#include <gtest/gtest.h>

#include "compiler.hpp"
#include "parser.hpp"

TEST(compiler, compile_operator_plus) {
  lang::Parser parser;
  auto parsed = std::make_unique<lang::ParseExp>(parser.parse(std::format("(+ {} {})", 1, 2)));
  lang::comp::Compiler compiler;
  compiler.LowerToLLVM(std::move(parsed), "compile_operator_plus.ll");
}

TEST(compiler, operator_plus_mul) {
  lang::Parser parser;
  auto parsed =
      std::make_unique<lang::ParseExp>(parser.parse(std::format("(+ (* {} {}) {})", 1, 2, 3)));
  lang::comp::Compiler compiler;
  compiler.LowerToLLVM(std::move(parsed), "compile_operator_plus_mul.ll");
}