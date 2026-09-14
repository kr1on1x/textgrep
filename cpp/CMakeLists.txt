cmake_minimum_required(VERSION 3.20)

project(textgrep VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(textgrep
    src/main.cpp
    src/config.cpp
    src/search.cpp
    src/utils.cpp
)

target_include_directories(textgrep PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
