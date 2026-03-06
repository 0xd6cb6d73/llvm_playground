cmake_minimum_required(VERSION 3.31)

cmake_policy(SET CMP0135 NEW)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(PROJECT_NAME my_lang)
project(${PROJECT_NAME} LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/main.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(LLVM CONFIG REQUIRED)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
link_directories(${LLVM_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_compile_options(${PROJECT_NAME} PRIVATE "-Wall" "-Wextra")

add_library("${PROJECT_NAME}.parser" STATIC)
add_library("${PROJECT_NAME}::parser" ALIAS "${PROJECT_NAME}.parser")
target_sources(
    "${PROJECT_NAME}.parser"
    PRIVATE src/parser.cpp
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src"
            FILES src/parser.hpp
)
target_compile_features("${PROJECT_NAME}.parser" PUBLIC cxx_std_23)

add_library("${PROJECT_NAME}.inter" STATIC)
add_library("${PROJECT_NAME}::inter" ALIAS "${PROJECT_NAME}.inter")
target_sources(
    "${PROJECT_NAME}.inter"
    PRIVATE src/inter.cpp
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src"
            FILES src/inter.hpp
)
target_compile_features("${PROJECT_NAME}.inter" PUBLIC cxx_std_23)

add_library("${PROJECT_NAME}.comp" STATIC)
add_library("${PROJECT_NAME}::comp" ALIAS "${PROJECT_NAME}.comp")
target_sources(
    "${PROJECT_NAME}.comp"
    PRIVATE src/compiler.cpp
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src"
            FILES src/compiler.hpp
)
target_compile_features("${PROJECT_NAME}.comp" PUBLIC cxx_std_23)
target_link_libraries(
    "${PROJECT_NAME}.comp"
    PUBLIC
        LLVMCore
        LLVMexecutionengine
        LLVMMCJIT
        LLVMInterpreter
        LLVMMC
        LLVMSupport
        ${LLVM_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE LLVMCore)
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE "${PROJECT_NAME}.parser" "${PROJECT_NAME}::inter" "${PROJECT_NAME}::comp"
)

install(TARGETS ${PROJECT_NAME} "${PROJECT_NAME}.parser" "${PROJECT_NAME}.inter" "${PROJECT_NAME}.comp")
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND "${PROJECT_NAME}.exe | lli out.ll")

include("cmake/tests.cmake")
