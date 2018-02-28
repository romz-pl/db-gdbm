#include <gdbm.h>
#include <unistd.h>
#include <cstdlib>
#include <cassert>

int main()
{
    GDBM_FILE dbf;
    char dbname[] = "./tmp.db";
    const int block_size = 0;
    const int mode = 0600;

    dbf = gdbm_open( dbname, block_size, GDBM_NEWDB, mode, NULL );
    assert( dbf );
    gdbm_close( dbf );

    return 0;
}

