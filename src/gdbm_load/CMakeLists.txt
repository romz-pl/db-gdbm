add_executable(gdbm_load
gdbm_load.c)

target_include_directories(gdbm_load PRIVATE ../libgdbm)
target_include_directories(gdbm_load PRIVATE ../libgdbmapp)

target_compile_options( gdbm_load PRIVATE -Wall -pedantic -pthread -g -O0 -fprofile-arcs -ftest-coverage -std=gnu11 -DNDEBUG -DNOLOGGING )

target_link_libraries( gdbm_load -fprofile-arcs pthread gdbm gdbmapp )

