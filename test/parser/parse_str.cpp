#include <gtest/gtest.h>

import std;

#include "../../src/parser.hpp"

TEST(parser, parse_str_0) {
  lang::Parser parser;
  const auto ret = parser.parse(std::string(R"((""))"));
  EXPECT_TRUE(
      std::ranges::equal(std::get<std::string>(ret.lhs), std::string()));
  EXPECT_TRUE(ret.type == lang::ParseExpType::Symbol);
}

TEST(parser, parse_str_15) {
  lang::Parser parser;
  const auto ret = parser.parse(std::string(R"(("01234567898765"))"));
  EXPECT_TRUE(std::ranges::equal(std::get<std::string>(ret.lhs),
                                 std::string("01234567898765")));
  EXPECT_TRUE(ret.type == lang::ParseExpType::Symbol);
}

TEST(parser, parse_str_32) {
  lang::Parser parser;
  const auto ret =
      parser.parse(std::string(R"(("0123456789876543210123456789876"))"));
  EXPECT_TRUE(
      std::ranges::equal(std::get<std::string>(ret.lhs),
                         std::string("0123456789876543210123456789876")));
  EXPECT_TRUE(ret.type == lang::ParseExpType::Symbol);
}