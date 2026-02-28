#include <gtest/gtest.h>

import std;

#include "../../src/parser.hpp"

TEST(parser, parse_operator_plus) {
  lang::Parser parser;
  const auto ret = parser.parse(std::format("(+ {} {})", 1, 2));
  EXPECT_EQ(ret.type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(std::get<std::intptr_t>(ret.lhs), 1);
  EXPECT_EQ(std::get<std::intptr_t>(ret.rhs), 2);
}

TEST(parser, parse_operator_sub_plus) {
  lang::Parser parser;
  const auto ret = parser.parse(std::format("(+ (+ {} {}) {})", 1, 2, 3));
  EXPECT_EQ(ret.type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(std::get<std::unique_ptr<lang::ParseExp>>(ret.lhs)->type,
            lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(std::get<std::intptr_t>(std::get<std::unique_ptr<lang::ParseExp>>(ret.lhs)->lhs), 1);
  EXPECT_EQ(std::get<std::intptr_t>(std::get<std::unique_ptr<lang::ParseExp>>(ret.lhs)->rhs), 2);
  EXPECT_EQ(std::get<std::intptr_t>(ret.rhs), 3);
}

TEST(parser, parse_operator_plus_sub) {
  lang::Parser parser;
  const auto ret = parser.parse(std::format("(+ {} (+ {} {}))", 1, 2, 3));
  EXPECT_EQ(ret.type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(std::get<std::unique_ptr<lang::ParseExp>>(ret.rhs)->type,
            lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(std::get<std::intptr_t>(std::get<std::unique_ptr<lang::ParseExp>>(ret.rhs)->lhs), 2);
  EXPECT_EQ(std::get<std::intptr_t>(std::get<std::unique_ptr<lang::ParseExp>>(ret.rhs)->rhs), 3);
  EXPECT_EQ(std::get<std::intptr_t>(ret.lhs), 1);
}

TEST(parser, parse_operator_recurse_plus) {
  lang::Parser parser;
  //(+ (+ {lhs_lhs} (+ (+ {lhs_rhs_lhs} (+ {lhs_rhs_lhs_lhs} {lhs_rhs_lhs_rhs}))
  //{lhs_rhs_rhs})) {rhs})
  auto ret = parser.parse(std::format("(+ (+ {} (+ (+ {} (+ {} {})) {})) {})", 1, 2, 3, 4, 5, 6));

  const auto outer_type = ret.type;
  const std::unique_ptr<lang::ParseExp> outer_lhs =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(ret.lhs));
  const auto outer_rhs = std::get<std::intptr_t>(ret.rhs);

  const auto outer_lhs_type = outer_lhs->type;
  const auto outer_lhs_lhs = std::get<std::intptr_t>(outer_lhs->lhs);
  const std::unique_ptr<lang::ParseExp> outer_lhs_rhs =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(outer_lhs->rhs));

  const auto outer_lhs_rhs_type = outer_lhs_rhs->type;
  const std::unique_ptr<lang::ParseExp> outer_lhs_rhs_lhs =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(outer_lhs_rhs->lhs));
  const auto outer_lhs_rhs_rhs = std::get<std::intptr_t>(outer_lhs_rhs->rhs);

  const auto outer_lhs_rhs_lhs_type = outer_lhs_rhs_lhs->type;
  const auto outer_lhs_rhs_lhs_lhs = std::get<std::intptr_t>(outer_lhs_rhs_lhs->lhs);
  const std::unique_ptr<lang::ParseExp> outer_lhs_rhs_lhs_rhs =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(outer_lhs_rhs_lhs->rhs));

  const auto outer_lhs_rhs_lhs_rhs_type = outer_lhs_rhs_lhs_rhs->type;
  const auto outer_lhs_rhs_lhs_rhs_lhs = std::get<std::intptr_t>(outer_lhs_rhs_lhs_rhs->lhs);
  const auto outer_lhs_rhs_lhs_rhs_rhs = std::get<std::intptr_t>(outer_lhs_rhs_lhs_rhs->rhs);

  EXPECT_EQ(outer_type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(outer_lhs_type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(outer_lhs_rhs_type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(outer_lhs_rhs_lhs_type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(outer_lhs_rhs_lhs_rhs_type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(outer_rhs, 6);
  EXPECT_EQ(outer_lhs_lhs, 1);
  EXPECT_EQ(outer_lhs_rhs_rhs, 5);
  EXPECT_EQ(outer_lhs_rhs_lhs_lhs, 2);
  EXPECT_EQ(outer_lhs_rhs_lhs_rhs_lhs, 3);
  EXPECT_EQ(outer_lhs_rhs_lhs_rhs_rhs, 4);
}

TEST(parser, parse_operator_recurse_plus_minus) {
  lang::Parser parser;
  //(+ (+ {lhs_lhs} (+ (+ {lhs_rhs_lhs} (+ {lhs_rhs_lhs_lhs} {lhs_rhs_lhs_rhs}))
  //{lhs_rhs_rhs})) {rhs})
  auto ret = parser.parse(std::format("(+ (- {} (+ (- {} (+ {} {})) {})) {})", 1, 2, 3, 4, 5, 6));

  const auto outer_type = ret.type;
  const std::unique_ptr<lang::ParseExp> outer_lhs =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(ret.lhs));
  const auto outer_rhs = std::get<std::intptr_t>(ret.rhs);

  const auto outer_lhs_type = outer_lhs->type;
  const auto outer_lhs_lhs = std::get<std::intptr_t>(outer_lhs->lhs);
  const std::unique_ptr<lang::ParseExp> outer_lhs_rhs =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(outer_lhs->rhs));

  const auto outer_lhs_rhs_type = outer_lhs_rhs->type;
  const std::unique_ptr<lang::ParseExp> outer_lhs_rhs_lhs =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(outer_lhs_rhs->lhs));
  const auto outer_lhs_rhs_rhs = std::get<std::intptr_t>(outer_lhs_rhs->rhs);

  const auto outer_lhs_rhs_lhs_type = outer_lhs_rhs_lhs->type;
  const auto outer_lhs_rhs_lhs_lhs = std::get<std::intptr_t>(outer_lhs_rhs_lhs->lhs);
  const std::unique_ptr<lang::ParseExp> outer_lhs_rhs_lhs_rhs =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(outer_lhs_rhs_lhs->rhs));

  const auto outer_lhs_rhs_lhs_rhs_type = outer_lhs_rhs_lhs_rhs->type;
  const auto outer_lhs_rhs_lhs_rhs_lhs = std::get<std::intptr_t>(outer_lhs_rhs_lhs_rhs->lhs);
  const auto outer_lhs_rhs_lhs_rhs_rhs = std::get<std::intptr_t>(outer_lhs_rhs_lhs_rhs->rhs);

  EXPECT_EQ(outer_type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(outer_lhs_type, lang::ParseExpType::OperatorMinus);
  EXPECT_EQ(outer_lhs_rhs_type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(outer_lhs_rhs_lhs_type, lang::ParseExpType::OperatorMinus);
  EXPECT_EQ(outer_lhs_rhs_lhs_rhs_type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(outer_rhs, 6);
  EXPECT_EQ(outer_lhs_lhs, 1);
  EXPECT_EQ(outer_lhs_rhs_rhs, 5);
  EXPECT_EQ(outer_lhs_rhs_lhs_lhs, 2);
  EXPECT_EQ(outer_lhs_rhs_lhs_rhs_lhs, 3);
  EXPECT_EQ(outer_lhs_rhs_lhs_rhs_rhs, 4);
}

TEST(parser, parse_operator_recurse_mul_div) {
  lang::Parser parser;
  //(+ (+ {lhs_lhs} (+ (+ {lhs_rhs_lhs} (+ {lhs_rhs_lhs_lhs} {lhs_rhs_lhs_rhs}))
  //{lhs_rhs_rhs})) {rhs})
  auto ret = parser.parse(std::format("(* (/ {} (* (/ {} (* {} {})) {})) {})", 1, 2, 3, 4, 5, 6));

  const auto outer_type = ret.type;
  const std::unique_ptr<lang::ParseExp> outer_lhs =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(ret.lhs));
  const auto outer_rhs = std::get<std::intptr_t>(ret.rhs);

  const auto outer_lhs_type = outer_lhs->type;
  const auto outer_lhs_lhs = std::get<std::intptr_t>(outer_lhs->lhs);
  const std::unique_ptr<lang::ParseExp> outer_lhs_rhs =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(outer_lhs->rhs));

  const auto outer_lhs_rhs_type = outer_lhs_rhs->type;
  const std::unique_ptr<lang::ParseExp> outer_lhs_rhs_lhs =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(outer_lhs_rhs->lhs));
  const auto outer_lhs_rhs_rhs = std::get<std::intptr_t>(outer_lhs_rhs->rhs);

  const auto outer_lhs_rhs_lhs_type = outer_lhs_rhs_lhs->type;
  const auto outer_lhs_rhs_lhs_lhs = std::get<std::intptr_t>(outer_lhs_rhs_lhs->lhs);
  const std::unique_ptr<lang::ParseExp> outer_lhs_rhs_lhs_rhs =
      std::move(std::get<std::unique_ptr<lang::ParseExp>>(outer_lhs_rhs_lhs->rhs));

  const auto outer_lhs_rhs_lhs_rhs_type = outer_lhs_rhs_lhs_rhs->type;
  const auto outer_lhs_rhs_lhs_rhs_lhs = std::get<std::intptr_t>(outer_lhs_rhs_lhs_rhs->lhs);
  const auto outer_lhs_rhs_lhs_rhs_rhs = std::get<std::intptr_t>(outer_lhs_rhs_lhs_rhs->rhs);

  EXPECT_EQ(outer_type, lang::ParseExpType::OperatorMul);
  EXPECT_EQ(outer_lhs_type, lang::ParseExpType::OperatorDiv);
  EXPECT_EQ(outer_lhs_rhs_type, lang::ParseExpType::OperatorMul);
  EXPECT_EQ(outer_lhs_rhs_lhs_type, lang::ParseExpType::OperatorDiv);
  EXPECT_EQ(outer_lhs_rhs_lhs_rhs_type, lang::ParseExpType::OperatorMul);
  EXPECT_EQ(outer_rhs, 6);
  EXPECT_EQ(outer_lhs_lhs, 1);
  EXPECT_EQ(outer_lhs_rhs_rhs, 5);
  EXPECT_EQ(outer_lhs_rhs_lhs_lhs, 2);
  EXPECT_EQ(outer_lhs_rhs_lhs_rhs_lhs, 3);
  EXPECT_EQ(outer_lhs_rhs_lhs_rhs_rhs, 4);
}