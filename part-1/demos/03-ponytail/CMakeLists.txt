cmake_minimum_required(VERSION 3.16)
project(demo03_ponytail CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
    add_compile_options(/W4 /WX /EHsc)
else()
    add_compile_options(-Wall -Wextra -Wconversion -Werror)
endif()

add_library(range_check src/range_check.cpp)
target_include_directories(range_check PUBLIC include)

add_executable(range_check_test tests/range_check_test.cpp)
target_link_libraries(range_check_test PRIVATE range_check)

enable_testing()
add_test(NAME range_check_test COMMAND range_check_test)
