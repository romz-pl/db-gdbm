cmake_minimum_required(VERSION 3.0)

project(romz-gdbm-ex01)

add_executable(ex01.x
main.cpp
)


target_include_directories(ex01.x PUBLIC ${PROJECT_SOURCE_DIR}/../src/libgdbm)


target_link_libraries( ex01.x -fprofile-arcs pthread gdbm )
