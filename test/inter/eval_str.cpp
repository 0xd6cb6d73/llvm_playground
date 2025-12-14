#include <algorithm>
#include <gtest/gtest.h>

#include "../../src/inter.hpp"

// Demonstrate some basic assertions
TEST(inter, eval_str_0) {
  lang::Interpreter inter;
  const auto empty = std::string();
  const auto val = inter.eval(empty);
  EXPECT_TRUE(std::ranges::equal(*std::get_if<std::string>(&val), empty));
}

TEST(inter, eval_str_15) {
  lang::Interpreter inter;
  const auto str = std::string("01234567898765");
  const auto val = inter.eval(str);
  EXPECT_TRUE(std::ranges::equal(*std::get_if<std::string>(&val), str));
}

TEST(inter, eval_str_32) {
  lang::Interpreter inter;
  const auto str = std::string("0123456789876543210123456789876");
  const auto val = inter.eval(str);
  EXPECT_TRUE(std::ranges::equal(*std::get_if<std::string>(&val), str));
}
