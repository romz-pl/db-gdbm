add_executable(gdbmtools
datconv.c
gdbmtool.c
gram.c
input-std.c
lex.c
util.c
var.c
)

target_include_directories(gdbmtools PRIVATE ../libgdbm)
target_include_directories(gdbmtools PRIVATE ../libgdbmapp)

target_compile_options( gdbmtools PRIVATE -Wall -pedantic -pthread -g -O0 -fprofile-arcs -ftest-coverage -std=gnu11 -DNDEBUG -DNOLOGGING )

target_link_libraries( gdbmtools -fprofile-arcs pthread gdbm gdbmapp )

