#include <gtest/gtest.h>

import std;

#include "../../src/inter.hpp"

// Demonstrate some basic assertions
TEST(inter, eval_str_0) {
  lang::Interpreter inter;
  auto empty = lang::ParseExpVal(std::string());
  const auto ret = inter.eval({
      lang::ParseExpType::Symbol,
      std::move(empty),
  });
  EXPECT_TRUE(std::ranges::equal(std::get<std::string>(ret),
                                 std::get<std::string>(empty)));
}

TEST(inter, eval_str_15) {
  lang::Interpreter inter;
  auto str = lang::ParseExpVal(std::string("01234567898765"));
  const auto ret = inter.eval({
      lang::ParseExpType::Symbol,
      std::move(str),
  });
  EXPECT_TRUE(std::ranges::equal(std::get<std::string>(ret),
                                 std::string("01234567898765")));
}

TEST(inter, eval_str_32) {
  lang::Interpreter inter;
  auto str = lang::ParseExpVal(std::string("0123456789876543210123456789876"));
  const auto ret = inter.eval({
      lang::ParseExpType::Symbol,
      std::move(str),
  });
  EXPECT_TRUE(
      std::ranges::equal(std::get<std::string>(ret),
                         std::string("0123456789876543210123456789876")));
}
