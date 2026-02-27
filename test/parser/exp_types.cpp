#include <gtest/gtest.h>

#include "parser.hpp"

TEST(ExpTypes, op_plus) {
  const std::string test("+ 1 1");
  const auto res = lang::get_exp_type(test);
  EXPECT_EQ(lang::ParseExpType::OperatorPlus, res);
}

TEST(ExpTypes, op_minus) {
  const std::string test("- 1 1");
  const auto res = lang::get_exp_type(test);
  EXPECT_EQ(lang::ParseExpType::OperatorMinus, res);
}

TEST(ExpTypes, op_mul) {
  const std::string test("* 1 1");
  const auto res = lang::get_exp_type(test);
  EXPECT_EQ(lang::ParseExpType::OperatorMul, res);
}

TEST(ExpTypes, op_div) {
  const std::string test("/ 1 1");
  const auto res = lang::get_exp_type(test);
  EXPECT_EQ(lang::ParseExpType::OperatorDiv, res);
}

TEST(ExpTypes, op_call) {
  const std::string test("call printf blah");
  const auto res = lang::get_exp_type(test);
  EXPECT_EQ(lang::ParseExpType::FuncCall, res);
}

TEST(ExpTypes, op_set) {
  const std::string test("set foo 1");
  const auto res = lang::get_exp_type(test);
  EXPECT_EQ(lang::ParseExpType::FuncSet, res);
}

TEST(ExpTypes, op_def) {
  const std::string test("def my_call printf");
  const auto res = lang::get_exp_type(test);
  EXPECT_EQ(lang::ParseExpType::FuncDef, res);
}