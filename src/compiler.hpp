#pragma once

#include "parser.hpp"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include <cstdint>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Value.h>
#include <memory>

namespace lang::comp {
class Compiler {
public:
  Compiler() = default;
  std::unique_ptr<llvm::Module>
  LowerToLLVM(std::unique_ptr<ParseExp> ast,
              std::optional<const std::string_view> file_name = std::nullopt);

private:
  std::unique_ptr<llvm::LLVMContext> ctx = std::make_unique<llvm::LLVMContext>();
  std::unique_ptr<llvm::Module> mod = std::make_unique<llvm::Module>("lang::comp", *this->ctx);
  std::unique_ptr<llvm::IRBuilder<>> builder = std::make_unique<llvm::IRBuilder<>>(*this->ctx);

  void lower(std::unique_ptr<ParseExp> ast);
  void insert_function(const std::string_view name, llvm::FunctionType *signature,
                       llvm::Function::LinkageTypes link,
                       std::optional<const std::string_view> bb_name);
  void insert_main();
  llvm::Value *insert_int(const intptr_t val);
  llvm::Value *insert_str(const std::string_view str);
  llvm::Value *insert_op(std::unique_ptr<ParseExp> exp);
};
} // namespace lang::comp