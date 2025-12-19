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
  EXPECT_EQ(std::get<intptr_t>(ret.lhs), 1);
  EXPECT_EQ(std::get<intptr_t>(ret.rhs), 1);
}

TEST(parser, parse_operator_plus_sub) {
  lang::Parser parser;
  const auto ret = parser.parse(std::format("(+ {} (+ {} {}))", 1, 1, 1));
  EXPECT_EQ(ret.type, lang::ParseExpType::OperatorPlus);
  EXPECT_EQ(std::get<intptr_t>(ret.lhs), 1);
  EXPECT_EQ(std::get<intptr_t>(ret.rhs), 1);
}
