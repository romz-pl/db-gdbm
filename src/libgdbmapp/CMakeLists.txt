add_library(gdbmapp STATIC
err.c
mem.c
parseopt.c
progname.c
)

target_include_directories(gdbmapp PRIVATE ../libgdbm)

target_compile_options( gdbmapp PRIVATE -Wall -pedantic -pthread -g -O0 -fprofile-arcs -ftest-coverage -std=gnu11 -DNDEBUG -DNOLOGGING )

