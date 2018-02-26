add_executable(gdbm_load
gdbm_load.c)

target_include_directories(gdbm_load PRIVATE ../libgdbm)
target_include_directories(gdbm_load PRIVATE ../libgdbmapp)

target_link_libraries(gdbm_load gdbmapp)
target_link_libraries(gdbm_load gdbm)



