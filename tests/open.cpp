#include <gtest/gtest.h>
#include <gdbm.h>
#include <unistd.h>
#include <stdlib.h>

TEST(gdbm, open)
{
    GDBM_FILE dbf;
    char dbname[] = "./tmp.db";
    const int block_size = 0;
    const int mode = 0600;

    dbf = gdbm_open( dbname, block_size, GDBM_NEWDB, mode, NULL );
    EXPECT_TRUE( dbf );
    EXPECT_NO_THROW( gdbm_close( dbf ) );

    dbf = gdbm_open( dbname, block_size, GDBM_READER, mode, NULL );
    EXPECT_TRUE( dbf );
    EXPECT_NO_THROW( gdbm_close( dbf ) );

    dbf = gdbm_open( dbname, block_size, GDBM_WRITER, mode, NULL );
    EXPECT_TRUE( dbf );
    EXPECT_NO_THROW( gdbm_close( dbf ) );

    EXPECT_TRUE( unlink( dbname ) == 0 );


    dbf = gdbm_open( dbname, block_size, GDBM_READER, mode, NULL );
    EXPECT_FALSE( dbf );

    dbf = gdbm_open( dbname, block_size, GDBM_WRITER, mode, NULL );
    EXPECT_FALSE( dbf );

}


TEST(gdbm, open_block_size)
{
    GDBM_FILE dbf;
    char dbname[] = "./tmp.db";
    int block_size = 0;
    const int mode = 0600;

    srand( 1234 );

    for( int i = 1; i < 100; i++)
    {
        block_size = rand() % ( 1 << 16 );
        // printf( "%d\n", block_size );
        dbf = gdbm_open( dbname, block_size, GDBM_NEWDB, mode, NULL );
        EXPECT_TRUE( dbf );
        EXPECT_NO_THROW( gdbm_close( dbf ) );
    }
    EXPECT_TRUE( unlink( dbname ) == 0 );
}

TEST(gdbm, open_sync)
{
    GDBM_FILE dbf;
    char dbname[] = "./tmp.db";
    int block_size = 0;
    const int mode = 0600;
    
    dbf = gdbm_open( dbname, block_size, GDBM_NEWDB, mode, NULL );
    EXPECT_TRUE( dbf );
    EXPECT_NO_THROW( gdbm_sync( dbf ) );
    EXPECT_NO_THROW( gdbm_close( dbf ) );

}
