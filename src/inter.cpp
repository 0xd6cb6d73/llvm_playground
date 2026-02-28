#include "inter.hpp"

#include "parser.hpp"
#include "shared.hpp"
import std;

namespace lang {
class unaddable_type : std::exception {};
ParseExpVal Interpreter::eval(const ParseExp &exp) {
  if (exp.type == ParseExpType::OperatorPlus) {
    return this->add(exp.lhs, exp.rhs);
  } else if (exp.type == ParseExpType::OperatorMinus) {
    return this->minus(exp.lhs, exp.rhs);
  } else if (exp.type == ParseExpType::OperatorMul) {
    return this->mul(exp.lhs, exp.rhs);
  } else if (exp.type == ParseExpType::OperatorDiv) {
    return this->div(exp.lhs, exp.rhs);
  } else if (exp.type == ParseExpType::Int) {
    return std::get<std::intptr_t>(exp.lhs);
  } else if (exp.type == ParseExpType::Symbol) {
    return std::get<std::string>(exp.lhs);
  } else {
    throw unknown_exp_type();
  }
}

std::intptr_t Interpreter::add(const ParseExpVal &lhs, const ParseExpVal &rhs) {
  const auto left_val = this->visit_int32(lhs);
  const auto right_val = this->visit_int32(rhs);
  return left_val + right_val;
}

std::intptr_t Interpreter::minus(const ParseExpVal &lhs, const ParseExpVal &rhs) {
  const auto left_val = this->visit_int32(lhs);
  const auto right_val = this->visit_int32(rhs);
  return left_val - right_val;
}

std::intptr_t Interpreter::mul(const ParseExpVal &lhs, const ParseExpVal &rhs) {
  const auto left_val = this->visit_int32(lhs);
  const auto right_val = this->visit_int32(rhs);
  return left_val * right_val;
}

std::intptr_t Interpreter::div(const ParseExpVal &lhs, const ParseExpVal &rhs) {
  const auto left_val = this->visit_int32(lhs);
  const auto right_val = this->visit_int32(rhs);
  return left_val / right_val;
}

std::intptr_t Interpreter::visit_int32(const ParseExpVal &input) {
  return std::visit(overloaded{
                        [this](const std::intptr_t val) -> std::intptr_t { return val; },
                        [this](const std::string &val) -> std::intptr_t {
                          return static_cast<std::intptr_t>(std::stoi(val));
                        },
                        [this](const std::unique_ptr<ParseExp> &val) -> std::intptr_t {
                          return std::get<std::intptr_t>(this->eval(*val));
                        },
                    },
                    input);
}
} // namespace lang