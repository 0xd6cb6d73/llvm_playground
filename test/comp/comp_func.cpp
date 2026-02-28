#include <gtest/gtest.h>

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>

#include "compiler.hpp"
#include "parser.hpp"

#include <memory>
#include <string>

namespace lang {
class CompileFuncTest : public testing::Test {
protected:
  lang::Parser parser;
  lang::comp::Compiler compiler;
  llvm::ExecutionEngine *interpreter;
  std::unique_ptr<llvm::Module> mod;
  CompileFuncTest() {}

  ParseExp Parse(const std::string_view str) { return this->parser.parse(str); }

  bool Lower(std::unique_ptr<ParseExp> &&ast, const std::string_view file_name) {
    this->mod = std::move(this->compiler.LowerToLLVM(std::move(ast), file_name));
    return this->mod != nullptr;
  }

  llvm::GenericValue Run() {
    std::string err;
    this->interpreter = llvm::EngineBuilder(std::move(this->mod))
                            .setEngineKind(llvm::EngineKind::Interpreter)
                            .setErrorStr(&err)
                            .create();
    auto main = this->interpreter->FindFunctionNamed("main");
    return this->interpreter->runFunction(main, {});
  }
};

TEST_F(CompileFuncTest, printf_single_arg) {
  const std::string test(R"((call printf ("Hello, %s!" "World")))");
  auto parsed = std::make_unique<lang::ParseExp>(Parse(test));
  ASSERT_TRUE(Lower(std::move(parsed), "compile_operator_plus.ll"));
  Run();
}
} // namespace lang
