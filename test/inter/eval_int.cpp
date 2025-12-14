#include <cstdint>
#include <gtest/gtest.h>

#include "../../src/inter.hpp"

// Demonstrate some basic assertions
TEST(inter, eval_num_0) {
  lang::Interpreter inter;
  const auto val = inter.eval({lang::ParseExpType::Int, 0});
  EXPECT_EQ(*std::get_if<int32_t>(&val), 0);
}

TEST(inter, eval_num_1) {
  lang::Interpreter inter;
  const auto val = inter.eval({lang::ParseExpType::Int, 1});
  EXPECT_EQ(*std::get_if<int32_t>(&val), 1);
}

TEST(inter, eval_num_intmax) {
  lang::Interpreter inter;
  const auto num = INT32_MAX;
  const auto val = inter.eval({lang::ParseExpType::Int, num});
  EXPECT_EQ(*std::get_if<int32_t>(&val), num);
}

TEST(inter, eval_num_intmin) {
  lang::Interpreter inter;
  const auto num = INT32_MIN;
  const auto val = inter.eval({lang::ParseExpType::Int, num});
  EXPECT_EQ(*std::get_if<int32_t>(&val), num);
}
