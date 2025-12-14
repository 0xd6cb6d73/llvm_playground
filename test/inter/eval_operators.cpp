#include <cstdint>
#include <gtest/gtest.h>

#include "../../src/inter.hpp"

// Demonstrate some basic assertions
TEST(inter, eval_op_plus) {
  lang::Interpreter inter;
  const auto pack = lang::OperatorPack{
      .op = lang::ParseExpOperator::Plus, .lhs = 1, .rhs = 1};
  const auto val = inter.eval({lang::ParseExpType::Operator, pack});
  EXPECT_EQ(*std::get_if<int32_t>(&val), 2);
}

TEST(inter, eval_op_minus) {
  lang::Interpreter inter;
  const auto pack = lang::OperatorPack{
      .op = lang::ParseExpOperator::Minus, .lhs = 4, .rhs = 2};
  const auto val = inter.eval({lang::ParseExpType::Operator, pack});
  EXPECT_EQ(*std::get_if<int32_t>(&val), 2);
}

TEST(inter, eval_op_mul) {
  lang::Interpreter inter;
  const auto pack =
      lang::OperatorPack{.op = lang::ParseExpOperator::Mul, .lhs = 2, .rhs = 1};
  const auto val = inter.eval({lang::ParseExpType::Operator, pack});
  EXPECT_EQ(*std::get_if<int32_t>(&val), 2);
}

TEST(inter, eval_op_div) {
  lang::Interpreter inter;
  const auto pack =
      lang::OperatorPack{.op = lang::ParseExpOperator::Div, .lhs = 6, .rhs = 3};
  const auto val = inter.eval({lang::ParseExpType::Operator, pack});
  EXPECT_EQ(*std::get_if<int32_t>(&val), 2);
}
