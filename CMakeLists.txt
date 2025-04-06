cmake_minimum_required(VERSION 3.31)

set(THIS ExpressionParser)

project(${THIS} CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

add_library(${THIS} STATIC ${LIB_DIR}/Parser.cpp ${LIB_DIR}/Tokenizer.cpp ${LIB_DIR}/Expression.cpp)
target_include_directories(${THIS} PUBLIC ${LIB_DIR})

add_executable(Driver "src/driver.cpp")
target_link_libraries(Driver PUBLIC ${THIS})

add_executable(TestParser tests/TestParser.cpp)
add_executable(TestTokenizer tests/TestTokenizer.cpp)
target_link_libraries(TestParser PRIVATE ${THIS} GTest::gtest_main ${THIS})
target_link_libraries(TestTokenizer PRIVATE ${THIS} GTest::gtest_main ${THIS})

include(GoogleTest)
gtest_discover_tests(TestParser)
gtest_discover_tests(TestTokenizer)

