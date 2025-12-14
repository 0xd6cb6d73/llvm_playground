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
ParseExpVal Interpreter::eval(const ParseExp exp) {
  if (exp.type == ParseExpType::Operator) {
    if (const auto val = std::get_if<OperatorPack>(&exp.value)) {
      std::cout << "found operator ";
      if (val->op == ParseExpOperator::Plus) {
        std::cout << "plus" << std::endl;
        return val->lhs + val->rhs;
      } else if (val->op == ParseExpOperator::Minus) {
        std::cout << "minus" << std::endl;
        return val->lhs - val->rhs;
      } else if (val->op == ParseExpOperator::Mul) {
        std::cout << "mul" << std::endl;
        return val->lhs * val->rhs;
      } else if (val->op == ParseExpOperator::Div) {
        std::cout << "div" << std::endl;
        return val->lhs / val->rhs;
      }
    }
    throw unknown_exp_type();
  } else if (exp.type == ParseExpType::Int) {
    return *std::get_if<int32_t>(&exp.value);
  } else if (exp.type == ParseExpType::Symbol) {
    return *std::get_if<std::string>(&exp.value);
  } else if (exp.type == ParseExpType::List) {
    std::cout << "found list" << std::endl;
    for (const auto &item : *std::get_if<std::vector<ParseExp>>(&exp.value)) {
      const auto ret = this->eval(item);
      this->append(ret);
    }
    std::cout << "state contents: " << std::endl;
    for (const uint8_t &item : this->state) {
      std::cout << std::to_string(item) << std::endl;
    }
    return std::string(
        std::string_view(reinterpret_cast<const char *>(this->state.data()),
                         this->state.size()));
  }
  throw unknown_exp_type();
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