#include "llvm_lang.hpp"

int main() {
  LangLLVM lang;
  lang.exec(std::string(R"((print "Hello, world!"))"));
  return 0;
}