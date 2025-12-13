cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME llvm_lang)
project(${PROJECT_NAME} LANGUAGES CXX)
add_executable(${PROJECT_NAME} main.cpp)

set(LLVM_CMAKE_DIR "D:/tooling/llvm-mingw-20251212-ucrt-x86_64/lib/cmake/llvm")
execute_process(COMMAND ${CMAKE_FIND_ROOT_PATH}/../bin/llvm-config --cxxflags --ldflags --system-libs --libs core OUTPUT_VARIABLE LLVM_CONFIG)
target_compile_options(${PROJECT_NAME} PRIVATE ${LLVM_CONFIG})
target_link_options(${PROJECT_NAME} PRIVATE ${LLVM_CONFIG})
target_link_libraries(${PROJECT_NAME} PRIVATE libLLVM-21.dll.a)