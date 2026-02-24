namespace lang {
template <class... Ts> struct overloaded : Ts... {
  using Ts::operator()...;
};
} // namespace lang