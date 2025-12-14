#include "inter.hpp"

#include "parser.hpp"
#include <exception>
#include <variant>

namespace lang {
class unknown_exp_type : std::exception {};
ParseExpVal Interpreter::eval(const ParseExpVal exp) {
  if (const auto val = std::get_if<int32_t>(&exp)) {
    return *val;
  } else if (const auto val = std::get_if<std::string>(&exp)) {
    return *val;
  } else if (const auto val = std::get_if<std::vector<ParseExp>>(&exp)) {
    return *val;
  } else {
    throw unknown_exp_type();
  }
}
} // namespace lang