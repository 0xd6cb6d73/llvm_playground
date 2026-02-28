#include <gtest/gtest.h>

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>

import std;

#include "compiler.hpp"
#include "parser.hpp"

TEST(compiler, compile_operator_plus) {
  lang::Parser parser;
  auto parsed = std::make_unique<lang::ParseExp>(parser.parse(std::format("(+ {} {})", 1, 2)));
  lang::comp::Compiler compiler;
  auto mod = compiler.LowerToLLVM(std::move(parsed), "compile_operator_plus.ll");
}

TEST(compiler, operator_plus_mul) {
  lang::Parser parser;
  auto parsed =
      std::make_unique<lang::ParseExp>(parser.parse(std::format("(+ (* {} {}) {})", 1, 2, 3)));
  lang::comp::Compiler compiler;
  auto mod = compiler.LowerToLLVM(std::move(parsed), "compile_operator_plus_mul.ll");
  std::string err;
  auto exec = llvm::EngineBuilder(std::move(mod))
                  .setEngineKind(llvm::EngineKind::Interpreter)
                  .setErrorStr(&err)
                  .create();
  auto main = exec->FindFunctionNamed("main");
  const auto res = exec->runFunction(main, {});
  EXPECT_EQ(7, res.IntVal.getLimitedValue());
}