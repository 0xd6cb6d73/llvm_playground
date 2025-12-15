enable_testing()

add_executable(
    inter_test
    "test/inter/eval_int.cpp"
    "test/inter/eval_str.cpp"
    "test/inter/eval_operators.cpp"
)
target_link_libraries(inter_test GTest::gtest_main ${INTER_NAME})
target_compile_features(inter_test PRIVATE cxx_std_23)

include(GoogleTest)
gtest_discover_tests(inter_test)
