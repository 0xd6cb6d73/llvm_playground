#include "main.hpp"

int main() {
  LangLLVM lang;
  lang.exec(std::string(R"(ret 1)"));
  return 0;
}