#include <algorithm>
#include <cstdint>
#include <gtest/gtest.h>
#include <vector>

#include "../../src/inter.hpp"

// Demonstrate some basic assertions
TEST(inter, eval_list_plus_plus) {
  lang::Interpreter inter;
  const auto pack_1 = lang::OperatorPack{
      .op = lang::ParseExpOperator::Plus, .lhs = 1, .rhs = 1};
  const auto pack_2 = lang::OperatorPack{
      .op = lang::ParseExpOperator::Plus, .lhs = 2, .rhs = 2};
  const auto list =
      std::vector<lang::ParseExp>{{lang::ParseExpType::Operator, pack_1},
                                  {lang::ParseExpType::Operator, pack_2}};
  const auto val = inter.eval({lang::ParseExpType::List, list});
  EXPECT_EQ(*std::get_if<int32_t>(&val), 6);
}

TEST(inter, eval_list_str_int) {
  lang::Interpreter inter;
  const std::string str("My number is ");
  const auto list = std::vector<lang::ParseExp>{
      {lang::ParseExpType::Symbol, str}, {lang::ParseExpType::Int, 33}};
  const auto val = inter.eval({lang::ParseExpType::List, list});
  const std::string_view expect("My number is 6");
  EXPECT_TRUE(std::ranges::equal(*std::get_if<std::string>(&val), expect));
}