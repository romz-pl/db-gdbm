add_executable(gdbm_dump
gdbm_dump.c)

target_include_directories(gdbm_dump PRIVATE ../libgdbm)
target_include_directories(gdbm_dump PRIVATE ../libgdbmapp)

target_link_libraries(gdbm_dump gdbmapp)
target_link_libraries(gdbm_dump gdbm)



