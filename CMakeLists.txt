cmake_minimum_required(VERSION 3.14)
project(LabSequence)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Основная программа
add_executable(main main.cpp demo.cpp)
# Тесты
add_executable(tests tests.cpp)
target_link_libraries(tests GTest::gtest_main)

enable_testing()
add_test(NAME AllTests COMMAND tests)