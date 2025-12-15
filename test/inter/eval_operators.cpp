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

TEST(inter, eval_op_plus_plus) {
  lang::Interpreter inter;

  auto lhs = lang::ParseExpVal(1);
  auto pack_1 = lang::ParseExpVal(lang::ParseExp{
      .type = lang::ParseExpType::OperatorPlus, .lhs = &lhs, .rhs = &lhs});
  const auto pack = lang::ParseExp{
      .type = lang::ParseExpType::OperatorPlus, .lhs = &lhs, .rhs = &pack_1};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<int32_t>(val), 3);
}

TEST(inter, eval_op_minus) {
  lang::Interpreter inter;
  auto lhs = lang::ParseExpVal(8);
  auto rhs = lang::ParseExpVal(6);
  const auto pack = lang::ParseExp{
      .type = lang::ParseExpType::OperatorMinus, .lhs = &lhs, .rhs = &rhs};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<int32_t>(val), 2);
}

TEST(inter, eval_op_minus_minus) {
  lang::Interpreter inter;
  auto lhs = lang::ParseExpVal(8);
  auto rhs = lang::ParseExpVal(6);
  auto pack_1 = lang::ParseExpVal(lang::ParseExp{
      .type = lang::ParseExpType::OperatorMinus, .lhs = &lhs, .rhs = &rhs});
  const auto pack = lang::ParseExp{
      .type = lang::ParseExpType::OperatorMinus, .lhs = &lhs, .rhs = &pack_1};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<int32_t>(val), 6);
}

TEST(inter, eval_op_mul) {
  lang::Interpreter inter;
  auto lhs = lang::ParseExpVal(2);
  auto rhs = lang::ParseExpVal(1);
  const auto pack = lang::ParseExp{
      .type = lang::ParseExpType::OperatorMul, .lhs = &lhs, .rhs = &rhs};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<int32_t>(val), 2);
}

TEST(inter, eval_op_mul_mul) {
  lang::Interpreter inter;
  auto lhs = lang::ParseExpVal(2);
  auto rhs = lang::ParseExpVal(1);
  auto pack_1 = lang::ParseExpVal(lang::ParseExp{
      .type = lang::ParseExpType::OperatorMul, .lhs = &lhs, .rhs = &rhs});
  const auto pack = lang::ParseExp{
      .type = lang::ParseExpType::OperatorMul, .lhs = &lhs, .rhs = &pack_1};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<int32_t>(val), 4);
}

TEST(inter, eval_op_div) {
  lang::Interpreter inter;
  auto lhs = lang::ParseExpVal(6);
  auto rhs = lang::ParseExpVal(3);
  const auto pack = lang::ParseExp{
      .type = lang::ParseExpType::OperatorDiv, .lhs = &lhs, .rhs = &rhs};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<int32_t>(val), 2);
}

TEST(inter, eval_op_div_div) {
  lang::Interpreter inter;
  auto lhs = lang::ParseExpVal(6);
  auto rhs = lang::ParseExpVal(3);
  auto pack_1 = lang::ParseExpVal(lang::ParseExp{
      .type = lang::ParseExpType::OperatorDiv, .lhs = &lhs, .rhs = &rhs});
  const auto pack = lang::ParseExp{
      .type = lang::ParseExpType::OperatorDiv, .lhs = &lhs, .rhs = &pack_1};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<int32_t>(val), 3);
}
