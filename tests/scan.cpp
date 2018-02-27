#include <gtest/gtest.h>
#include <gdbm.h>
#include <unistd.h>
#include <stdlib.h>
#include <map>

typedef std::map< int, int > Data;

void Insert( GDBM_FILE dbf, Data& data )
{
    const int flag = GDBM_REPLACE;
    gdbm_count_t loopSize = 20000;
    datum key, content;
    int a, b;

    srand( 1234 );
    for( gdbm_count_t i = 0; i < loopSize; i++ )
    {
        a = rand();
        key.dptr = (char*)&a;
        key.dsize = sizeof( a );

        b = rand();
        content.dptr = (char*)&b;
        content.dsize = sizeof( b );

        EXPECT_TRUE( gdbm_store( dbf, key, content, flag ) == 0 );

        data[ a ] = b;
    }

    gdbm_count_t count;
    EXPECT_TRUE( gdbm_count( dbf, &count ) == 0 );
    EXPECT_EQ( count, (gdbm_count_t)data.size() );

}

void Scan( GDBM_FILE dbf, Data& data )
{
    int a;
    datum nextkey;
    datum key = gdbm_firstkey( dbf );
    while( key.dptr )
    {
        
        a = *( (int*)key.dptr );
        EXPECT_TRUE( data.find( a ) != data.end() );
        EXPECT_TRUE( data.erase( a ) == 1 );

        /* Obtain the next key */
        nextkey = gdbm_nextkey( dbf, key );
        free( key.dptr );

        /* Use nextkey in the next iteration. */
        key = nextkey;
    }

    EXPECT_TRUE( data.empty( ) ); 
}


TEST(gdbm, scan)
{
    GDBM_FILE dbf;
    char dbname[] = "./tmp.db";
    const int block_size = 0;
    const int mode = 0600;
    Data data;

    dbf = gdbm_open( dbname, block_size, GDBM_NEWDB, mode, NULL );
    EXPECT_TRUE( dbf );

    Insert( dbf, data );
    Scan( dbf, data );


    EXPECT_NO_THROW( gdbm_close( dbf ) );

    EXPECT_TRUE( unlink( dbname ) == 0 );
}


