


add_library(gdbm STATIC
base64.c
bucket.c
# debug.c
falloc.c
findkey.c
fullio.c
gdbmclose.c
gdbmcount.c
gdbmdelete.c
gdbmdump.c
gdbmerrno.c
gdbmexists.c
gdbmexp.c
gdbmfdesc.c
gdbmfetch.c
gdbmimp.c
gdbmload.c
gdbmopen.c
gdbmreorg.c
gdbmseq.c
gdbmsetopt.c
gdbmstore.c
gdbmsync.c
hash.c
lock.c
mmap.c
recover.c
update.c
version.c
)

target_compile_options( gdbm PRIVATE -Wall -Wextra )