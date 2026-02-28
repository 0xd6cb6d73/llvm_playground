#include <gtest/gtest.h>

#include "../../src/inter.hpp"

// Demonstrate some basic assertions
TEST(inter, eval_num_0) {
  lang::Interpreter inter;
  auto num = lang::ParseExpVal(0);
  const auto ret = inter.eval({
      lang::ParseExpType::Int,
      std::move(num),
  });
  EXPECT_EQ(std::get<std::intptr_t>(ret), 0);
}

TEST(inter, eval_num_1) {
  lang::Interpreter inter;
  auto num = lang::ParseExpVal(1);
  const auto ret = inter.eval({
      lang::ParseExpType::Int,
      std::move(num),
  });
  EXPECT_EQ(std::get<std::intptr_t>(ret), 1);
}

TEST(inter, eval_num_intmax) {
  lang::Interpreter inter;
  auto num = lang::ParseExpVal(INT32_MAX);
  const auto ret = inter.eval({
      lang::ParseExpType::Int,
      std::move(num),
  });
  EXPECT_EQ(std::get<std::intptr_t>(ret), static_cast<std::intptr_t>(INT32_MAX));
}

TEST(inter, eval_num_intmin) {
  lang::Interpreter inter;
  auto num = lang::ParseExpVal(INT32_MIN);
  const auto ret = inter.eval({
      lang::ParseExpType::Int,
      std::move(num),
  });
  EXPECT_EQ(std::get<std::intptr_t>(ret), static_cast<std::intptr_t>(INT32_MIN));
}

TEST(inter, eval_num_int64max) {
  lang::Interpreter inter;
  auto num = lang::ParseExpVal(INT64_MAX);
  const auto ret = inter.eval({
      lang::ParseExpType::Int,
      std::move(num),
  });
  EXPECT_EQ(std::get<std::intptr_t>(ret), static_cast<std::intptr_t>(INT64_MAX));
}

TEST(inter, eval_num_int64min) {
  lang::Interpreter inter;
  auto num = lang::ParseExpVal(INT64_MIN);
  const auto ret = inter.eval({
      lang::ParseExpType::Int,
      std::move(num),
  });
  EXPECT_EQ(std::get<std::intptr_t>(ret), static_cast<std::intptr_t>(INT64_MIN));
}
