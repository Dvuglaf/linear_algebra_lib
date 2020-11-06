# CMakeList.txt: проект CMake для linear; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
project(linear)
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
if (MSVC)
    # remove default warning level from CMAKE_CXX_FLAGS_INIT
    string (REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT}")
endif()
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options(/W4 /D_CRT_SECURE_NO_WARNINGS)
endif()


# Добавьте источник в исполняемый файл этого проекта.
add_executable (linear "linear.cpp" "linear.h" "matrix.h" "matrix.cpp" "var.h" "complex.h" "complex.cpp" "vector.h" "vector.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
