
add_executable(tests
delete.cpp
insert.cpp
main.cpp
open.cpp
scan.cpp
)

target_compile_options( tests PRIVATE -Wall -pedantic -pthread -g -O0 -fprofile-arcs -ftest-coverage -std=c++11 -DNDEBUG )

target_include_directories( tests PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} )

target_link_libraries( tests -fprofile-arcs gtest gtest_main pthread gdbm )

add_test(NAME gdbm_test COMMAND tests)

