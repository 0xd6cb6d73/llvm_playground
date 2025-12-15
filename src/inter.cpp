#include "inter.hpp"

#include "parser.hpp"
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <span>
#include <string>
#include <variant>
#include <vector>

namespace lang {
class unknown_exp_type : std::exception {};
class unaddable_type : std::exception {};
ParseExpVal Interpreter::eval(const ParseExp exp) {
  if (exp.type == ParseExpType::OperatorPlus) {
    return this->add(exp.lhs, exp.rhs);
  } else if (exp.type == ParseExpType::OperatorMinus) {
    return this->minus(exp.lhs, exp.rhs);
  } else if (exp.type == ParseExpType::OperatorMul) {
    return this->mul(exp.lhs, exp.rhs);
  } else if (exp.type == ParseExpType::OperatorDiv) {
    return this->div(exp.lhs, exp.rhs);
  } else if (exp.type == ParseExpType::Int) {
    return std::get<int32_t>(*exp.lhs);
  } else if (exp.type == ParseExpType::Symbol) {
    return std::get<std::string>(*exp.lhs);
  } else {
    throw unknown_exp_type();
  }
}

int32_t Interpreter::add(const ParseExpVal *lhs, const ParseExpVal *rhs) {
  const auto left_val = this->visit_int32(*lhs);
  const auto right_val = this->visit_int32(*rhs);
  return left_val + right_val;
}

int32_t Interpreter::minus(const ParseExpVal *lhs, const ParseExpVal *rhs) {
  const auto left_val = this->visit_int32(*lhs);
  const auto right_val = this->visit_int32(*rhs);
  return left_val - right_val;
}

int32_t Interpreter::mul(const ParseExpVal *lhs, const ParseExpVal *rhs) {
  const auto left_val = this->visit_int32(*lhs);
  const auto right_val = this->visit_int32(*rhs);
  return left_val * right_val;
}

int32_t Interpreter::div(const ParseExpVal *lhs, const ParseExpVal *rhs) {
  const auto left_val = this->visit_int32(*lhs);
  const auto right_val = this->visit_int32(*rhs);
  return left_val / right_val;
}

int32_t Interpreter::visit_int32(const ParseExpVal &input) {
  return std::visit(overloaded{
                        [this](const int32_t val) -> int32_t { return val; },
                        [this](const std::string &val) -> int32_t {
                          return static_cast<int32_t>(std::stoi(val));
                        },
                        [this](ParseExp val) -> int32_t {
                          return std::get<int32_t>(this->eval(val));
                        },
                    },
                    input);
}

bool Interpreter::append(const ParseExpVal &val) {
  if (const auto cont = std::get_if<int32_t>(&val)) {
    const auto old = this->state.size();
    std::cout << "state size before: " << old << std::endl;
    this->state.resize(old + sizeof(int32_t));
    std::cout << "state size after: " << this->state.size() << std::endl;
    std::cout << "state contains: " << std::to_string(*this->state.data() + old)
              << std::endl;
    return memcpy(std::next(this->state.data(), old), cont, sizeof(int32_t)) !=
           nullptr;
  } else if (const auto cont = std::get_if<std::string>(&val)) {
    const auto data = std::span<const uint8_t>{
        reinterpret_cast<const uint8_t *>(cont->data()), cont->size()};
    std::ranges::copy(data, this->state.begin() + this->state.size());
    return true;
  }
  return false;
}
} // namespace lang