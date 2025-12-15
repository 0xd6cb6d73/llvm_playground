#include <cstdint>
#include <gtest/gtest.h>

#include "../../src/inter.hpp"

// Demonstrate some basic assertions
TEST(inter, eval_num_0) {
  lang::Interpreter inter;
  auto num = lang::ParseExpVal(0);
  const auto ret = inter.eval({
      lang::ParseExpType::Int,
      &num,
  });
  EXPECT_EQ(std::get<int32_t>(ret), 0);
}

TEST(inter, eval_num_1) {
  lang::Interpreter inter;
  auto num = lang::ParseExpVal(1);
  const auto ret = inter.eval({
      lang::ParseExpType::Int,
      &num,
  });
  EXPECT_EQ(std::get<int32_t>(ret), 1);
}

TEST(inter, eval_num_intmax) {
  lang::Interpreter inter;
  auto num = lang::ParseExpVal(INT32_MAX);
  const auto ret = inter.eval({
      lang::ParseExpType::Int,
      &num,
  });
  EXPECT_EQ(std::get<int32_t>(ret), std::get<int32_t>(num));
}

TEST(inter, eval_num_intmin) {
  lang::Interpreter inter;
  auto num = lang::ParseExpVal(INT32_MIN);
  const auto ret = inter.eval({
      lang::ParseExpType::Int,
      &num,
  });
  EXPECT_EQ(std::get<int32_t>(ret), std::get<int32_t>(num));
}
