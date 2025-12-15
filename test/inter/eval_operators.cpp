#include <cstdint>
#include <gtest/gtest.h>

#include "../../src/inter.hpp"

// Demonstrate some basic assertions
TEST(inter, eval_op_plus) {
  lang::Interpreter inter;

  auto lhs = lang::ParseExpVal(1);
  const auto pack = lang::ParseExp{
      .type = lang::ParseExpType::OperatorPlus, .lhs = &lhs, .rhs = &lhs};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<int32_t>(val), 2);
}

TEST(inter, eval_op_minus) {
  lang::Interpreter inter;
  auto lhs = lang::ParseExpVal(4);
  auto rhs = lang::ParseExpVal(2);
  const auto pack = lang::ParseExp{
      .type = lang::ParseExpType::OperatorMinus, .lhs = &lhs, .rhs = &lhs};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<int32_t>(val), 2);
}

TEST(inter, eval_op_mul) {
  lang::Interpreter inter;
  auto lhs = lang::ParseExpVal(2);
  auto rhs = lang::ParseExpVal(1);
  const auto pack = lang::ParseExp{
      .type = lang::ParseExpType::OperatorMinus, .lhs = &lhs, .rhs = &lhs};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<int32_t>(val), 2);
}

TEST(inter, eval_op_div) {
  lang::Interpreter inter;
  auto lhs = lang::ParseExpVal(6);
  auto rhs = lang::ParseExpVal(3);
  const auto pack = lang::ParseExp{
      .type = lang::ParseExpType::OperatorMinus, .lhs = &lhs, .rhs = &lhs};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<int32_t>(val), 2);
}
