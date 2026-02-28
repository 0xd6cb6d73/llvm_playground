#include <gtest/gtest.h>

#include "parser.hpp"

#include <format>

TEST(parser, parse_num_0) {
  lang::Parser parser;
  const auto ret = parser.parse(std::format("({})", 0));
  EXPECT_EQ(std::get<std::intptr_t>(ret.lhs), 0);
  EXPECT_TRUE(ret.type == lang::ParseExpType::Int);
}

TEST(parser, parse_num_1) {
  lang::Parser parser;
  const auto ret = parser.parse(std::format("({})", 1));
  EXPECT_EQ(std::get<std::intptr_t>(ret.lhs), 1);
  EXPECT_TRUE(ret.type == lang::ParseExpType::Int);
}

TEST(parser, parse_num_intmax) {
  lang::Parser parser;
  const auto ret = parser.parse(std::format("({})", INT_MAX));
  EXPECT_EQ(std::get<std::intptr_t>(ret.lhs), INT_MAX);
  EXPECT_TRUE(ret.type == lang::ParseExpType::Int);
}

TEST(parser, parse_num_intmin) {
  lang::Parser parser;
  const auto ret = parser.parse(std::format("({})", INT_MIN));
  EXPECT_EQ(std::get<std::intptr_t>(ret.lhs), INT_MIN);
  EXPECT_TRUE(ret.type == lang::ParseExpType::Int);
}
