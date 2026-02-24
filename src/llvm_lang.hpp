#pragma once

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Value.h>

#include <memory>
#include <optional>
#include <string>
#include <string_view>

class LangLLVM {
public:
  LangLLVM();
  void exec(const std::string_view program);

private:
  std::unique_ptr<llvm::LLVMContext> ctx;
  std::unique_ptr<llvm::Module> mod;
  std::unique_ptr<llvm::IRBuilder<>> builder;
  llvm::Function *curr_fn;
  std::unique_ptr<llvm::raw_fd_ostream> out_fd;

  void moduleInit();
  void compile(std::optional<std::string> ast);
  llvm::Value *gen();
  void setup_extern_fn(const std::string_view name, llvm::FunctionType *typ);
  llvm::Function *create_function(const std::string_view name, llvm::FunctionType *typ);
  llvm::Function *create_prototype(const std::string_view name, llvm::FunctionType *typ);
  void create_block(llvm::Function *fn);
  llvm::BasicBlock *create_bb(const std::string_view name, llvm::Function *fn = nullptr);
  void saveModuleToFile(const std::string_view file_name);
};