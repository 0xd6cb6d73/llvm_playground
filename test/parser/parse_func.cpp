#include <gtest/gtest.h>

#include "../../src/parser.hpp"

TEST(parser, parse_func_call) {
  lang::Parser parser;
  auto ret = parser.parse(R"((call printf "Hello, world!"))");
  const std::unique_ptr<lang::ParseExp> args =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(ret.rhs));
  EXPECT_EQ(ret.type, lang::ParseExpType::FuncCall);
  EXPECT_EQ(std::get<std::string>(ret.lhs), std::string("printf"));
  EXPECT_EQ(args->type, lang::ParseExpType::Symbol);
  EXPECT_EQ(std::get<std::string>(args->lhs), std::string("Hello, world!"));
}