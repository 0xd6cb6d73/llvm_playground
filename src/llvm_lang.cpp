#include "llvm_lang.hpp"

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
#include <vector>

LangLLVM::LangLLVM() { this->moduleInit(); };

void LangLLVM::exec(const std::string_view program) {
  this->compile(std::nullopt);
  this->mod->print(llvm::outs(), nullptr);
  this->saveModuleToFile(std::string("./out.ll"));
}

void LangLLVM::moduleInit() {
  this->ctx = std::make_unique<llvm::LLVMContext>();
  this->mod = std::make_unique<llvm::Module>("LangLLVM", *this->ctx);
  this->builder = std::make_unique<llvm::IRBuilder<>>(*this->ctx);
}

void LangLLVM::compile(std::optional<std::string> ast) {
  this->curr_fn = create_function(
      "main", llvm::FunctionType::get(this->builder->getInt32Ty(), false));

  auto byte_ptr_typ = llvm::PointerType::get(*this->ctx, 0); // opaque ptr
  auto printf_typ =
      llvm::FunctionType::get(this->builder->getInt32Ty(), byte_ptr_typ, true);
  this->setup_extern_fn("printf", printf_typ);
  auto result = this->gen();
  this->builder->CreateRet(this->builder->getInt32(0));
}

llvm::Value *LangLLVM::gen() { // return this->builder->getInt32(0);
  auto str = this->builder->CreateGlobalString("Hello, world!\n");
  auto printf_fn = this->mod->getFunction("printf");
  std::vector<llvm::Value *> args{str};
  return this->builder->CreateCall(printf_fn, args);
}

void LangLLVM::setup_extern_fn(const std::string_view name,
                               llvm::FunctionType *typ) {
  this->mod->getOrInsertFunction(name, typ);
}

llvm::Function *LangLLVM::create_function(const std::string_view name,
                                          llvm::FunctionType *typ) {
  auto fn = this->mod->getFunction(name);
  if (fn == nullptr) {
    fn = create_prototype(name, typ);
  }
  this->create_block(fn);
  return fn;
}

llvm::Function *LangLLVM::create_prototype(const std::string_view name,
                                           llvm::FunctionType *typ) {
  auto fn = llvm::Function::Create(typ, llvm::Function::ExternalLinkage, name,
                                   *this->mod);
  llvm::verifyFunction(*fn);
  return fn;
}

void LangLLVM::create_block(llvm::Function *fn) {
  auto entry = this->create_bb("entry", fn);
  this->builder->SetInsertPoint(entry);
}

llvm::BasicBlock *LangLLVM::create_bb(const std::string_view name,
                                      llvm::Function *fn) {
  return llvm::BasicBlock::Create(*this->ctx, name, fn);
}

void LangLLVM::saveModuleToFile(const std::string_view file_name) {
  std::error_code error_code;
  this->out_fd = std::make_unique<llvm::raw_fd_ostream>(file_name, error_code);
  this->mod->print(*this->out_fd, nullptr);
}
