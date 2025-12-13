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
#include <system_error>

class LangLLVM {
public:
  LangLLVM() { this->moduleInit(); };
  void exec(const std::string_view program) {
    this->compile(std::nullopt);
    this->mod->print(llvm::outs(), nullptr);
    this->saveModuleToFile(std::string("./out.ll"));
  }

private:
  std::unique_ptr<llvm::LLVMContext> ctx;
  std::unique_ptr<llvm::Module> mod;
  std::unique_ptr<llvm::IRBuilder<>> builder;
  llvm::Function *fn;
  void moduleInit() {
    this->ctx = std::make_unique<llvm::LLVMContext>();
    this->mod = std::make_unique<llvm::Module>("LangLLVM", *this->ctx);
    this->builder = std::make_unique<llvm::IRBuilder<>>(*this->ctx);
  }
  void compile(std::optional<std::string> ast) {
    fn = create_function(
        "main", llvm::FunctionType::get(this->builder->getInt32Ty(), false));
    auto result = this->gen();
    auto typ_result =
        this->builder->CreateIntCast(result, this->builder->getInt32Ty(), true);
    this->builder->CreateRet(typ_result);
  }
  llvm::Value *gen() { // return this->builder->getInt32(0);
    return this->builder->CreateGlobalString("Hello, world!\n");
  };
  llvm::Function *create_function(const std::string_view name,
                                  llvm::FunctionType *typ) {
    auto fn = this->mod->getFunction(name);
    if (fn == nullptr) {
      fn = create_prototype(name, typ);
    }
    this->create_block(fn);
    return fn;
  }
  llvm::Function *create_prototype(const std::string_view name,
                                   llvm::FunctionType *typ) {
    auto fn = llvm::Function::Create(typ, llvm::Function::ExternalLinkage, name,
                                     *this->mod);
    llvm::verifyFunction(*fn);
    return fn;
  }
  void create_block(llvm::Function *fn) {
    auto entry = this->create_bb("entry", fn);
    this->builder->SetInsertPoint(entry);
  }
  llvm::BasicBlock *create_bb(const std::string_view name,
                              llvm::Function *fn = nullptr) {
    return llvm::BasicBlock::Create(*this->ctx, name, fn);
  }
  void saveModuleToFile(const std::string_view file_name) {
    std::error_code error_code;
    llvm::raw_fd_ostream out_ll(file_name, error_code);
    this->mod->print(out_ll, nullptr);
  }
};