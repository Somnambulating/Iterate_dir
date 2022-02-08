cmake_minimum_required(VERSION 3.14)

project(Iterate_dir)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

add_executable(Iterate main.cpp)


include_directories(
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(Iterate tools)