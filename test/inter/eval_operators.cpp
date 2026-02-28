#include <gtest/gtest.h>

#include "../../src/inter.hpp"

// Demonstrate some basic assertions
TEST(inter, eval_op_plus) {
  lang::Interpreter inter;
  const auto pack = lang::ParseExp{.type = lang::ParseExpType::OperatorPlus,
                                   .lhs = lang::ParseExpVal(1),
                                   .rhs = lang::ParseExpVal(1)};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<std::intptr_t>(val), 2);
}

TEST(inter, eval_op_plus_plus) {
  lang::Interpreter inter;
  auto pack_1 =
      std::make_unique<lang::ParseExp>(lang::ParseExp{.type = lang::ParseExpType::OperatorPlus,
                                                      .lhs = lang::ParseExpVal(1),
                                                      .rhs = lang::ParseExpVal(1)});
  const auto pack = lang::ParseExp{.type = lang::ParseExpType::OperatorPlus,
                                   .lhs = lang::ParseExpVal(1),
                                   .rhs = std::move(pack_1)};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<std::intptr_t>(val), 3);
}

TEST(inter, eval_op_minus) {
  lang::Interpreter inter;
  const auto pack = lang::ParseExp{.type = lang::ParseExpType::OperatorMinus,
                                   .lhs = lang::ParseExpVal(8),
                                   .rhs = lang::ParseExpVal(6)};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<std::intptr_t>(val), 2);
}

TEST(inter, eval_op_minus_minus) {
  lang::Interpreter inter;
  auto pack_1 =
      std::make_unique<lang::ParseExp>(lang::ParseExp{.type = lang::ParseExpType::OperatorMinus,
                                                      .lhs = lang::ParseExpVal(8),
                                                      .rhs = lang::ParseExpVal(6)});
  const auto pack = lang::ParseExp{.type = lang::ParseExpType::OperatorMinus,
                                   .lhs = lang::ParseExpVal(8),
                                   .rhs = std::move(pack_1)};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<std::intptr_t>(val), 6);
}

TEST(inter, eval_op_mul) {
  lang::Interpreter inter;
  const auto pack = lang::ParseExp{.type = lang::ParseExpType::OperatorMul,
                                   .lhs = lang::ParseExpVal(2),
                                   .rhs = lang::ParseExpVal(1)};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<std::intptr_t>(val), 2);
}

TEST(inter, eval_op_mul_mul) {
  lang::Interpreter inter;
  auto pack_1 =
      std::make_unique<lang::ParseExp>(lang::ParseExp{.type = lang::ParseExpType::OperatorMul,
                                                      .lhs = lang::ParseExpVal(2),
                                                      .rhs = lang::ParseExpVal(1)});
  const auto pack = lang::ParseExp{.type = lang::ParseExpType::OperatorMul,
                                   .lhs = lang::ParseExpVal(2),
                                   .rhs = std::move(pack_1)};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<std::intptr_t>(val), 4);
}

TEST(inter, eval_op_div) {
  lang::Interpreter inter;
  const auto pack = lang::ParseExp{.type = lang::ParseExpType::OperatorDiv,
                                   .lhs = lang::ParseExpVal(6),
                                   .rhs = lang::ParseExpVal(3)};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<std::intptr_t>(val), 2);
}

TEST(inter, eval_op_div_div) {
  lang::Interpreter inter;
  auto pack_1 =
      std::make_unique<lang::ParseExp>(lang::ParseExp{.type = lang::ParseExpType::OperatorDiv,
                                                      .lhs = lang::ParseExpVal(6),
                                                      .rhs = lang::ParseExpVal(3)});
  const auto pack = lang::ParseExp{.type = lang::ParseExpType::OperatorDiv,
                                   .lhs = lang::ParseExpVal(6),
                                   .rhs = std::move(pack_1)};
  const auto val = inter.eval(pack);
  EXPECT_EQ(std::get<std::intptr_t>(val), 3);
}
