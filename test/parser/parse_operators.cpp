#include <cstdint>
#include <format>
#include <gtest/gtest.h>

#include "../../src/parser.hpp"

TEST(parser, parse_operator_plus) {
  lang::Parser parser;
  const auto ret = parser.parse(std::format("(+ {} {})", 1, 1));
  EXPECT_EQ(ret.type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(std::get<intptr_t>(ret.lhs), 1);
  EXPECT_EQ(std::get<intptr_t>(ret.rhs), 1);
}

TEST(parser, parse_operator_sub_plus) {
  lang::Parser parser;
  const auto ret = parser.parse(std::format("(+ (+ {} {}) {})", 1, 1, 1));
  EXPECT_EQ(ret.type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(std::get<std::unique_ptr<lang::ParseExp>>(ret.lhs)->type,
            lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(std::get<intptr_t>(
                std::get<std::unique_ptr<lang::ParseExp>>(ret.lhs)->lhs),
            1);
  EXPECT_EQ(std::get<intptr_t>(
                std::get<std::unique_ptr<lang::ParseExp>>(ret.lhs)->rhs),
            1);
  EXPECT_EQ(std::get<intptr_t>(ret.rhs), 1);
}

TEST(parser, parse_operator_plus_sub) {
  lang::Parser parser;
  const auto ret = parser.parse(std::format("(+ {} (+ {} {}))", 1, 1, 1));
  EXPECT_EQ(ret.type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(std::get<std::unique_ptr<lang::ParseExp>>(ret.rhs)->type,
            lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(std::get<intptr_t>(
                std::get<std::unique_ptr<lang::ParseExp>>(ret.rhs)->lhs),
            1);
  EXPECT_EQ(std::get<intptr_t>(
                std::get<std::unique_ptr<lang::ParseExp>>(ret.rhs)->rhs),
            1);
  EXPECT_EQ(std::get<intptr_t>(ret.lhs), 1);
}

TEST(parser, parse_operator_recurse_plus) {
  lang::Parser parser;
  auto ret = parser.parse(
      std::format("(+ (+ {} (+ (+ {} (+ {} {})) {})) {})", 1, 1, 1, 1, 1, 1));

  const auto outer_type = ret.type;
  std::unique_ptr<lang::ParseExp> outer_lhs =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(ret.lhs));
  const auto outer_rhs = std::get<intptr_t>(ret.rhs);

  const auto outer_lhs_type = outer_lhs->type;
  const auto outer_lhs_lhs = std::get<intptr_t>(outer_lhs->lhs);
  const std::unique_ptr<lang::ParseExp> outer_lhs_rhs =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(outer_lhs->rhs));

  const auto outer_lhs_rhs_type = outer_lhs_rhs->type;
  const std::unique_ptr<lang::ParseExp> outer_lhs_rhs_lhs =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(outer_lhs_rhs->lhs));
  const auto outer_lhs_rhs_rhs = std::get<intptr_t>(outer_lhs_rhs->rhs);

  const auto outer_lhs_rhs_lhs_type = outer_lhs_rhs_lhs->type;
  const auto outer_lhs_rhs_lhs_lhs = std::get<intptr_t>(outer_lhs_rhs_lhs->lhs);
  const std::unique_ptr<lang::ParseExp> outer_lhs_rhs_lhs_rhs = std::move(
      std::get<std::unique_ptr<lang::ParseExp>>(outer_lhs_rhs_lhs->rhs));

  const auto outer_lhs_rhs_lhs_rhs_type = outer_lhs_rhs_lhs_rhs->type;
  const auto outer_lhs_rhs_lhs_rhs_lhs =
      std::get<intptr_t>(outer_lhs_rhs_lhs_rhs->lhs);
  const auto outer_lhs_rhs_lhs_rhs_rhs =
      std::get<intptr_t>(outer_lhs_rhs_lhs_rhs->rhs);

  EXPECT_EQ(outer_type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(outer_lhs_type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(outer_lhs_rhs_type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(outer_lhs_rhs_lhs_type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(outer_lhs_rhs_lhs_rhs_type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(outer_rhs, 1);
  EXPECT_EQ(outer_lhs_rhs_rhs, 1);
  EXPECT_EQ(outer_lhs_rhs_lhs_lhs, 1);
  EXPECT_EQ(outer_lhs_rhs_lhs_rhs_lhs, 1);
  EXPECT_EQ(outer_lhs_rhs_lhs_rhs_rhs, 1);
}
