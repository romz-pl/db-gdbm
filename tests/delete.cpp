#include <gtest/gtest.h>
#include <gdbm.h>
#include <unistd.h>
#include <random>
#include <map>
#include <cstdlib>

//
//
//
std::string GetRandomString( const std::size_t maxLength )
{
    const std::string alphabet( "0123456789"
                                "abcdefghijklmnopqrstuvwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );

    std::random_device rd;
    std::mt19937 g( rd() );
    std::uniform_int_distribution< std::string::size_type > pick( 1, alphabet.size() );
    std::uniform_int_distribution< std::string::size_type > pickLength( 1, maxLength );

    std::size_t length = pickLength( g );
    std::string s;
    s.reserve( length );

    while( length-- )
    {
        const char c = alphabet[ pick( g ) ];
        s += c;
    }
    return s;
}


void Insert( GDBM_FILE dbf, const std::string& keyD, const std::string& contentD )
{
    datum key, content, fetched;

    key.dptr = (char*)keyD.c_str();
    key.dsize = keyD.size();

    content.dptr = (char*)contentD.c_str();
    content.dsize = contentD.size();

    const int flag = GDBM_REPLACE;
    EXPECT_TRUE( gdbm_store( dbf, key, content, flag ) == 0 );

    fetched = gdbm_fetch( dbf, key );
    EXPECT_TRUE( fetched.dptr );
    EXPECT_EQ( fetched.dsize, content.dsize );
    EXPECT_TRUE( memcmp( fetched.dptr, content.dptr, fetched.dsize ) == 0 );

    free( fetched.dptr );
}

bool Delete( GDBM_FILE dbf, const std::string& keyD )
{
    const double threshold = 0.5;

    if( drand48() < threshold )
    {
         // printf(".");
         return false;
    }
    datum key, fetched;

    key.dptr = (char*)keyD.c_str();
    key.dsize = keyD.size();

    fetched = gdbm_fetch( dbf, key );
    EXPECT_TRUE( fetched.dptr );
    free( fetched.dptr );

    EXPECT_TRUE( gdbm_delete( dbf, key ) == 0 );

    fetched = gdbm_fetch( dbf, key );
    EXPECT_TRUE( !fetched.dptr );

    return true;
}

typedef std::map< std::string, std::string > Data;

void Check( GDBM_FILE dbf, Data& data )
{
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
    }
    gdbm_count_t count;
    EXPECT_TRUE( gdbm_count( dbf, &count ) == 0 );
    EXPECT_EQ( count, data.size() );
}


TEST(gdbm, delete)
{
    GDBM_FILE dbf;
    char dbname[] = "./tmp.db";
    const int block_size = 0;
    const int mode = 0600;

    const std::size_t loopSize = 20000;
    const std::size_t maxKeyLength = 5;
    const std::size_t maxContentLength = 6000;
    std::string key, content;

    Data data;

    dbf = gdbm_open( dbname, block_size, GDBM_NEWDB, mode, NULL );

    for( std::size_t i = 0; i < loopSize; i++ )
    {
        key = GetRandomString( maxKeyLength );
        content = GetRandomString( maxContentLength );

        data[ key ] = content;
        Insert( dbf, key, content );

        if( Delete( dbf, key ) )
        {
             data.erase( key );
        }
    }

    Check( dbf, data );

    EXPECT_NO_THROW( gdbm_close( dbf ) );
    EXPECT_TRUE( unlink( dbname ) == 0 );
}

