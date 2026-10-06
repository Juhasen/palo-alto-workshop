cmake_minimum_required(VERSION 3.16)
project(demo07_ticket_to_pr CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
    add_compile_options(/W4 /WX /EHsc)
else()
    add_compile_options(-Wall -Wextra -Wconversion -Werror)
endif()

add_library(port_ranges src/port_ranges.cpp)
target_include_directories(port_ranges PUBLIC include)

add_executable(port_ranges_test tests/port_ranges_test.cpp)
target_link_libraries(port_ranges_test PRIVATE port_ranges)

enable_testing()
add_test(NAME port_ranges_test COMMAND port_ranges_test)
