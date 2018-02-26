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

target_link_libraries(gdbmtools gdbmapp)
target_link_libraries(gdbmtools gdbm)



