#include <gtest/gtest.h>

#include "parser.hpp"

#include <memory>
#include <string>

TEST(parser, func_single_arg) {
  lang::Parser parser;
  auto ret = parser.parse(R"((call printf "Hello, world!"))");
  const std::unique_ptr<lang::ParseExp> args =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(ret.rhs));
  EXPECT_EQ(ret.type, lang::ParseExpType::FuncCall);
  EXPECT_EQ(std::get<std::string>(ret.lhs), std::string("printf"));
  EXPECT_EQ(args->type, lang::ParseExpType::Symbol);
  EXPECT_EQ(std::get<std::string>(args->lhs), std::string("Hello, world!"));
}

TEST(parser, func_multiple_args) {
  lang::Parser parser;
  const std::string test(R"((call printf ("Hello, %s!" "World")))");
  auto ret = parser.parse(test);
  const std::unique_ptr<lang::ParseExp> args =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(ret.rhs));
  EXPECT_EQ(ret.type, lang::ParseExpType::FuncCall);
  EXPECT_EQ(std::get<std::string>(ret.lhs), std::string("printf"));
  EXPECT_EQ(args->type, lang::ParseExpType::Symbol);
  const std::string hello(R"(Hello, %s!)");
  EXPECT_EQ(std::get<std::string>(args->lhs), hello);
  const std::string world("World");
  EXPECT_EQ(std::get<std::string>(args->rhs), world);
}
