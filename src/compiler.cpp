#include "compiler.hpp"

#include "parser.hpp"
#include "shared.hpp"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <stdexcept>
#include <string>
#include <utility>

namespace lang::comp {
void Compiler::insert_function(const std::string_view name, llvm::FunctionType *signature,
                               llvm::Function::LinkageTypes link, const std::string_view bb_name) {
  auto func = this->mod->getFunction(name);
  if (func == nullptr) {
    func = llvm::Function::Create(signature, link, name, *this->mod);
    if (llvm::verifyFunction(*func)) {
      throw std::runtime_error("Function creation error");
    }
  }
  auto *bb = llvm::BasicBlock::Create(*this->ctx, bb_name, func);
  this->builder->SetInsertPoint(bb);
}
void Compiler::insert_main() {
  // main returns int and doesn't take any arguments
  auto type = llvm::FunctionType::get(this->builder->getInt32Ty(), false);
  const std::string name = "main";
  this->insert_function(name, type, llvm::Function::ExternalLinkage, "entry");
}

llvm::Value *Compiler::insert_op(std::unique_ptr<ParseExp> exp) {
  auto *lhs = std::visit(
      overloaded{
          [this](const intptr_t val) -> llvm::Value * {
            return llvm::ConstantInt::get(llvm::Type::getInt64Ty(*this->ctx), val);
          },
          [this](const std::string &val) -> llvm::Value * {
            return llvm::ConstantInt::get(llvm::Type::getInt64Ty(*this->ctx), std::stoll(val));
          },
          [this](std::unique_ptr<ParseExp> &val) -> llvm::Value * {
            return this->insert_op(std::move(val));
          },
      },
      exp->lhs);

  auto *rhs = std::visit(
      overloaded{
          [this](const intptr_t val) -> llvm::Value * {
            return llvm::ConstantInt::get(llvm::Type::getInt64Ty(*this->ctx), val);
          },
          [this](const std::string &val) -> llvm::Value * {
            return llvm::ConstantInt::get(llvm::Type::getInt64Ty(*this->ctx), std::stoll(val));
          },
          [this](std::unique_ptr<ParseExp> &val) -> llvm::Value * {
            return this->insert_op(std::move(val));
          },
      },
      exp->rhs);
  // insert the operator
  switch (exp->type) {
    using enum ParseExpType;
  case Int: {
    std::runtime_error("Not implemented");
  }
  case Symbol: {
    std::runtime_error("Not implemented");
  }
  case OperatorPlus: {
    auto val = this->builder->CreateAdd(lhs, rhs);
    // this->builder->Insert(val);
    return val;
  }
  case OperatorMinus: {
    auto val = this->builder->CreateSub(lhs, rhs);
    // this->builder->Insert(val);
    return val;
  }
  case OperatorMul: {
    auto val = this->builder->CreateMul(lhs, rhs);
    // this->builder->Insert(val);
    return val;
  }
  case OperatorDiv: {
    auto val = this->builder->CreateUDiv(lhs, rhs);
    // this->builder->Insert(val);
    return val;
  }
  case FuncCall: {
    std::runtime_error("Not implemented");
  }
  case FuncSet: {
    std::runtime_error("Not implemented");
  }
  case FuncDef: {
    std::runtime_error("Not implemented");
  }
    std::unreachable();
  }
}
// only basic arithmetic operations are currently supported by this very simple logic
void Compiler::lower(std::unique_ptr<ParseExp> ast) {
  this->insert_main();
  auto val = this->insert_op(std::move(ast));
  auto ret = this->builder->CreateRet(val);
  // this->builder->Insert(ret);
}

std::unique_ptr<llvm::Module>
Compiler::LowerToLLVM(std::unique_ptr<ParseExp> ast,
                      std::optional<const std::string_view> file_name) {
  // for now we can only process basic arithmetic expresssions, the result of which we return from
  // main
  this->lower(std::move(ast));
  if (file_name) { //
    std::error_code error_code;
    auto fd = llvm::raw_fd_ostream(file_name.value(), error_code);
    this->mod->print(fd, nullptr);
  }
  return std::move(this->mod);
}
} // namespace lang::comp