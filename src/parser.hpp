#pragma once

#include <cstdint>
#include <string>
#include <variant>
#include <vector>

namespace lang {
enum class ParseExpType : uint8_t { Int, Symbol, List };
struct ParseExp;
using ParseExpVal = std::variant<int32_t, std::string, std::vector<ParseExp>>;
struct ParseExp {
  ParseExpType type;
  ParseExpVal value;
};

class Parser {
public:
  Parser() = default;
  std::vector<uint8_t> parse(const ParseExp &exp);
};
} // namespace lang