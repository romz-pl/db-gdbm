#include <gtest/gtest.h>
#include <gdbm.h>
#include <unistd.h>

TEST(gdbm, open)
{
    GDBM_FILE dbf;
    char dbname[] = "./tmp.db";

    dbf = gdbm_open( dbname, 0, GDBM_NEWDB, 0600, NULL );
    EXPECT_TRUE( dbf );
    EXPECT_NO_THROW( gdbm_close( dbf ) );

    dbf = gdbm_open( dbname, 0, GDBM_READER, 0600, NULL );
    EXPECT_TRUE( dbf );
    EXPECT_NO_THROW( gdbm_close( dbf ) );

    dbf = gdbm_open( dbname, 0, GDBM_WRITER, 0600, NULL );
    EXPECT_TRUE( dbf );
    EXPECT_NO_THROW( gdbm_close( dbf ) );

    EXPECT_TRUE( unlink( dbname ) == 0 );


    dbf = gdbm_open( dbname, 0, GDBM_READER, 0600, NULL );
    EXPECT_FALSE( dbf );

    dbf = gdbm_open( dbname, 0, GDBM_WRITER, 0600, NULL );
    EXPECT_FALSE( dbf );

}

