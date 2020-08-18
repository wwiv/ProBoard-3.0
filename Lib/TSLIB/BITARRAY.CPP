/***************************************************************************
 class BitArray

 Compatibility: DOS, OS/2, Windows
 Models       : 16 bit - 32 bit
***************************************************************************/

#ifdef PEX
  #include <pb_sdk.h>
#endif

#include "tslib.hpp"

QBitArray::QBitArray(long size,long s)
{
	unsigned len = unsigned(size >> 4) + 1;
	
    array = new unsigned short[len];

    for(unsigned i = 0 ; i < len ; i++)
      array[i] = 0;

    start = s;
}

QBitArray::~QBitArray()
{
   delete [] array;
}

bool
QBitArray::operator[](long i) const
{
    return bool(!!(array[unsigned((i-start) >> 4)] & (1 << BYTE((i-start) & 0xF))));
}

void
QBitArray::set(long i)
{
    array[unsigned((i-start) >> 4)] |= WORD(1 << BYTE((i-start) & 0xF));
}

void
QBitArray::clear(long i)
{
    array[unsigned((i-start) >> 4)] &= WORD(~(1 << BYTE((i-start) & 0xF)));
}

