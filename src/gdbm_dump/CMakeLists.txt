add_executable(gdbm_dump
gdbm_dump.c)

target_include_directories(gdbm_dump PRIVATE ../libgdbm)
target_include_directories(gdbm_dump PRIVATE ../libgdbmapp)


target_compile_options( gdbm_dump PRIVATE -Wall -pedantic -pthread -g -O0 -fprofile-arcs -ftest-coverage -std=gnu11 -DNDEBUG -DNOLOGGING )

target_link_libraries( gdbm_dump -fprofile-arcs pthread gdbm gdbmapp )


