#include <gtest/gtest.h>
#include <gdbm.h>
#include <unistd.h>
#include <stdlib.h>
#include <random>
#include <vector>

//
//
//
std::string GetRandomString( )
{
    const std::string alphabet( "0123456789"
                                "abcdefghijklmnopqrstuvwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );

    std::random_device rd;
    std::mt19937 g( rd() );
    std::uniform_int_distribution< std::string::size_type > pick( 0, alphabet.size() );

    std::string::size_type length = 10 * pick( g );
    std::string s;
    s.reserve( length );

    while( length-- )
    {
        const char c = alphabet[ pick( g ) ];
        s += c;
    }
    return s;
}

typedef std::vector< std::pair< std::string, std::string > > Data;


void Insert( GDBM_FILE dbf, Data& data )
{
    data.clear();

    gdbm_count_t loopSize = 20000;
    datum key;
    datum content, fetched;
    std::string txtK, txtC;
    const int flag = GDBM_INSERT;
    for( gdbm_count_t i = 0; i < loopSize; i++ )
    {
        txtK = std::to_string( i ) + GetRandomString();
        key.dptr = (char*)txtK.c_str();
        key.dsize = txtK.size();

        txtC = GetRandomString();
        content.dptr = (char*)txtC.c_str();
        content.dsize = txtC.size();

        data.push_back( std::make_pair( txtK, txtC ) );

        // printf( "key = '%s'; content = '%s'\n", key.dptr, content.dptr );

        EXPECT_TRUE( gdbm_store( dbf, key, content, flag ) == 0 );

        fetched = gdbm_fetch( dbf, key );
        EXPECT_TRUE( fetched.dptr );
        EXPECT_EQ( fetched.dsize, content.dsize );
        EXPECT_TRUE( memcmp( fetched.dptr, content.dptr, fetched.dsize ) == 0 );

        free( fetched.dptr );
    }

    gdbm_count_t count;
    EXPECT_TRUE( gdbm_count( dbf, &count ) == 0 );
    EXPECT_EQ( count, loopSize );
}


void Delete( GDBM_FILE dbf, Data& data )
{
    std::random_device rd;
    std::mt19937 g( rd() );

    std::shuffle( data.begin(), data.end(), g );
    datum key;
    datum content, fetched;

    for( auto v : data )
    {
        key.dptr = (char*)v.first.c_str();
        key.dsize = v.first.size();

        content.dptr = (char*)v.second.c_str();
        content.dsize = v.second.size();

        fetched = gdbm_fetch( dbf, key );
        EXPECT_TRUE( fetched.dptr );

        EXPECT_EQ( fetched.dsize, content.dsize );
        EXPECT_TRUE( memcmp( fetched.dptr, content.dptr, fetched.dsize ) == 0 );

        free( fetched.dptr );

        EXPECT_TRUE( gdbm_delete( dbf, key ) == 0 );

        fetched = gdbm_fetch( dbf, key );
        EXPECT_TRUE( !fetched.dptr );
    }
    gdbm_count_t count;
    EXPECT_TRUE( gdbm_count( dbf, &count ) == 0 );
    EXPECT_EQ( count, 0 );
}


TEST(gdbm, store_fetch_delete)
{
    GDBM_FILE dbf;
    char dbname[] = "./tmp.db";
    const int block_size = 0;
    const int mode = 0600;

    std::vector< std::pair< std::string, std::string > > all;

    dbf = gdbm_open( dbname, block_size, GDBM_NEWDB, mode, NULL );
    EXPECT_TRUE( dbf );
    Insert( dbf, all );
    Delete( dbf, all );
    EXPECT_NO_THROW( gdbm_close( dbf ) );


    dbf = gdbm_open( dbname, block_size, GDBM_WRITER, mode, NULL );
    EXPECT_TRUE( dbf );
    Insert( dbf, all );
    Delete( dbf, all );
    EXPECT_NO_THROW( gdbm_close( dbf ) );


    EXPECT_TRUE( unlink( dbname ) == 0 );
}

