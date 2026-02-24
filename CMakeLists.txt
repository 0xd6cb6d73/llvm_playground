cmake_minimum_required(VERSION 3.31)

cmake_policy(SET CMP0135 NEW)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(PROJECT_NAME llvm_lang)
project(${PROJECT_NAME} LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL
        https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(LLVM 21.1.8 EXACT CONFIG REQUIRED)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
link_directories(${LLVM_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} src/main.cpp src/llvm_lang.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_compile_options(${PROJECT_NAME} PRIVATE "-Wall" "-Wextra")

set(PARSER_NAME "${PROJECT_NAME}_parser")
add_library("${PARSER_NAME}.lib" STATIC)
add_library("${PARSER_NAME}::lib" ALIAS "${PARSER_NAME}.lib")
target_sources(
    "${PARSER_NAME}.lib"
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src"
            FILES src/parser.hpp
)
target_sources("${PARSER_NAME}.lib" PRIVATE src/parser.cpp)
target_compile_features("${PARSER_NAME}.lib" PUBLIC cxx_std_23)

set(INTER_NAME "${PROJECT_NAME}_inter")
add_library("${INTER_NAME}.lib" STATIC)
add_library("${INTER_NAME}::lib" ALIAS "${INTER_NAME}.lib")
target_sources(
    "${INTER_NAME}.lib"
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src"
            FILES src/inter.hpp
)
target_sources("${INTER_NAME}.lib" PRIVATE src/inter.cpp)
target_compile_features("${INTER_NAME}.lib" PUBLIC cxx_std_23)

set(COMP_NAME "${PROJECT_NAME}_comp")
add_library("${COMP_NAME}.lib" STATIC)
add_library("${COMP_NAME}::lib" ALIAS "${COMP_NAME}.lib")
target_sources(
    "${COMP_NAME}.lib"
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src"
            FILES src/compiler.hpp
)
target_sources("${COMP_NAME}.lib" PRIVATE src/compiler.cpp)
target_compile_features("${COMP_NAME}.lib" PUBLIC cxx_std_23)
target_link_libraries("${COMP_NAME}.lib" PRIVATE LLVMCore)

target_link_libraries(${PROJECT_NAME} PRIVATE LLVMCore)
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE "${INTER_NAME}.lib" "${PARSER_NAME}::lib"
)

install(TARGETS ${PROJECT_NAME} "${PARSER_NAME}.lib")
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND "${PROJECT_NAME}.exe | lli out.ll")

include("cmake/tests.cmake")
