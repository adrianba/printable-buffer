#include "lest_basic.hpp"
using namespace std;

#include "../src/printable-buffer.h"

const lest::test specification[] =
{
    CASE( "Single char writes successfully and fills buffer" )
    {
        uint8_t buf[3];
        buf[0] = buf[1] = buf[2] = 0xcc;
        PrintableBuffer pb(buf,2);
        size_t r = pb.write('A');
        EXPECT( 1 == r );
        EXPECT( buf[0] == 'A');
        EXPECT( buf[1] == '\0');
        EXPECT( buf[2] == 0xcc);
        EXPECT( (const char*)pb == (const char*)buf);
        EXPECT( pb.remaining() == 0);
    },
    CASE( "Multiple char writes successfully and fills buffer" )
    {
        uint8_t buf[6];
        buf[5] = 0xcc;
        PrintableBuffer pb(buf,5);
        size_t r = pb.write((uint8_t*)"0123",4);
        EXPECT( 4 == r );
        EXPECT( buf[0] == '0');
        EXPECT( buf[1] == '1');
        EXPECT( buf[2] == '2');
        EXPECT( buf[3] == '3');
        EXPECT( buf[4] == '\0');
        EXPECT( buf[5] == 0xcc);
        EXPECT( pb.remaining() == 0);
    },
    CASE( "Multiple char write when buffer size is insufficient" )
    {
        uint8_t buf[3];
        buf[0] = buf[1] = buf[2] = 0xcc;
        PrintableBuffer pb(buf,2);
        size_t r = pb.write((uint8_t*)"0123",4);
        EXPECT( 1 == r );
        EXPECT( buf[0] == '0');
        EXPECT( buf[1] == '\0');
        EXPECT( buf[2] == 0xcc);
        EXPECT( pb.remaining() == 0);
    },
    CASE( "qprintf successfully and fills buffer" )
    {
        uint8_t buf[6];
        buf[5] = 0xcc;
        PrintableBuffer pb(buf,5);
        size_t r = pb.qprintf("0123");
        EXPECT( 4 == r );
        EXPECT( buf[0] == '0');
        EXPECT( buf[1] == '1');
        EXPECT( buf[2] == '2');
        EXPECT( buf[3] == '3');
        EXPECT( buf[4] == '\0');
        EXPECT( buf[5] == 0xcc);
        EXPECT( pb.remaining() == 0);
    },
    CASE( "qprintf when buffer size is insufficient" )
    {
        uint8_t buf[3];
        buf[0] = buf[1] = buf[2] = 0xcc;
        PrintableBuffer pb(buf,2);
        EXPECT( pb.remaining() == 1);
        size_t r = pb.qprintf("0123");
        EXPECT( 4 == r ); // qprintf returns the number of chars that _would have_ been written
        EXPECT( buf[0] == '0');
        EXPECT( buf[1] == '\0');
        EXPECT( buf[2] == 0xcc);
        EXPECT( pb.remaining() == 0);
    },
    CASE( "Repeat single char write until buffer full" )
    {
        uint8_t buf[4];
        buf[0] = buf[1] = buf[2] = buf[3] = 0xcc;
        PrintableBuffer pb(buf,3);
        size_t r = pb.write('A');
        EXPECT( 1 == r );
        EXPECT( buf[0] == 'A');
        EXPECT( buf[1] == '\0');
        EXPECT( buf[2] == 0xcc);
        EXPECT( pb.remaining() == 1);
        r = pb.write('B');
        EXPECT( 1 == r );
        EXPECT( buf[0] == 'A');
        EXPECT( buf[1] == 'B');
        EXPECT( buf[2] == '\0');
        EXPECT( buf[3] == 0xcc);
        EXPECT( pb.remaining() == 0);
        r = pb.write('C');
        EXPECT( 0 == r );
        EXPECT( buf[0] == 'A');
        EXPECT( buf[1] == 'B');
        EXPECT( buf[2] == '\0');
        EXPECT( buf[3] == 0xcc);
        EXPECT( pb.remaining() == 0);
    },
    CASE( "Repeat multiple char write until buffer full including partial write" )
    {
        uint8_t buf[7];
        buf[0] = buf[1] = buf[2] = buf[3] = buf[4] = buf[5] = buf[6] = 0xcc;
        PrintableBuffer pb(buf,6);
        size_t r = pb.write((uint8_t*)"01",2);
        EXPECT( 2 == r );
        EXPECT( buf[0] == '0');
        EXPECT( buf[1] == '1');
        EXPECT( buf[2] == '\0');
        EXPECT( buf[3] == 0xcc);
        EXPECT( pb.remaining() == 3);
        r = pb.write((uint8_t*)"23",2);
        EXPECT( 2 == r );
        EXPECT( buf[0] == '0');
        EXPECT( buf[1] == '1');
        EXPECT( buf[2] == '2');
        EXPECT( buf[3] == '3');
        EXPECT( buf[4] == '\0');
        EXPECT( buf[5] == 0xcc);
        EXPECT( pb.remaining() == 1);
        r = pb.write((uint8_t*)"45",2);
        EXPECT( 1 == r );
        EXPECT( buf[0] == '0');
        EXPECT( buf[1] == '1');
        EXPECT( buf[2] == '2');
        EXPECT( buf[3] == '3');
        EXPECT( buf[4] == '4');
        EXPECT( buf[5] == '\0');
        EXPECT( buf[6] == 0xcc);
        EXPECT( pb.remaining() == 0);
        r = pb.write((uint8_t*)"67",2);
        EXPECT( 0 == r );
        EXPECT( buf[0] == '0');
        EXPECT( buf[1] == '1');
        EXPECT( buf[2] == '2');
        EXPECT( buf[3] == '3');
        EXPECT( buf[4] == '4');
        EXPECT( buf[5] == '\0');
        EXPECT( buf[6] == 0xcc);
        EXPECT( pb.remaining() == 0);
    },
    CASE( "Repeat qprintf until buffer full including partial write" )
    {
        uint8_t buf[7];
        buf[0] = buf[1] = buf[2] = buf[3] = buf[4] = buf[5] = buf[6] = 0xcc;
        PrintableBuffer pb(buf,6);
        size_t r = pb.qprintf("01");
        EXPECT( 2 == r );
        EXPECT( buf[0] == '0');
        EXPECT( buf[1] == '1');
        EXPECT( buf[2] == '\0');
        EXPECT( buf[3] == 0xcc);
        EXPECT( pb.remaining() == 3);
        r = pb.qprintf("23");
        EXPECT( 2 == r );
        EXPECT( buf[0] == '0');
        EXPECT( buf[1] == '1');
        EXPECT( buf[2] == '2');
        EXPECT( buf[3] == '3');
        EXPECT( buf[4] == '\0');
        EXPECT( buf[5] == 0xcc);
        EXPECT( pb.remaining() == 1);
        r = pb.qprintf("45");
        EXPECT( 2 == r );
        EXPECT( buf[0] == '0');
        EXPECT( buf[1] == '1');
        EXPECT( buf[2] == '2');
        EXPECT( buf[3] == '3');
        EXPECT( buf[4] == '4');
        EXPECT( buf[5] == '\0');
        EXPECT( buf[6] == 0xcc);
        EXPECT( pb.remaining() == 0);
        r = pb.qprintf("67");
        EXPECT( 2 == r );
        EXPECT( buf[0] == '0');
        EXPECT( buf[1] == '1');
        EXPECT( buf[2] == '2');
        EXPECT( buf[3] == '3');
        EXPECT( buf[4] == '4');
        EXPECT( buf[5] == '\0');
        EXPECT( buf[6] == 0xcc);
        EXPECT( pb.remaining() == 0);
    },
    CASE( "Single char write when buffer size is 1" )
    {
        uint8_t buf[2];
        buf[0] = buf[1] = 0xcc;
        PrintableBuffer pb(buf,1);
        size_t r = pb.write('A');
        EXPECT( 0 == r );
        EXPECT( buf[0] == '\0');
        EXPECT( buf[1] == 0xcc);
        EXPECT( pb.remaining() == 0);
    },
    CASE( "Single char write when buffer size is 0" )
    {
        uint8_t buf[2];
        buf[0] = buf[1] = 0xcc;
        PrintableBuffer pb(buf,0);
        size_t r = pb.write('A');
        EXPECT( 0 == r );
        EXPECT( buf[0] == 0xcc);
        EXPECT( pb.remaining() == 0);
    },
    CASE( "Multiple char write when buffer size is 1" )
    {
        uint8_t buf[2];
        buf[0] = buf[1] = 0xcc;
        PrintableBuffer pb(buf,1);
        size_t r = pb.write((uint8_t*)"0123",4);
        EXPECT( 0 == r );
        EXPECT( buf[0] == '\0');
        EXPECT( buf[1] == 0xcc);
        EXPECT( pb.remaining() == 0);
    },
    CASE( "Multiple char write when buffer size is 0" )
    {
        uint8_t buf[2];
        buf[0] = buf[1] = 0xcc;
        PrintableBuffer pb(buf,0);
        size_t r = pb.write((uint8_t*)"0123",4);
        EXPECT( 0 == r );
        EXPECT( buf[0] == 0xcc);
        EXPECT( pb.remaining() == 0);
    },
    CASE( "qprintf when buffer size is 1" )
    {
        uint8_t buf[2];
        buf[0] = buf[1] = 0xcc;
        PrintableBuffer pb(buf,1);
        size_t r = pb.qprintf("0123");
        EXPECT( 4 == r );
        EXPECT( buf[0] == '\0');
        EXPECT( buf[1] == 0xcc);
        EXPECT( pb.remaining() == 0);
    },
    CASE( "qprintf when buffer size is 0" )
    {
        uint8_t buf[2];
        buf[0] = buf[1] = 0xcc;
        PrintableBuffer pb(buf,0);
        size_t r = pb.qprintf("0123");
        EXPECT( 4 == r );
        EXPECT( buf[0] == 0xcc);
        EXPECT( pb.remaining() == 0);
    },
};

int main( int argc, char * argv[] )
{
    int r = lest::run( specification );
    cout << "Run " << sizeof(specification)/sizeof(specification[0]) << " tests. (" << (r==0 ? "success" : "failure") << ")\n";
    return r;
}
