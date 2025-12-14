#include "inter.hpp"

#include "parser.hpp"
#include <exception>
#include <string>
#include <variant>

namespace lang {
class unknown_exp_type : std::exception {};
ParseExpVal Interpreter::eval(const ParseExp exp) {
  if (exp.type == ParseExpType::Operator) {
    if (const auto val = std::get_if<OperatorPack>(&exp.value)) {
      if (val->op == ParseExpOperator::Plus) {
        return val->lhs + val->rhs;
      } else if (val->op == ParseExpOperator::Minus) {
        return val->lhs - val->rhs;
      } else if (val->op == ParseExpOperator::Mul) {
        return val->lhs * val->rhs;
      } else if (val->op == ParseExpOperator::Div) {
        return val->lhs / val->rhs;
      }
    }
    throw unknown_exp_type();
  } else if (exp.type == ParseExpType::Int) {
    return *std::get_if<int32_t>(&exp.value);
  } else if (exp.type == ParseExpType::Symbol) {
    return *std::get_if<std::string>(&exp.value);
  } else if (exp.type == ParseExpType::List) {
    return *std::get_if<std::vector<ParseExp>>(&exp.value);
  }
  throw unknown_exp_type();
}
} // namespace lang