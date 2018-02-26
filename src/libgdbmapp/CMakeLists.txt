add_library(gdbmapp STATIC
err.c
mem.c
parseopt.c
progname.c
)

target_include_directories(gdbmapp PRIVATE ../libgdbm)

