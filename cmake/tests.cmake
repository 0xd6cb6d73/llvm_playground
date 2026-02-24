enable_testing()

add_executable(
    inter_test
    "test/inter/eval_int.cpp"
    "test/inter/eval_str.cpp"
    "test/inter/eval_operators.cpp"
)
target_link_libraries(inter_test GTest::gtest_main "${INTER_NAME}::lib")
target_compile_features(inter_test PRIVATE cxx_std_23)

add_executable(
    parser_test
    "test/parser/parse_int.cpp"
    "test/parser/parse_str.cpp"
    "test/parser/parse_operators.cpp"
    "test/parser/parse_func.cpp"
)
target_link_libraries(parser_test GTest::gtest_main "${PARSER_NAME}::lib")
target_compile_features(parser_test PRIVATE cxx_std_23)

add_executable(
    compiler_test
    "test/comp/comp_operators.cpp"
)
target_link_libraries(compiler_test GTest::gtest_main "${COMP_NAME}::lib" "${PARSER_NAME}::lib")
target_compile_features(compiler_test PRIVATE cxx_std_23)

include(GoogleTest)
gtest_discover_tests(inter_test)
gtest_discover_tests(parser_test)
gtest_discover_tests(compiler_test)
