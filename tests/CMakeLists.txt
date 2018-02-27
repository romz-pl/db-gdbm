cmake_minimum_required(VERSION 3.0)

project(romz-gdbm-tests)

add_executable(all.x
delete.cpp
insert.cpp
main.cpp
open.cpp
scan.cpp
)

target_include_directories(all.x PUBLIC ${PROJECT_SOURCE_DIR}/../3rdparty/googletest/include)
find_library(GOOGLETEST_LIB gtest.a HINT ${PROJECT_SOURCE_DIR}/../3rdparty/googletest)

target_include_directories(all.x PUBLIC ${PROJECT_SOURCE_DIR}/../src/libgdbm)
find_library(GDBM_LIB libgdbm.a HINT ${PROJECT_SOURCE_DIR}/../build/src/libgdbm)


target_link_libraries(all.x ${GOOGLETEST_LIB} pthread ${GDBM_LIB})
